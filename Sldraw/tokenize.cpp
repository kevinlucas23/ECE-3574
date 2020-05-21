#include "tokenize.hpp"
#include <cctype>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

TokenSequenceType tokenize(std::istream& seq) {
	std::string test, kev;
	// TODO: implement your code here
	while (std::getline(seq, test)) {	// reads line by line
		if (test.empty()) {
			// checks if empty
			continue;
		}

		std::size_t found = test.find(COMMENT);	// checks if a comment exist in the string
		if (found != std::string::npos) {
			test.erase(test.begin() + found, test.end());	// erase where the comment begins till
		}

		if (!test.empty()) {
			if (test.back() == 13 || test.back() == 10 || test.back() == 32) {
				test.pop_back();
			}

			kev += (test + " ");
		}
	}

	return final_F(kev);
}

TokenSequenceType final_F(std::string& kev)
{
	std::istringstream kef(kev);
	TokenSequenceType tokens;
	std::string nope;
	while (std::getline(kef, nope, ' ')) {
		if (nope.find('\n') != std::string::npos) {//checks if the string contains backslash n.
			std::string kaboum = "";
			std::size_t pos = 0;

			while ((pos = nope.find('\n')) != std::string::npos) {
				kaboum += nope.substr(0, pos) + " ";
				nope.erase(0, pos + 1);
			}

			kaboum += nope + " ";
			std::istringstream kef(kaboum);
			std::string iss;

			while (std::getline(kef, iss, ' ')) {
				letsee(iss, &tokens);
			}
		}
		else {
			if (!nope.empty()) {
				letsee(nope, &tokens);
			}
		}
	}

	return tokens;
}

void letsee(std::string nope, TokenSequenceType* tokens)
{
	if (nope.front() == OPEN) {
		nope.erase(nope.begin());
		tokens->push_back("(");
		if (!nope.empty()) {
			if (nope.back() == CLOSE) {
				int lolipop = 0;
				while (nope.back() == CLOSE) {
					lolipop++;
					nope.pop_back();
					if (nope.empty()) break;
				}
				if (!nope.empty()) {
					tokens->push_back(nope);
				}
				int i = 0;
				while (i < lolipop) {
					tokens->push_back(")");
					i++;
				}
			}
			else {
				tokens->push_back(nope);
			}
		}
	}
	else if (nope.back() == CLOSE) {
		int lolipop = 0;
		for (auto i = nope.size() - 1; i > 0; i--) {	// checks if the back of string is ")"
			if (nope.at(i) == CLOSE) {
				lolipop++;
			}
		}
		int i = 0;
		std::string kab = nope;
		while (i < lolipop) {
			nope.pop_back();
			i++;
		}

		if (nope.empty()) {
			tokens->push_back(kab);
		}
		else {
			tokens->push_back(nope);
			i = 0;
			while (i < lolipop) {
				tokens->push_back(")");
				i++;
			}
		}
	}
	else {
		tokens->push_back(nope);
	}
}