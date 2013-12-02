#ifndef __REGULAR_EXPRESSION_H__
#define __REGULAR_EXPRESSION_H__

#include "non_deterministic_finite_automata.h"

class regular_expression
{
public:
	virtual non_deterministic_finite_automata to_non_deterministic_finite_automata() const = 0;
};

#endif
