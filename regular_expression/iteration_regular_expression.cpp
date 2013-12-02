#include "stdafx.h"
#include "iteration_regular_expression.h"

iteration_regular_expression::iteration_regular_expression(const regular_expression& first) : first(first)
{
}

non_deterministic_finite_automata iteration_regular_expression::to_non_deterministic_finite_automata() const
{
	// s0-...->f0
	// f0-e->s
	// s-e->f
	// This is slightly different from lecture - this is implementation specific - with that I can always assume the last node is the end node

	non_deterministic_finite_automata first_result = first.to_non_deterministic_finite_automata();	
	non_deterministic_finite_automata result;

	int index = 0;
	for (vector<vector<pair<char, int>>>::iterator first_iterator = first_result.adjacency_list.begin(); first_iterator != first_result.adjacency_list.end(); first_iterator++)
	{
		result.adjacency_list.push_back(vector<pair<char, int>>());
		for (vector<pair<char, int>>::iterator first_next_iterator = first_iterator->begin(); first_next_iterator != first_iterator->end(); first_next_iterator++)
		{
			result.adjacency_list[index].push_back(pair<char,int>(first_next_iterator->first, first_next_iterator->second));
		}
		index++;
	}

	result.adjacency_list.push_back(vector<pair<char, int>>());
	result.adjacency_list[0].push_back(pair<char,int>('\0', index));
	result.adjacency_list[index-1].push_back(pair<char,int>('\0', 0));

	return result;
}
