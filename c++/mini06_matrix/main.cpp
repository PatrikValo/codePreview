#include "matrix.hpp"
#include <iostream>

using namespace std;

int main() {
	matrix mtOne({ 1, 0, 1, 0,
	                 0, 1, 0, 1,
	                 1, 0, 1, 0,
	                 0, 1, 0, 1 },
	    4);

	matrix mtTwo({ 0, 1, 0, 1,
	                 1, 0, 1, 0,
	                 0, 1, 0, 1,
	                 1, 1, 1, 1 },
	    4);

	const int multiplier = 2;

	cout << "************** mtOne **************\n";
	cout << mtOne << endl;

	cout << "************** mtTwo **************\n";
	cout << mtTwo << endl;

	cout << "************** mtOne + mtTwo **************\n";
	cout << (mtOne + mtTwo) << endl;

	cout << "************** mtOne - mtTwo **************\n";
	cout << (mtOne - mtTwo) << endl;

	cout << "************** mtOne * multiplier **************\n";
	cout << (mtOne * multiplier) << endl;

	cout << "************** mtOne[{ 1, 1 }] **************\n";
	cout << "mtOne[{ 1, 1 }]: " << mtOne[{ 1, 1 }] << endl;

	cout << boolalpha; // print bool values as true/false instead of 1/0
	cout << "************* equality comparison **************\n";
	cout << "mtOne == mtOne: " << (mtOne == mtOne) << endl;
	cout << "mtOne != mtTwo: " << (mtOne != mtTwo) << endl;

	return 0;
}
