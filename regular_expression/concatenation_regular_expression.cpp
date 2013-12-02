#include "stdafx.h"
#include "concatenation_regular_expression.h"

concatenation_regular_expression::concatenation_regular_expression(const regular_expression& first, const regular_expression& second) : first(first), second(second)
{ 

}

non_deterministic_finite_automata concatenation_regular_expression::to_non_deterministic_finite_automata() const
{
	// s0 -...-> f0 -e-> s1 -...-> f1
	non_deterministic_finite_automata first_result = first.to_non_deterministic_finite_automata();
	non_deterministic_finite_automata second_result = second.to_non_deterministic_finite_automata();

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
	result.adjacency_list[index-1].push_back(pair<char,int>('\0', index));
	int offset = index;
	for (vector<vector<pair<char, int>>>::iterator second_iterator = second_result.adjacency_list.begin(); second_iterator != second_result.adjacency_list.end(); second_iterator++)
	{
		result.adjacency_list.push_back(vector<pair<char, int>>());
		for (vector<pair<char, int>>::iterator second_next_iterator = second_iterator->begin(); second_next_iterator != second_iterator->end(); second_next_iterator++)
		{
			result.adjacency_list[index].push_back(pair<char,int>(second_next_iterator->first, second_next_iterator->second + offset));
		}
		index++;
	}

	return result;
}
