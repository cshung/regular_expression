#ifndef __character_regular_expression_H__
#define __character_regular_expression_H__

#include "regular_expression.h"

class character_regular_expression : public regular_expression
{
public:
	character_regular_expression(char c);
	virtual non_deterministic_finite_automata to_non_deterministic_finite_automata() const;
private:
	char c;
};

#endif
