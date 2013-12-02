#ifndef __union_regular_expression_H__
#define __union_regular_expression_H__

#include "regular_expression.h"
#include "non_deterministic_finite_automata.h"

class union_regular_expression : public regular_expression
{
public:
	union_regular_expression(const regular_expression& first, const regular_expression& second);
	virtual non_deterministic_finite_automata to_non_deterministic_finite_automata() const;
private:
	const regular_expression& first;
	const regular_expression& second;
};

#endif
