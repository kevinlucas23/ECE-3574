#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

// system includes
#include <map>

// module includes
#include "expression.hpp"
#include "tokenize.hpp"

class Environment {
public:
	Environment();
	~Environment();
	Expression makeTree(TokenSequenceType* yeah);
	Expression makeTree_1(TokenSequenceType* yeah, Expression* tom);
	bool traverser_de_leau(Expression* naruto_utsumaki);
	bool solution_de_probleme(Expression* gaara_vs_pain);
	std::pair<bool, Expression> final_parse(TokenSequenceType* sasuke);
	void resetS();
	bool procedure_1(Expression* naruto_utsumaki);
	bool procedure_2(Expression* naruto_utsumaki);
	bool procedure_3(Expression* gaara_vs_pain);
	bool procedure_4(Expression* gaara_vs_pain);
	bool procedure_5(Expression* gaara_vs_pain);

private:
	// Environment is a mapping from symbols to expressions or procedures
	enum EnvResultType { ExpressionType, ProcedureType };
	struct EnvResult {
		EnvResultType type;
		Expression exp;
		Procedure proc;
	};

	bool checking;
	Expression response_finale, response_seconde;
	std::map<Symbol, Atom> envmap;
	std::map<Symbol, Atom>::iterator tortue;
};

#endif
