#include "stdafx.h"
#include "deterministic_finite_automata.h"

#include <stack>
#include <map>
#include <set>

using namespace std;

bool deterministic_finite_automata::match(char* c)
{
	int state = 0;
	while (*c != '\0')
	{
		bool found = false;
		for (vector<pair<char, int>>::iterator link_iterator = this->adjacency_list[state].begin(); link_iterator != this->adjacency_list[state].end(); link_iterator++)
		{
			if (link_iterator->first == *c)
			{
				found = true;
				state = link_iterator->second;
				break;
			}
		}

		if (!found)
		{
			return false;
		}
		c++;
	}

	for (vector<int>::iterator i = this->final_states.begin(); i != this->final_states.end(); i++)
	{
		if (*i == state)
		{
			return true;
		}
	}

	return false;
}