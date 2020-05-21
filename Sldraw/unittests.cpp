#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

//TODO: add your unit tests here
#include "interpreter_semantic_error.hpp"
#include "interpreter.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include"tokenize.hpp"

Expression go_gone(const std::string& program) {
	std::istringstream iss(program);

	Interpreter interp;

	bool ok = interp.parse(iss);
	if (!ok) {
		std::cerr << "Failed to parse: " << program << std::endl;
	}
	REQUIRE(ok == true);

	Expression result;
	REQUIRE_NOTHROW(result = interp.eval());

	return result;
}

void not_go_gone(const std::string& program) {
	std::istringstream iss(program);

	Interpreter interp;

	bool ok = interp.parse(iss);
	REQUIRE(ok == false);
}

Expression semantic_err(const std::string& program) {

	std::istringstream iss(program);
	Interpreter interp;
	interp.parse(iss);
	Expression result;
	REQUIRE_THROWS_AS(result = interp.eval(), InterpreterSemanticError);
	return Expression();
}

TEST_CASE("error 1", "[interpreter]") {
		std::string program = "(= 5 5 5 5)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 2", "[interpreter]") {
		std::string program = "(= 2 1 4 true)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 3", "[interpreter]") {
		std::string program = "(= 1 2 4 true)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 4", "[interpreter]") {
		std::string program = "(= 6 3 3 what)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 5", "[interpreter]") {
		std::string program = "(= 2 3 4 yx)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 6", "[interpreter]") {
		std::string program = "(= 2 2 2 sup)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 7", "[interpreter]") {
		std::string program = "(= 3 3 2)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 8", "[interpreter]") {
		std::string program = "(>= 4 3 5)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 9", "[interpreter]") {
		std::string program = "(= 1 a)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 10", "[interpreter]") {
		std::string program = "(>= 5 b)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 11", "[interpreter]") {
		std::string program = "(<= 4 6 4)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 12", "[interpreter]") {
		std::string program = "(<= 4 b)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 13", "[interpreter]") {
		std::string program = "(< 2 7 4)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 14", "[interpreter]") {
		std::string program = "(< 5 a)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 15", "[interpreter]") {
		std::string program = "(> 2 3 4)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 16", "[interpreter]") {
		std::string program = "(> 5 d)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 17", "[interpreter]") {
		std::string program = "(* 1 6 true)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 18", "[interpreter]") {
		std::string program = "(/ 1 5 true)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 19", "[interpreter]") {
		std::string program = "(log10 5 3 true)";
		Expression result = semantic_err(program);
}
TEST_CASE("error 20", "[interpreter]") {
		std::string program = "(point 3 false)";
		Expression result = semantic_err(program);
}

TEST_CASE("Test for logic ", "[interpreter]")
{
	{ // not, unary case
		std::string program = "(begin (define a False) (not a))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(true));
	}

	{ // and, binary case
		std::string program = "(begin (define a True) (define b False) (and a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(false));
	}

	{ // and, mary case
		std::string program = "(and True True True false True)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(false));
	}

	{ // or, binary case
		std::string program = "(begin (define a True) (define b False) (or a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(true));
	}

	{ // or, mary case
		std::string program = "(or True True True false True)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(true));
	}
}

TEST_CASE("Test for comparison operations", "[interpreter]")
{
	{ // less than, binary case
		std::string program = "(begin (define a 7) (define b 8) (< a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(true));
	}

	{ // less than or equal, binary case
		std::string program = "(begin (define a 7) (define b 8) (<= a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(true));
	}

	{ // greater than, binary case
		std::string program = "(begin (define a 7) (define b 8) (> a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(false));
	}

	{ // greater than or equal, binary case
		std::string program = "(begin (define a 7) (define b 8) (>= a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(false));
	}

	{ // equal, binary case
		std::string program = "(begin (define a 7) (define b 8) (= a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(false));
	}

	{ // equal, binary case
		std::string program = "(begin (define a 8) (define b 8) (= a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(true));
	}
}

TEST_CASE("Test for adds operations", "[interpreter]")
{
	{ // add, binary case
		std::string program = "(+ 1 2)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(3.));
	}

	{ // add, 3-ary case
		std::string program = "(+ 1 2 3)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(6.));
	}

	{ // add, 6-ary case
		std::string program = "(+ 1 2 3 4 5 6)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(21.));
	}

	{ // minus, single case
		std::string program = "(- 1)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(-1.));
	}

	{ // minus, binary case
		std::string program = "(- 1 2)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(-1.));
	}

	{ // multiply, binary case
		std::string program = "(* 78 45)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(3510.));
	}

	{ // multiply,6-ary case
		std::string program = "(* 1 2 3 4 5 6)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(720.));
	}

	{ // divide, binary case
		std::string program = "(/ 67.5 45)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(1.5));
	}
}

TEST_CASE("Test for logarithm expression", "[interpreter]")
{
	{ // log10, unary case
		std::string program = "(log10 1000)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(3.));
	}

	{ // power, binary case
		std::string program = "(pow 48 3)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(110592.));
	}
}

TEST_CASE("Test Interpreter parser literals", "[interpreter]") {
	std::vector<std::string> programs = { "(1)", "(+1)", "(+1e+0)", "(1e-0)" };

	for (auto program : programs) {
		std::istringstream iss(program);

		Interpreter interp;

		bool ok = interp.parse(iss);

		REQUIRE(ok == true);
	}
}

