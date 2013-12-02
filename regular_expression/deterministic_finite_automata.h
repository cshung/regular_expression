#ifndef __DETERMINISTIC_FINITE_AUTOMATA_H__
#define __DETERMINISTIC_FINITE_AUTOMATA_H__

#include <vector>
using namespace std;

// The start state is 0, implicitly
class deterministic_finite_automata
{
public:
	vector<vector<pair<char, int>>> adjacency_list;
	vector<int> final_states;
	bool match(char* c);
};

#endif
