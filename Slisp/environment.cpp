#include "environment.hpp"
#include "interpreter_semantic_error.hpp"

#include <cassert>
#include <cmath>
#include <stack>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>


Environment::Environment() {
	// TODO: implement your code ...
	checking = false;
}

Environment::~Environment() {
}

Expression Environment::makeTree(TokenSequenceType* yeah) { //creates a tree to store all the tokens
	Expression tom;
	while (!yeah->empty()) {
		if (yeah->front() == "(") {
			Atom letsRock;
			yeah->pop_front();

			if (yeah->empty()) {	// checks if the string is empty. If it is the parser input is invalid
				checking = true;
				return tom;
			}

			if (yeah->front() == ")") {	// checks if the string is ). If it is the parser input is invalid
				checking = true;
				return tom;
			}

			if (!token_to_atom(yeah->front(), letsRock)) { // checks if the string is valid
				checking = true;
				return tom;
			}
			tom = letsRock;
			yeah->pop_front();

			if (yeah->empty()) {	// checks if the string is empty. If it is the parser input is invalid
				checking = true;
				return tom;
			}

			while (yeah->front() == "(") {
				if (yeah->size() > 1) {
					tom.tail.push_back(makeTree(yeah));
				}
				else {
					checking = true;
					break;
				}

				if (yeah->empty()) {	// checks if the string is empty. If it is the parser input is invalid
					checking = true;
					return tom;
				}
			}
		}
		else if (yeah->front() == ")") {
			yeah->pop_front();
			return tom;	// therefore the parser was correct.
		}
		else {
			Expression kevin;
			kevin = makeTree_1(yeah, &tom);
			if (kevin.head.type != NoneType) {
				return kevin;
			}
		}
	}
	return tom;
}

Expression Environment::makeTree_1(TokenSequenceType* yeah, Expression* tom) {
	Atom radio;
	if (yeah->empty()) {	// checks if the string is empty. If it is the parser input is invalid
		checking = true;
		return *tom;
	}

	if (!token_to_atom(yeah->front(), radio)) {	// checks if the string is valid
		checking = true;
		return *tom;
	}

	tom->tail.push_back(radio);
	yeah->pop_front();

	if (yeah->empty()) {	// checks if the string is empty. If it is the parser input is invalid
		checking = true;
		return *tom;
	}

	while (yeah->front() == "(") {
		if (yeah->size() > 1) {
			tom->tail.push_back(makeTree(yeah));
		}
		else {
			checking = true;
			break;
		}

		if (yeah->empty()) {	// checks if the string is empty. If it is the parser input is invalid
			checking = true;
			return *tom;
		}
	}
	return Expression();
}

bool Environment::traverser_de_leau(Expression* naruto_utsumaki) {
	if (checking) {
		return false;
	}
	for (auto i = 0; i < naruto_utsumaki->tail.size(); i++) {
		response_finale = naruto_utsumaki->tail.at(i);
		if (!traverser_de_leau(&naruto_utsumaki->tail.at(i))) {	// check if there was an issue encountered with the parser.
			return false;
			break;
		}
		if (naruto_utsumaki->tail.at(i).head.type == NoneType) {
			naruto_utsumaki->tail.erase(naruto_utsumaki->tail.begin() + i); i -= 1;
		}
		else naruto_utsumaki->tail.at(i) = response_finale;
	}
	std::string bigHead = naruto_utsumaki->head.value.sym_value;
	if (bigHead == "define" || bigHead == "begin") {
		return procedure_1(naruto_utsumaki);
	}
 if (bigHead == "if") {
		return procedure_2(naruto_utsumaki);
	}
	if (bigHead == "not" || bigHead == "and" || bigHead == "or" || bigHead == "<" || bigHead == "<=" || bigHead == ">" || bigHead == ">=" || bigHead == "=" || bigHead == "+" || bigHead == "-" || bigHead == "*" || bigHead == "/" || bigHead == "log10" || bigHead == "pow") {
			if (naruto_utsumaki->tail.empty()) {
				return false;
			}
			for (auto i = 0; i < naruto_utsumaki->tail.size(); i++) {
				Atom moche;
				tortue = envmap.find(naruto_utsumaki->tail.at(i).head.value.sym_value);
				if (tortue == envmap.end() && naruto_utsumaki->tail.at(i).head.type != SymbolType) { // checks if it's in the map
					moche = naruto_utsumaki->tail.at(i).head;
				}
				else if (tortue != envmap.end()) {
					moche = tortue->second;
				}
				else {
					return false;
				}
				naruto_utsumaki->tail.at(i).head = moche;
			}
			if (!solution_de_probleme(naruto_utsumaki)) {
				return false;
			}
			response_finale = response_seconde;
		}
		else if (naruto_utsumaki->head.type != NoneType) {
			tortue = envmap.find(naruto_utsumaki->head.value.sym_value);
			if (tortue == envmap.end()) {	// checks if it's in the map
				response_finale = *naruto_utsumaki;
			}
			else {
				response_finale = tortue->second;
			}
		}
	return true;
}

