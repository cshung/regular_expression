#ifndef __iteration_regular_expression_H__
#define __iteration_regular_expression_H__

#include "regular_expression.h"

class iteration_regular_expression : public regular_expression
{
public:
	iteration_regular_expression(const regular_expression& first);
	virtual non_deterministic_finite_automata to_non_deterministic_finite_automata() const;
private:
	const regular_expression& first;
};

#endif
