//
// Created by Andrew on 30-Sep-20.
//

#include "NotEnoughMoneyException.h"
#include <ostream>

NotEnoughMoneyException::NotEnoughMoneyException(double available, double requested) :
		_available(available), _requested(requested) {
}

double NotEnoughMoneyException::available() const {
	return _available;
}

double NotEnoughMoneyException::requested() const {
	return _requested;
}

std::ostream& operator<<(std::ostream& os, const NotEnoughMoneyException& e) {
	os << "available amount of money: " << e.available() << ", requested: " << e.requested();
	return os;
}