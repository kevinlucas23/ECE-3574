#include "interpreter.hpp"
#include "tokenize.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"

// system includes
#include <stack>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>

bool Interpreter::parse(std::istream& expression) noexcept {
	// TODO: implement this function
	// return true if input is valid. otherwise, return false.
	ast = Expression();
	TokenSequenceType watchYourSelf = tokenize(expression);
	std::pair<bool, Expression> cool = env.final_parse(&watchYourSelf);
	ast = cool.second;
	bool done = cool.first;
	isGood = done;
	return done;
};

Expression Interpreter::eval() {
	// TODO: implement this function
	if (isGood) {	// value that stores the return value of parse
		graphics = env.drawm();
		isGood = false;
		return ast;
	}

	clear();
	InterpreterSemanticError as("Error: wrong input");
	throw as;
}

void Interpreter::clear()
{
	graphics.clear();
	env.resetS();
}

void Interpreter::ontheGo() {
	if (ast.head.type == NumberType) {
		std::cout << "(" << ast.head.value.num_value << ")" << std::endl;
	}
	else if (ast.head.type == BooleanType) {
		if (ast.head.value.bool_value) {
			std::cout << "(True)" << std::endl;
		}
		else {
			std::cout << "(False)" << std::endl;
		}
	}
	else if (ast.head.type == PointType) {
		std::cout << "(" << ast.head.value.point_value.x << "," << ast.head.value.point_value.y << ")" << std::endl;
	}
	else if (ast.head.type == LineType) {
		std::cout << "((" << ast.head.value.line_value.first.x << "," << ast.head.value.line_value.first.y << "),(" << ast.head.value.line_value.second.x << "," << ast.head.value.line_value.second.y << "))" << std::endl;
	}
	else if (ast.head.type == ArcType) {
		std::cout << "((" << ast.head.value.arc_value.center.x << "," << ast.head.value.arc_value.center.y << "),(" << ast.head.value.arc_value.start.x << "," << ast.head.value.arc_value.start.y << ") " << ast.head.value.arc_value.span << ")" << std::endl;
	}
	else if (ast.head.type == NoneType) {
		std::cout << "(None)" << std::endl;
	}
}