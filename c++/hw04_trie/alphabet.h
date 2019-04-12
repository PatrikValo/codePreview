#ifndef ALPHABET_H
#define ALPHABET_H
#pragma once

/** Alphabet specifications
Every alphabet specification class has to have the following static members:
  static const int size; // the number of letters in the alphabet
  static int ord(char letter); // maps letters to 0 .. size - 1
                               // returns -1 for invalid letters
  static char chr(int index); // maps 0 .. size - 1 to letters
                              // behaviour for indices < 0 or >= size undefined
*/

template <char From, char To>
struct RangeAlphabet {
	static_assert(From <= To, "RangeAlphabet with empty Range");
	static const int size = To - From + 1;
	static int ord(char letter) {
		return From <= letter && letter <= To ? letter - From : -1;
	}
	static char chr(int index) {
		return From + index;
	}
};

template <typename A1, typename A2>
struct CombineAlphabets {
	// note: only works correctly if the alphabets are disjoint
	static const int size = A1::size + A2::size;
	static int ord(char letter) {
		int result = A1::ord(letter);
		if (result != -1) {
			return result;
		}
		result = A2::ord(letter);
		return result == -1 ? -1 : A1::size + result;
	}
	static char chr(int index) {
		return index < A1::size
		    ? A1::chr(index)
		    : A2::chr(index - A1::size);
	}
};

using PrintableASCII = RangeAlphabet<32, 126>;
using LowerCaseAlphabet = RangeAlphabet<'a', 'z'>;
using UpperCaseAlphabet = RangeAlphabet<'A', 'Z'>;
using BothCasesAlphabet = CombineAlphabets<LowerCaseAlphabet, UpperCaseAlphabet>;
using Binary = RangeAlphabet<'0', '1'>;
using Digits = RangeAlphabet<'0', '9'>;
using HexDigits = CombineAlphabets<Digits, RangeAlphabet<'A', 'F'>>;
using AlphaNumeric = CombineAlphabets<BothCasesAlphabet, Digits>;

struct MorseCode {
	static const int size = 2;
	static int ord(char letter) {
		return letter == '.' ? 0 : letter == '-' ? 1 : -1;
	}
	static char chr(int index) {
		return ".-"[index];
	}
};

struct DNACode {
	static const int size = 4;
	static int ord(char letter) {
		for (int i = 0; i < size; ++i) {
			if ("ACTG"[i] == letter) {
				return i;
			}
		}
		return -1;
	}
	static char chr(int index) {
		return "ACTG"[index];
	}
};

#endif
