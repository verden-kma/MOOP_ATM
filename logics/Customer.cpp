//
// Created by Andrew on 30-Sep-20.
//


#include "Customer.h"
#include <utility>
#include <logics/exceptions/NoSuchCardException.h>
#include <logics/exceptions/NoSuchCreditException.h>
#include <logics/exceptions/NoSuchDepositException.h>
#include <data_access/CardDAO.h>
#include <data_access/CustomerDAO.h>
#include <data_access/CreditDAO.h>
#include <data_access/DepositDAO.h>
#include <data_access/PaymentDAO.h>

Customer::Customer(QString name, QString taxNum, QString phoneNum, const Money revenue) :
		_name(std::move(name)), _taxNumber(std::move(taxNum)), _phoneNumber(std::move(phoneNum)),
		_revenue(revenue),
		_creditLimit(revenue * Credit::creditLimitOfIncome) {

}

const QString& Customer::name() const {
    return _name;
}

const Money& Customer::revenue() const {
	return _revenue;
}

void Customer::setRevenue(const Money& m) {
	_revenue = m;
	_creditLimit = _revenue * Credit::creditLimitOfIncome;
}

const QString& Customer::phoneNumber() const {
	return _phoneNumber;
}

const Money& Customer::creditLimit() const {
	return _creditLimit;
}

const QList<Card*>& Customer::cards() const {
	return _cards;
}

const QList<Credit*>& Customer::credits() const {
    return _credits;
}

const QList<Deposit*>& Customer::deposits() const {
    return _deposits;
}

void Customer::addCard(Card* c) {
	_cards.append(c);
	CardDAO::getInstance().saveCard(*c);
	CustomerDAO::getInstance().addCard(_taxNumber, c->id());
}

void Customer::addCredit(Credit* c) {
	_credits.append(c);
}

void Customer::removeCredit(uint id) {
	int index = findIndex(_credits, id);
	if (index == -1) throw NoSuchCreditException(_taxNumber, id);
	_credits.removeAt(index);
}

void Customer::addDeposit(Deposit* d) {
	_deposits.append(d);
}

void Customer::removeDeposit(uint id) {
	int index = findIndex(_deposits, id);
	if (index == -1) throw NoSuchDepositException(_taxNumber, id);
	_deposits.removeAt(index);
}


Customer::~Customer() {
    releaseMemory(_cards);
    releaseMemory(_credits);
    releaseMemory(_deposits);
}

template<typename Pointer>
void Customer::releaseMemory(QList<Pointer>& list) {
    for (uint i = 0; i < list.length(); i++) {
        delete list[i];
        list[i] = nullptr;
    }
}

//QList<RegularPayment*> Customer::regularPayments() const {
//    return PaymentDAO::getInstance().getSenderCardPayments(_taxNumber);
//}

