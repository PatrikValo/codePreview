#include "bank.hpp"

IAccount& Bank::createAccount(const std::string& name, IAccount& account) {
	if (_accounts.find(name) != _accounts.end()) {
		throw std::runtime_error("Already exist account with name");
	}
    return *_accounts.emplace(std::make_pair(name, account.clone())).first->second;
}

const IAccount& Bank::getAccount(const std::string& name) const {
	auto it = _accounts.find(name);
	if (it == _accounts.end()) {
		throw std::runtime_error("Not exist account with name");
	}
    return *it->second;
}

IAccount& Bank::getAccount(const std::string& name) {
	auto it = _accounts.find(name);
	if (it == _accounts.end()) {
		throw std::runtime_error("Not exist account with name");
	}
    return *it->second;
}

void Bank::print(std::ostream& out) const {
	for (auto it = _accounts.begin(); it != _accounts.end(); ++it) {
		out << "Name " << it->first << '\n';
		it->second.get()->print(out);
		out << '\n';
	}
}
void Bank::nextMonth() {
	for (auto it = _accounts.begin(); it != _accounts.end(); ++it) {
		it->second.get()->applyInterest();
	}
}
