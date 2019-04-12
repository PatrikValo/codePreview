#include "accounts.hpp"
#include "bank.hpp"

#include <iostream>

int main() {
	// You can play with your implementation here.
	/*CheckingAccount a(1'30, 10'000);
    std::cout << a;*/
	SavingsAccount b(1'0, 10'000, 10);
	std::cout << b;
	b.applyInterest();
	b.withdraw(1000);
	std::cout << b;
}
