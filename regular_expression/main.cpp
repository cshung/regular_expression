// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>

#include "regular_expression.h"
#include "character_regular_expression.h"
#include "concatenation_regular_expression.h"
#include "iteration_regular_expression.h"
#include "union_regular_expression.h"
#include "non_deterministic_finite_automata.h"
#include "deterministic_finite_automata.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	/* (p+q)*p */
	character_regular_expression a('p');
	character_regular_expression b('q');
	character_regular_expression c('p');
	union_regular_expression d(a, b);
	iteration_regular_expression e(d);
	concatenation_regular_expression f(e, c);
	deterministic_finite_automata dfa = f.to_non_deterministic_finite_automata().to_deterministic_finite_automata();
	cout << "adjacency list:" << endl;
	int index = 0;
	for (vector<vector<pair<char, int>>>::iterator i = dfa.adjacency_list.begin(); i != dfa.adjacency_list.end(); i++)
	{
		cout << index << ": ";
		for (vector<pair<char, int>>::iterator j = i->begin(); j != i->end(); j++)
		{
			cout << "(" << j->first << "->" << j->second << ")" << ", ";
		}
		cout << endl;
		index++;
	}
	cout << "final states:" << endl;
	for (vector<int>::iterator final_states_iterator = dfa.final_states.begin(); final_states_iterator != dfa.final_states.end(); final_states_iterator++)
	{
		cout << *final_states_iterator << ", ";
	}
	cout << endl;

	cout << dfa.match("p") << endl;
	cout << dfa.match("pp") << endl;
	cout << dfa.match("qp") << endl;

	cout << dfa.match("q") << endl;
	cout << dfa.match("r") << endl;
}

