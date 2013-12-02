#ifndef __NFA_H__
#define __NFA_H__

#include <vector>
#include <map>
#include <set>
using namespace std;

#include "deterministic_finite_automata.h"

// The start state is 0, implicitly
// The end state is the maximum index, implicitly
class non_deterministic_finite_automata
{
public:
	vector<vector<pair<char, int>>> adjacency_list;
	deterministic_finite_automata to_deterministic_finite_automata();
private:
	set<int> epsilon_closure(set<int> input_set);
};

#endif
