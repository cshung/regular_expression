#ifndef __CONCATENATEREGULAREXPRESSION_H__
#define __CONCATENATEREGULAREXPRESSION_H__

#include "regular_expression.h"

class concatenation_regular_expression : public regular_expression
{
public:
	concatenation_regular_expression(const regular_expression& first, const regular_expression& second);
	virtual non_deterministic_finite_automata to_non_deterministic_finite_automata() const;
private:
	const regular_expression& first;
	const regular_expression& second;
};

#endif
