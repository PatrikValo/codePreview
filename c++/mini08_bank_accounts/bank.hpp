/* TODO */
#pragma once
#include "accounts.hpp"
#include <map>
#include <utility>

class Bank {
	std::map<std::string, std::unique_ptr<IAccount>> _accounts;

public:
	Bank() = default;
	Bank(const Bank&) = delete;
	Bank& operator=(const Bank&) = delete;

	IAccount& createAccount(const std::string& name, IAccount& account);

	const IAccount& getAccount(const std::string& name) const;
	IAccount& getAccount(const std::string& name);

	void print(std::ostream& out) const;

	void nextMonth();
};
