#include <fstream>
#include<string>
#include<cstdlib>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include <algorithm>
#include <functional>
#include <sstream>

#include "interpreter.hpp"
#include "interpreter_semantic_error.hpp"

bool try_it(Interpreter* interp, std::istream& expression);

int main(int argc, char** argv) {
	Interpreter interp;
	std::vector<std::string> cmdk; 	//input all commands into the vector.
	for (int i = 0; i < argc; i++) {
		cmdk.push_back(std::string(argv[i]));
	}
	if (cmdk.size() == 1) {
		std::string test;
		while (true) {
			std::cout << "slisp> ";
			int go = std::cin.peek();
			if (go == EOF) {
				std::cout << "\n";
				exit(EXIT_SUCCESS);
			}
			std::getline(std::cin, test);
			std::istringstream iss(test);
			if (!test.empty()) {
				try_it(&interp, iss);
			}
		}
	}
	else if (cmdk.at(1) == "-e") {
		if (cmdk.size() > 3) {
			std::cout << "Error: wrong input argument" << std::endl;
			return EXIT_FAILURE;
		}
		std::istringstream iss(cmdk.at(2));
		if (!try_it(&interp, iss)) {
			return EXIT_FAILURE;
		}
	}
	else if (cmdk.size() == 2) {
		std::ifstream file;
		file.open(cmdk.at(1));
		if (file.fail() || file.peek() == std::ifstream::traits_type::eof())
		{
			std::cout << "Error: wrong file" << std::endl;
			return EXIT_FAILURE;
		}
		std::string kabo, test;
		if (file.is_open()) {
			while (std::getline(file, test)) {
				kabo.append((test + "\n"));
			}
		}
		std::istringstream iss(kabo);
		if (!try_it(&interp, iss)) {
			return EXIT_FAILURE;
		}
	}
	else {
		std::cout << "Error: try new input" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool try_it(Interpreter* interp, std::istream& expression) {
	interp->parse(expression);
	try {
		interp->eval();
		interp->ontheGo();
	}
	catch (InterpreterSemanticError & e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}