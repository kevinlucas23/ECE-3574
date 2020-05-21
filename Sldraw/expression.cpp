#include "expression.hpp"

// system includes
#include <sstream>
#include <cmath>
#include <limits>
#include <cctype>
#include <stdlib.h>
#include<iostream>
#include <tuple>

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

Expression::Expression(std::tuple<double, double> value) {
	// TODO: implement this function
	head.type = PointType;
	head.value.point_value.x = std::get<0>(value);
	head.value.point_value.y = std::get<1>(value);
}

Expression::Expression(std::tuple<double, double> start,
	std::tuple<double, double> end) {
	// TODO: implement this function
	head.type = LineType;
	head.value.line_value.first.x = std::get<0>(start);
	head.value.line_value.first.y = std::get<1>(start);

	head.value.line_value.second.x = std::get<0>(end);
	head.value.line_value.second.y = std::get<1>(end);
}

Expression::Expression(std::tuple<double, double> center,
	std::tuple<double, double> start,
	double angle) {
	// TODO: implement this function
	head.type = ArcType;
	head.value.arc_value.center.x = std::get<0>(center);
	head.value.arc_value.center.y = std::get<1>(center);

	head.value.arc_value.start.x = std::get<0>(start);
	head.value.arc_value.start.y = std::get<1>(start);

	head.value.arc_value.span = angle;
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

	if (exp.head.type == PointType) {
		return this->head.value.point_value == exp.head.value.point_value;
	}

	if (exp.head.type == LineType) {
		return this->head.value.line_value.first == exp.head.value.line_value.first && this->head.value.line_value.second == exp.head.value.line_value.second;
	}

	if (exp.head.type == ArcType) {
		return this->head.value.arc_value.span == exp.head.value.arc_value.span && this->head.value.arc_value.center == exp.head.value.arc_value.center && this->head.value.arc_value.start == exp.head.value.arc_value.start;
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