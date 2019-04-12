#include "accounts.hpp"
#include "bank.hpp"

#include "catch.hpp"
#include <limits>
#include <sstream>

class TestStream : public std::ostringstream {
public:
	bool contains(const std::string& substring) {
		return str().find(substring) != std::string::npos;
	}
};

TEST_CASE("CheckingAccount: Basic tests") {
	CheckingAccount cha(1'50, 50'000);
	SECTION("deposit and withdraw") {
		REQUIRE(cha.balance() == 50'000);
		cha.deposit(50'000);
		REQUIRE(cha.balance() == 100'000);
		REQUIRE(cha.withdraw(60'000));
		REQUIRE(cha.balance() == 40'000);
		REQUIRE_FALSE(cha.withdraw(60'000));
		REQUIRE_FALSE(cha.withdraw(0));
		REQUIRE(cha.balance() == 40'000);
		REQUIRE(cha.withdraw(40'000));
		REQUIRE(cha.balance() == 0);
	}

	SECTION("interest") {
		cha.applyInterest();
		REQUIRE(cha.balance() == 50'750);
		cha.applyInterest(); // Should be 51,511.25, but we round down
		REQUIRE(cha.balance() == 51'511);
	}

	SECTION("printing") {
		TestStream out;
		SECTION("print") {
			cha.print(out);
		}
		SECTION("operator<<") {
			out << cha;
		}
		REQUIRE(out.contains("50000"));
	}

	SECTION("clone") {
		auto fives = cha.clone();
		REQUIRE(fives);
		cha.withdraw(10'000);
		fives->deposit(225'555);
		REQUIRE(cha.balance() == 40'000);
		REQUIRE(fives->balance() == 27'5555);
	}

	// TODO: make your own tests!
}

TEST_CASE("SavingsAccount: Basic tests") {
	SavingsAccount sa(1'50, 50'000, 1'80);

	SECTION("withdraw") {
		REQUIRE_FALSE(sa.withdraw(49'116)); /* Incl. penalisation, we
                                                    round up to 50'001 */
		REQUIRE(sa.balance() == 50'000);
		REQUIRE(sa.withdraw(49'115)); /* Round up to 50'000 */
		REQUIRE(sa.balance() == 0);
	}

	// TODO: make your own tests!
}

TEST_CASE("CheckingAccountWithOverdraft: Basic tests") {
	CheckingAccountWithOverdraft chawod(1'50, 3000, 13'00, 2000);

	SECTION("overdraft") {
		REQUIRE(chawod.withdraw(2000));
		chawod.applyInterest();
		REQUIRE(chawod.balance() == 1015);
		REQUIRE(chawod.withdraw(2000));
		REQUIRE(chawod.balance() == -985);
		chawod.applyInterest();
		REQUIRE(chawod.balance() == -1114); // -1113.05 rounded down
		REQUIRE(chawod.withdraw(800));
		REQUIRE_FALSE(chawod.withdraw(100));
		chawod.applyInterest();
		REQUIRE(chawod.balance() == -2163);
		REQUIRE_FALSE(chawod.withdraw(0));
		REQUIRE_FALSE(chawod.withdraw(1));
	}

	// TODO: make your own tests!
}

TEST_CASE("Bank: Basic tests") {
	Bank b;
	std::string rick = "Rick Sanchez";
	std::string morty = "Morty Smith";
	CheckingAccount cha1(2'00, 10'000);
	CheckingAccount cha2(40, 1000);
	b.createAccount(rick, cha1);
	b.createAccount(morty, cha2);

	SECTION("getAccount") {
		REQUIRE(b.getAccount(morty).balance() == 1000);
	}

	SECTION("account is copied") {
		REQUIRE(cha1.withdraw(5000));
		REQUIRE(b.getAccount(rick).balance() == 10'000);
		REQUIRE(b.getAccount(morty).withdraw(700));
		REQUIRE(b.getAccount(morty).balance() == 300);
		REQUIRE(cha2.balance() == 1000);
	}

	SECTION("nextMonth") {
		b.nextMonth();
		REQUIRE(cha1.balance() == 10'000);
		REQUIRE(cha2.balance() == 1000);
		REQUIRE(b.getAccount(rick).balance() == 10'200);
		REQUIRE(b.getAccount(morty).balance() == 1004);
	}

	SECTION("print") {
		TestStream out;
		b.print(out);
		REQUIRE(out.contains(rick));
		REQUIRE(out.contains(morty));
		REQUIRE(out.contains("10000"));
	}

	// TODO: make your own tests!
}

TEST_CASE("MY") {
	SECTION("Saving Overflow") {
		SavingsAccount sa(9999, 2000000000, 99);
		sa.withdraw(1900000099);
		REQUIRE(sa.balance() == 81189900);
		auto new_ = sa.clone();
		new_.get()->withdraw(8000);
		sa.withdraw(8000);
		//REQUIRE(new_.get()->balance() == 81189901);
		REQUIRE(sa.balance() == new_.get()->balance());
	}
	SECTION("MIX") {
		CheckingAccountWithOverdraft sa(9999, 2000000000, 9879, 888688888);
		sa.withdraw(1900000099);
		REQUIRE(sa.balance() == 99999901);
		sa.withdraw(99999901);
		REQUIRE(sa.balance() == 0);
		sa.withdraw(879899988);
		REQUIRE(sa.balance() == -879899988);
		sa.applyInterest();
		REQUIRE(sa.balance() == -1749153187);
	}

	SECTION("MIX2") {
		CheckingAccountWithOverdraft sa(10000, 50473, 1585, 58475);
		sa.withdraw(100946);
		REQUIRE(sa.balance() == -50473);
		sa.applyInterest();
		REQUIRE(sa.withdraw(2));
		auto nove = sa.clone();
		nove.get()->deposit(8000);
		REQUIRE(nove.get()->balance() != sa.balance());
		nove.get()->withdraw(8000);
		REQUIRE(nove.get()->balance() == sa.balance());
	}

	SECTION("MIX3") {
		CheckingAccountWithOverdraft sa(5, 50473, 1, 58475);
		sa.applyInterest();
		REQUIRE(sa.balance() == 50498);
		REQUIRE(sa.balance() == 50498);
		REQUIRE(sa.withdraw(50499));
		sa.applyInterest();
		REQUIRE(sa.balance() == -2);
	}
	SECTION("MIX4") {
		CheckingAccountWithOverdraft sa(1, 1999999899, 1, 58475);
		sa.applyInterest();
		REQUIRE(sa.balance() == 2000199898);
	}

	SECTION("MIX5") {
		CheckingAccountWithOverdraft sa(1, 11, 5, 58475);
		sa.applyInterest();
		REQUIRE(sa.balance() == 11);
		sa.withdraw(10);
		sa.applyInterest();
		REQUIRE_FALSE(sa.withdraw(0));
		REQUIRE(sa.balance() == 1);
		REQUIRE(sa.withdraw(58476));
		REQUIRE(sa.balance() == -58475);
		sa.applyInterest();
		REQUIRE(sa.balance() == -58505);
		sa.applyInterest();
		REQUIRE(sa.balance() == -58535);
		sa.deposit(58535);
		REQUIRE(sa.balance() == 0);
		sa.applyInterest();
		sa.applyInterest();
		sa.applyInterest();
		sa.applyInterest();
		REQUIRE(sa.balance() == 0);
	}
	SECTION("MIX6") {
		CheckingAccountWithOverdraft sa(1, 11, 5, 58475);
		sa.applyInterest();
		REQUIRE(sa.balance() == 11);
		sa.withdraw(10);
		sa.applyInterest();
		REQUIRE(sa.balance() == 1);
		REQUIRE(sa.withdraw(58476));
		REQUIRE(sa.balance() == -58475);
		REQUIRE_FALSE(sa.withdraw(0));
		sa.applyInterest();
		REQUIRE(sa.balance() == -58505);
		sa.applyInterest();
		REQUIRE(sa.balance() == -58535);
		sa.deposit(58535);
		REQUIRE(sa.balance() == 0);
		sa.applyInterest();
		sa.applyInterest();
		sa.applyInterest();
		sa.applyInterest();
		REQUIRE(sa.balance() == 0);
		REQUIRE_FALSE(sa.withdraw(0));
		REQUIRE(sa.balance() == 0);
		REQUIRE(sa.withdraw(58475));
		REQUIRE(sa.balance() == -58475);
	}
}
