#include "accounts.hpp"

/* TODO */
#include <iostream>
#include <memory>


/*
 * CheckingAccount
*/
CheckingAccount::CheckingAccount(unsigned interest, unsigned deposit)
    : _interest(interest)
    , _deposit(deposit) {}

void CheckingAccount::deposit(unsigned increase) {
	_deposit += increase;
}

bool CheckingAccount::withdraw(unsigned decrease) {
	if (_deposit >= decrease && decrease > 0) {
		_deposit -= decrease;
		return true;
	}
	return false;
}

int CheckingAccount::balance() const {
	return int(_deposit);
}

void CheckingAccount::print(std::ostream& out) const {
	out << "Interest " << _interest << '\n';
	out << "Deposit " << _deposit << '\n';
}

void CheckingAccount::applyInterest() {
	long int interest = (_interest * _deposit) / 10000U;
	_deposit += interest;
}

std::unique_ptr<IAccount> CheckingAccount::clone() const {
	return std::make_unique<CheckingAccount>(*this);
}

/*
 * SavingsAccout
*/

SavingsAccount::SavingsAccount(unsigned interest, unsigned deposit, unsigned penalties)
    : CheckingAccount(interest, deposit)
    , _penalties(penalties) {}

bool SavingsAccount::withdraw(unsigned decrease) {
	long int modulo = (decrease * _penalties) % 10000U;
	long int result = (decrease * _penalties) / 10000U;

	if (modulo != 0) {
		result++;
	}
	result += decrease;
	if (_deposit >= result && result > 0) {
		_deposit -= result;
		return true;
	}
	return false;
}

void SavingsAccount::print(std::ostream& out) const {
	out << "Interest " << _interest << '\n';
	out << "Deposit " << _deposit << '\n';
	out << "Penalties " << _penalties << "\n";
}

std::unique_ptr<IAccount> SavingsAccount::clone() const {
	return std::make_unique<SavingsAccount>(*this);
}

/*
 * CheckingAccountWithOverdraft
*/

CheckingAccountWithOverdraft::CheckingAccountWithOverdraft(unsigned interest, unsigned deposit, unsigned overdraftInterest, unsigned overdraftLimit)
    : CheckingAccount(interest, deposit)
    , _overdraftInterest(overdraftInterest)
    , _overdraftLimit(overdraftLimit) {}

bool CheckingAccountWithOverdraft::withdraw(unsigned decrease) {
	long int result = _deposit - decrease;
	if (decrease > 0 && (result > 0 || -result <= _overdraftLimit)) {
		_deposit -= decrease;
		return true;
	}
	return false;
}

void CheckingAccountWithOverdraft::print(std::ostream& out) const {
	out << "Interest " << _interest << '\n';
	out << "Deposit " << _deposit << '\n';
	out << "OverdraftInterest " << _overdraftInterest << '\n';
	out << "OverdraftLimit " << _overdraftLimit << '\n';
}

void CheckingAccountWithOverdraft::applyInterest() {
	if (_deposit >= 0) {
		long int interest = (_interest * _deposit) / 10000U;
		_deposit += interest;
		return;
	}

	long int interest = -(_overdraftInterest * _deposit) / 10000U;
	long int modulo = -(_overdraftInterest * _deposit) % 10000U;
	if (modulo != 0) {
		interest++;
	}
	_deposit -= interest;
}

std::unique_ptr<IAccount> CheckingAccountWithOverdraft::clone() const {
	return std::make_unique<CheckingAccountWithOverdraft>(*this);
}
