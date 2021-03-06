//
// Created by Vladyslav Synytsyn on 22/10/2020.
//

#include <QtCore/QRandomGenerator>
#include "Registrator.h"

#include <QDebug>
#include <logics/exceptions/CustomerRegistrationException.h>
#include <logics/utils/general.h>

std::pair<QString, QString> Registrator::registerCustomer(const CustomerVerificationData& verificationData) const {
    Customer* customer = _customerDataManager.getCustomerByTaxNumber(verificationData.getTaxNumber());
    if (customer != nullptr) {
        QList<Card*> cards = customer->cards();
        for (int i = 0; i < cards.count(); ++i) {
            if (cards[i]->cardType() == verificationData.getCardType()) {
                throw CustomerRegistrationException(
                    "The person with a given tax number and chosen card type has been already registered.");
            }
        }
    } else {
        customer = new Customer(
                    verificationData.getName(),
                    verificationData.getTaxNumber(),
                    verificationData.getPhoneNumber(),
                    verificationData.getIncome());
    }

    QString pin = genPin();
    const QString number = generateCardNumber();
	Card* newCard = new Card(number, verificationData.getCardType(), pin);
    customer->addCard(newCard);

    _customerDao.saveCustomer(*customer);
    const std::pair<QString, QString>& returnVal = std::pair<QString, QString>(pin, newCard->id());
    delete customer;
    return returnVal;
}

QString Registrator::genPin() {
    return generatePin();
}

const QString Registrator::generateCardNumber() {
    QString cardNumber("4441");
    
    QRandomGenerator generator;
    generator.seed(QDateTime::currentSecsSinceEpoch());
    
    for (int i = 0; i < 12; ++i) {
        cardNumber += QString::number(generator.bounded(10));
    }
    return cardNumber;
}
