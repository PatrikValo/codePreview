#include "trie.h"

#include "alphabet.h"

#include <iostream>
#include <stdexcept>
#include <string>

using Decoder = Trie<MorseCode, char>;

Decoder createDecoder() {
	Decoder decoder;
	decoder.insert(".-",   'A');
	decoder.insert("-...", 'B');
	decoder.insert("-.-.", 'C');
	decoder.insert("-..",  'D');
	decoder.insert(".",    'E');
	decoder.insert("..-.", 'F');
	decoder.insert("--.",  'G');
	decoder.insert("....", 'H');
	decoder.insert("..",   'I');
	decoder.insert(".---", 'J');
	decoder.insert("-.-",  'K');
	decoder.insert(".-..", 'L');
	decoder.insert("--",   'M');
	decoder.insert("-.",   'N');
	decoder.insert("---",  'O');
	decoder.insert(".--.", 'P');
	decoder.insert("--.-", 'Q');
	decoder.insert(".-.",  'R');
	decoder.insert("...",  'S');
	decoder.insert("-",    'T');
	decoder.insert("..-",  'U');
	decoder.insert("...-", 'V');
	decoder.insert(".--",  'W');
	decoder.insert("-..-", 'X');
	decoder.insert("-.--", 'Y');
	decoder.insert("--..", 'Z');
	return decoder;
}

int main() {
	try {
		const Decoder decoder = createDecoder();
		std::string word;
		while (std::cin >> word) {
			const char* letter = decoder.search(word);
			std::cout << (letter ? *letter : '?');
		}
		std::cout << '\n';
	} catch (std::out_of_range& ex) {
		std::cerr << "Error: wrong symbol.\n";
	}
}