bool Environment::solution_de_probleme(Expression* gaara_vs_pain) {
	std::string procedure = gaara_vs_pain->head.value.sym_value;
	if (procedure == "not") {
		if (gaara_vs_pain->tail.size() == 1) {
			if (gaara_vs_pain->tail.at(0).head.type == BooleanType) {
				if (gaara_vs_pain->tail.at(0).head.value.bool_value) {
					response_seconde = false;
				}
				else {
					response_seconde = true;
				}
				gaara_vs_pain->tail.clear();
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	if (procedure == "and") {
		if (gaara_vs_pain->tail.size() >= 2) {
			response_seconde.head.value.bool_value = gaara_vs_pain->tail.at(0).head.value.bool_value;
			for (auto i = 1; i < gaara_vs_pain->tail.size(); i++) {
				if (gaara_vs_pain->tail.at(i).head.type == BooleanType) {
					response_seconde = response_seconde.head.value.bool_value && gaara_vs_pain->tail.at(i).head.value.bool_value;
				}
				else {
					return false;
				}
			}
			gaara_vs_pain->tail.clear();
		}
		else {
			return false;
		}
	}
	if (procedure == "or") {
		if (gaara_vs_pain->tail.size() >= 2) {
			response_seconde.head.value.bool_value = gaara_vs_pain->tail.at(0).head.value.bool_value;
			for (auto i = 1; i < gaara_vs_pain->tail.size(); i++) {
				if (gaara_vs_pain->tail.at(i).head.type == BooleanType) {
					response_seconde = response_seconde.head.value.bool_value || gaara_vs_pain->tail.at(i).head.value.bool_value;
				}
				else {
					return false;
				}
			}
			gaara_vs_pain->tail.clear();
		}
		else {
			return false;
		}
	}
	else {
		return procedure_3(gaara_vs_pain);
	}
	return true;
}

std::pair<bool, Expression> Environment::final_parse(TokenSequenceType* sasuke) {
	if (sasuke->size() < 3) {
		return std::make_pair(false, Expression());
	}
	response_finale = response_seconde = Expression();
	checking = false;
	Expression pass = makeTree(sasuke);
	if (!sasuke->empty()) {
		sasuke->clear();
		return std::make_pair(false, Expression());
	}
	bool done = traverser_de_leau(&pass);
	if (response_finale.head.type == SymbolType) {
		return std::make_pair(false, Expression());
	}
	return std::make_pair(done, response_finale);
}

void Environment::resetS() {	// clears the map when an error was encountered.
	envmap.clear();
}


bool Environment::procedure_1(Expression* naruto_utsumaki) {
	std::string bigHead = naruto_utsumaki->head.value.sym_value;
	if (bigHead == "define") {
		if (naruto_utsumaki->tail.size() == 2) {
			if (naruto_utsumaki->tail.at(0).head.type == SymbolType) {
				if (naruto_utsumaki->tail.at(0).head.value.sym_value != "if" && naruto_utsumaki->tail.at(0).head.value.sym_value != "define" && naruto_utsumaki->tail.at(0).head.value.sym_value != "begin" && naruto_utsumaki->tail.at(0).head.value.sym_value != "point" && naruto_utsumaki->tail.at(0).head.value.sym_value != "line" && naruto_utsumaki->tail.at(0).head.value.sym_value != "arc" && naruto_utsumaki->tail.at(0).head.value.sym_value != "draw") {
					if (naruto_utsumaki->tail.at(1).head.type == SymbolType) {
						tortue = envmap.find(naruto_utsumaki->tail.at(1).head.value.sym_value);
						if (tortue == envmap.end()) { return false;	// checks if it's in the map
						}
						response_finale = tortue->second;
						envmap[naruto_utsumaki->tail.at(0).head.value.sym_value] = response_finale.head;
					}
					else {
						envmap[naruto_utsumaki->tail.at(0).head.value.sym_value] = naruto_utsumaki->tail.at(1).head;
						response_finale = naruto_utsumaki->tail.at(1);
					}
					naruto_utsumaki->head.type = NoneType;
				}
				else { return false;
				}
			}
			else { return false;
			}
		}
		else { return false;
		}
	}
	else if (bigHead == "begin") {
		naruto_utsumaki->head.type = NoneType;
		if (naruto_utsumaki->tail.size() == 1) {
			response_finale = naruto_utsumaki->tail.at(0);
		}
	}
	return true;
}

bool Environment::procedure_2(Expression* naruto_utsumaki) {
	std::string bigHead = naruto_utsumaki->head.value.sym_value;
 if (bigHead == "if") {
		if (naruto_utsumaki->tail.size() == 3) {
			Expression virtuoza, mocha;
			tortue = envmap.find(naruto_utsumaki->tail.at(1).head.value.sym_value);
			if (tortue == envmap.end() && naruto_utsumaki->tail.at(1).head.type != SymbolType) {	// checks if it's in the map
				virtuoza = naruto_utsumaki->tail.at(1).head;
			}
			else if (tortue != envmap.end()) { virtuoza = tortue->second;
			}
			else { return false;
			}
			tortue = envmap.find(naruto_utsumaki->tail.at(2).head.value.sym_value);
			if (tortue == envmap.end() && naruto_utsumaki->tail.at(2).head.type != SymbolType) {	// checks if it's in the map
				mocha = naruto_utsumaki->tail.at(2).head;
			}
			else if (tortue != envmap.end()) { mocha = tortue->second;
			}
			else { return false;
			}
			if (naruto_utsumaki->tail.at(0).head.type == BooleanType) {
				if (naruto_utsumaki->tail.at(0).head.value.bool_value) { response_finale = virtuoza;
				}
				else { response_finale = mocha;
				}
			}
			else { return false;
			}
		}
		else { return false; }
	}
	return true;
}

bool Environment::procedure_3(Expression* gaara_vs_pain) {
	std::string procedure = gaara_vs_pain->head.value.sym_value;
	for (auto i = 0; i < gaara_vs_pain->tail.size(); i++) {
		if (gaara_vs_pain->tail.at(i).head.type != NumberType) { return false;
		}
	}
	if (procedure == "<") {
		if (gaara_vs_pain->tail.size() == 2) {
			if (gaara_vs_pain->tail.at(0).head.value.num_value < gaara_vs_pain->tail.at(1).head.value.num_value) {
				response_seconde = true;
			}
			else { response_seconde = false;
			}
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	if (procedure == "<=") {
		if (gaara_vs_pain->tail.size() == 2) {
			if (gaara_vs_pain->tail.at(0).head.value.num_value <= gaara_vs_pain->tail.at(1).head.value.num_value) {
				response_seconde = true;
			}
			else {
				response_seconde = false;
			}
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	if (procedure == ">") {
		if (gaara_vs_pain->tail.size() == 2) {
			if (gaara_vs_pain->tail.at(0).head.value.num_value > gaara_vs_pain->tail.at(1).head.value.num_value) {
				response_seconde = true;
			}
			else { response_seconde = false;
			}
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	if (procedure == ">=") {
		if (gaara_vs_pain->tail.size() == 2) {
			if (gaara_vs_pain->tail.at(0).head.value.num_value >= gaara_vs_pain->tail.at(1).head.value.num_value) {
				response_seconde = true;
			}
			else { response_seconde = false;
			}
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	else { return procedure_4(gaara_vs_pain);
	}
	return true;
}

bool Environment::procedure_4(Expression* gaara_vs_pain) {
	std::string procedure = gaara_vs_pain->head.value.sym_value;
	if (procedure == "=") {
		if (gaara_vs_pain->tail.size() == 2) {
			if (gaara_vs_pain->tail.at(0).head.value.num_value == gaara_vs_pain->tail.at(1).head.value.num_value) { response_seconde = true;
			}
			else { response_seconde = false;
			}
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	if (procedure == "+") {
		response_seconde.head.value.num_value = 0;
		for (auto i = 0; i < gaara_vs_pain->tail.size(); i++) {
			response_seconde = response_seconde.head.value.num_value + gaara_vs_pain->tail.at(i).head.value.num_value;
		}
		gaara_vs_pain->tail.clear();
	}
	if (procedure == "-") {
		if (gaara_vs_pain->tail.size() < 3 && !gaara_vs_pain->tail.empty()) {
			if (gaara_vs_pain->tail.size() == 2) {
				response_seconde = gaara_vs_pain->tail.at(0).head.value.num_value - gaara_vs_pain->tail.at(1).head.value.num_value;
			}
			else {
				response_seconde = -1 * gaara_vs_pain->tail.at(0).head.value.num_value;
			}
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	if (procedure == "*") {
		response_seconde.head.value.num_value = 1;
		for (auto i = 0; i < gaara_vs_pain->tail.size(); i++) {
			response_seconde = response_seconde.head.value.num_value * gaara_vs_pain->tail.at(i).head.value.num_value;
		}
		gaara_vs_pain->tail.clear();
	}
	if (procedure == "/") {
		if (gaara_vs_pain->tail.size() == 2) {
			response_seconde = gaara_vs_pain->tail.at(0).head.value.num_value / gaara_vs_pain->tail.at(1).head.value.num_value;
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	if (procedure == "log10") {
		if (gaara_vs_pain->tail.size() == 1) {
			response_seconde = log10(gaara_vs_pain->tail.at(0).head.value.num_value);
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	else { return procedure_5(gaara_vs_pain);
	}
	return true;
}

bool Environment::procedure_5(Expression* gaara_vs_pain) {
	std::string procedure = gaara_vs_pain->head.value.sym_value;
	if (procedure == "pow") {
		if (gaara_vs_pain->tail.size() == 2) {
			response_seconde = pow(gaara_vs_pain->tail.at(0).head.value.num_value, gaara_vs_pain->tail.at(1).head.value.num_value);
			gaara_vs_pain->tail.clear();
		}
		else { return false;
		}
	}
	return true;
}
