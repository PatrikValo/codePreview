/* TODO */
#pragma once
#include <iostream>
#include <memory>

class IAccount {
public:
	virtual void deposit(unsigned) = 0;
	virtual bool withdraw(unsigned) = 0;
	virtual int balance() const = 0;
	virtual void print(std::ostream&) const = 0;
	virtual void applyInterest() = 0;
	virtual std::unique_ptr<IAccount> clone() const = 0;
	friend std::ostream& operator<<(std::ostream& out, const IAccount& a) {
		a.print(out);
		return out;
	}
	virtual ~IAccount() = default;
};

class CheckingAccount : public IAccount {

protected:
	const long int _interest;
	long int _deposit;

public:
	CheckingAccount() = delete;
	CheckingAccount(unsigned interest, unsigned deposit);

	void deposit(unsigned increase) override;

	bool withdraw(unsigned decrease) override;

	int balance() const override;

	void print(std::ostream& out) const override;

	void applyInterest() override;

	std::unique_ptr<IAccount> clone() const override;
};

class SavingsAccount : public CheckingAccount {
	const long int _penalties;

public:
	SavingsAccount() = delete;
	SavingsAccount(unsigned interest, unsigned deposit, unsigned penalties);

	bool withdraw(unsigned decrease) override;

	void print(std::ostream& out) const override;

	std::unique_ptr<IAccount> clone() const override;
};

class CheckingAccountWithOverdraft : public CheckingAccount {
	const long int _overdraftInterest;
	const long int _overdraftLimit;

public:
	CheckingAccountWithOverdraft() = delete;
	CheckingAccountWithOverdraft(unsigned interest, unsigned deposit, unsigned overdraftInterest, unsigned overdraftLimit);

	bool withdraw(unsigned decrease) override;

	void print(std::ostream& out) const override;

	void applyInterest() override;

	std::unique_ptr<IAccount> clone() const override;
};
