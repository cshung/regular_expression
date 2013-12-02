#include "stdafx.h"
#include "character_regular_expression.h"

character_regular_expression::character_regular_expression(char c)
{	
	this->c = c; 
}

non_deterministic_finite_automata character_regular_expression::to_non_deterministic_finite_automata() const
{
	// 0 -c-> 1
	non_deterministic_finite_automata result;
	result.adjacency_list.push_back(vector<pair<char, int>>());
	result.adjacency_list.push_back(vector<pair<char, int>>());
	result.adjacency_list[0].push_back(pair<char, int>(c, 1));
	return result;
}
