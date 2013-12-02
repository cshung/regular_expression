#include "stdafx.h"
#include "union_regular_expression.h"

union_regular_expression::union_regular_expression(const regular_expression& first, const regular_expression& second) : first(first), second(second) 
{ 
}

non_deterministic_finite_automata union_regular_expression::to_non_deterministic_finite_automata() const
{
	// s -e->s1-...->f1-e->f
	// s -e->s2-...->f2-e->f

	non_deterministic_finite_automata first_result = first.to_non_deterministic_finite_automata();
	non_deterministic_finite_automata second_result = second.to_non_deterministic_finite_automata();
	non_deterministic_finite_automata result;

	// Step 1: Create the start node
	result.adjacency_list.push_back(vector<pair<char, int>>());

	// Step 2: Copy the first result (all node indexes += 1)
	int index = 1;
	for (vector<vector<pair<char, int>>>::iterator first_iterator = first_result.adjacency_list.begin(); first_iterator != first_result.adjacency_list.end(); first_iterator++)
	{
		result.adjacency_list.push_back(vector<pair<char, int>>());
		for (vector<pair<char, int>>::iterator first_next_iterator = first_iterator->begin(); first_next_iterator != first_iterator->end(); first_next_iterator++)
		{
			result.adjacency_list[index].push_back(pair<char,int>(first_next_iterator->first, first_next_iterator->second+1));
		}
		index++;
	}

	// Step 3: Copy the second result (all node indexes += offset)
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

	// Step 4: Create the end node
	result.adjacency_list.push_back(vector<pair<char, int>>());

	// Step 5: Build the start epsilon links
	result.adjacency_list[0].push_back(pair<char, int>('\0', 1));
	result.adjacency_list[0].push_back(pair<char, int>('\0', offset));
	result.adjacency_list[offset-1].push_back(pair<char, int>('\0', index));
	result.adjacency_list[index-1].push_back(pair<char, int>('\0', index));

	return result;
}