TEST_CASE("Test Interpreter parser input", "[interpreter]") {
	std::string program = "(begin (define r 10) (* pi (* r r)))";

	std::istringstream iss(program);

	Interpreter interp;

	bool ok = interp.parse(iss);

	REQUIRE(ok == true);
}

TEST_CASE("Test Interpreters expressions", "[interpreter]") {
	{ // Boolean True
		std::string program = "(True)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(true));
	}

	{ // Boolean False
		std::string program = "(False)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(false));
	}

	{ // Number
		std::string program = "(4)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(4.));
	}

	{ // Symbol
		std::string program = "(pi)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(atan2(0, -1)));
	}
}

TEST_CASE("Test Interpreter result with simple (add)", "[interpreter]") {
	{ // add, binary case
		std::string program = "(+ 1 2)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(3.));
	}

	{ // add, 3-ary case
		std::string program = "(+ 1 2 3)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(6.));
	}

	{ // add, 6-ary case
		std::string program = "(+ 1 2 3 4 5 6)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(21.));
	}
}

TEST_CASE("Test Interpreter special form of if", "[interpreter]") {
	{
		std::string program = "(if True (4) (-4))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(4.));
	}

	{
		std::string program = "(if False (4) (-4))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(-4.));
	}
}

TEST_CASE("Test Interpreter special forms of begin and define", "[interpreter]") {
	{
		std::string program = "(define answer 42)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(42.));
	}

	{
		std::string program = "(begin (define answer 42)\n(answer))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(42.));
	}

	{
		std::string program = "(begin (define answer (+ 9 11)) (answer))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(20.));
	}

	{
		std::string program = "(begin (define a 1) (define b 1) (+ a b))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(2.));
	}
}

TEST_CASE("Test a extreme complex expression", "[interpreter]") {
	{
		std::string program = "(+ (+ 10 1) (+ 30 (+ 1 1)))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(43.));
	}
}

TEST_CASE("Test for a very complex expression", "[interpreter]") {
	{
		std::string program = "( define a (if (> 8 9) (and true false false true false) (- 185 ( / 16200 (+ 7 8 9 10 11 45)))))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(5.));
	}
}

TEST_CASE("Test bad exp", "[interpreter]") {
	{
		std::string program = "(begin (define a 7) (*";
		not_go_gone(program);
	}
}

TEST_CASE("Test bad string", "[interpreter]") {
	{
		std::string program = "(f";
		not_go_gone(program);
	}
}

TEST_CASE("Test bad inp", "[interpreter]") {
	{
		std::string program = "( * 4 3) (+ 4 2)";
		not_go_gone(program);
	}
}

TEST_CASE("Test empty tokenized", "[interpreter]") {
	{
		std::string program = "( )";
		not_go_gone(program);
	}
}

TEST_CASE("Test bad tokenize", "[interpreter]") {
	{
		std::string program = "(1abc)";
		not_go_gone(program);
	}
}

TEST_CASE("Test none tokens", "[interpreter]") {
	{
		std::string program = "(@ none)";
		not_go_gone(program);
	}
}

TEST_CASE("Test none input", "[interpreter]") {
	{
		std::string program = "hello";
		not_go_gone(program);
	}

	{
		std::string program = "Yakima";
		not_go_gone(program);
	}
}

TEST_CASE("Test none comment", "[interpreter]") {
	{
		std::string program = ";comment testing if it works\n";
		not_go_gone(program);
	}
}

TEST_CASE("Test good comment", "[interpreter]") {
	{
		std::string program = ";comment testing if it works\n";
		program += "(begin (define answer (+ 9 11)) (answer))";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(20.));
	}
}

TEST_CASE("Test good trying", "[interpreter]") {
	{
		std::string program = ";comment testing if it works\n";
		program += "(or false false)";
		Expression result = go_gone(program);
		REQUIRE(result == Expression(false));
	}
}

TEST_CASE("Test Tokenized  input", "[tokenize]") {
	std::string program = "(begin (define r 10) (* pi (* r r)))";

	std::istringstream iss(program);

	TokenSequenceType tokens = tokenize(iss);

	REQUIRE(tokens.size() == 17);
	REQUIRE(tokens[0] == "(");
	REQUIRE(tokens[1] == "begin");
	REQUIRE(tokens[2] == "(");
	REQUIRE(tokens[3] == "define");
	REQUIRE(tokens[4] == "r");
	REQUIRE(tokens[5] == "10");
	REQUIRE(tokens[6] == ")");
	REQUIRE(tokens[7] == "(");
	REQUIRE(tokens[8] == "*");
	REQUIRE(tokens[9] == "pi");
	REQUIRE(tokens[10] == "(");
	REQUIRE(tokens[11] == "*");
	REQUIRE(tokens[12] == "r");
	REQUIRE(tokens[13] == "r");
	REQUIRE(tokens[14] == ")");
	REQUIRE(tokens[15] == ")");
	REQUIRE(tokens[16] == ")");
}

TEST_CASE("Test ok", "[types]") {
	Atom a;

	std::string token = "True";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == BooleanType);
	REQUIRE(a.value.bool_value == true);

	token = "False";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == BooleanType);
	REQUIRE(a.value.bool_value == false);

	token = "1";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == 1);

	token = "-1";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == -1);

	token = "var";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == SymbolType);
	REQUIRE(a.value.sym_value == "var");

	token = "1abc";
	REQUIRE(!token_to_atom(token, a));

	token = "var1";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == SymbolType);
	REQUIRE(a.value.sym_value == token);
}
