#include "expression.hpp"

// system includes
#include <sstream>
#include <cmath>
#include <limits>
#include <cctype>
#include <stdlib.h>
#include<iostream>

Expression::Expression(bool tf) {
	// TODO: implement this function
	head.type = BooleanType;
	head.value.bool_value = tf;
}

Expression::Expression(double num) {
	// TODO: implement this function
	head.type = NumberType;
	head.value.num_value = num;
}

Expression::Expression(const std::string& sym) {
	// TODO: implement this function
	head.type = SymbolType;
	head.value.sym_value = sym;
}

bool Expression::operator==(const Expression& exp) const noexcept {
	// TODO: implement this function
	if (exp.head.type == NumberType) {
		return  this->head.value.num_value == exp.head.value.num_value;
	}

	if (exp.head.type == BooleanType) {
		return this->head.value.bool_value == exp.head.value.bool_value;
	}

	if (exp.head.type == SymbolType) {
		return this->head.value.sym_value == exp.head.value.sym_value;
	}

	if (exp.head.type == NoneType) {
		return true;
	}

	return true;
}

std::ostream& operator<<(std::ostream& out, const Expression& exp) {
	// TODO: implement this function
	return out;
}

bool token_to_atom(const std::string& token, Atom& atom) {
	// TODO: implement this function
// return true if it a token is valid. otherwise, return false.
bool letter = false;
bool digit = false;
double kev;
std::istringstream look(token);
look >> std::noskipws >> kev;
if (token == "True" || token == "true") {
	atom.type = BooleanType;
	atom.value.bool_value = true;
	return true;
}

if (token == "False" || token == "false") {
	atom.type = BooleanType;
	atom.value.bool_value = false;
	return true;
}

if (token == "pi") {
	atom.type = NumberType;
	atom.value.num_value = atan2(0, -1);
	return true;
}

if (look.eof() && !look.fail()) {
	atom.type = NumberType;
	atom.value.num_value = kev;
	return true;
}

if (token.size() >= 2) {
	if (isdigit(token.at(0)) != 0 && isalpha(token.at(1)) != 0) {
		return false;
	}
}

atom.type = SymbolType;
atom.value.sym_value = token;
return true;
}
