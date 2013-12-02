#include "stdafx.h"
#include "non_deterministic_finite_automata.h"

#include <stack>
#include <map>
#include <set>

using namespace std;

deterministic_finite_automata non_deterministic_finite_automata::to_deterministic_finite_automata()
{
	deterministic_finite_automata result;
	// Step 1: Computing epsilon closure of the start node to begin the algorithm
	set<int> start;
	start.insert(0);
	map<set<int>, int> nfa_nodes_to_index;
	map<int, set<int>> index_to_nfa_nodes;
	set<int> start_node = epsilon_closure(start);

	int node_index = nfa_nodes_to_index.size();
	nfa_nodes_to_index.insert(pair<set<int>, int>(start_node, node_index));
	index_to_nfa_nodes.insert(pair<int, set<int>>(node_index, start_node));

	// Now perform a DFS on the implicit DFA graph to complete the conversion
	stack<int> stack;
	stack.push(0);
	vector<pair<int,pair<char, int>>> links;
	while (stack.size() > 0)
	{	
		int visiting = stack.top();
		stack.pop();

		// Step 1: Find all the outgoing neighbors
		map<char, set<int>> outgoing_neighbors;
		// For each nodes
		for (set<int>::iterator nfa_node_iterator = index_to_nfa_nodes[visiting].begin(); nfa_node_iterator != index_to_nfa_nodes[visiting].end(); nfa_node_iterator++)
		{
			// Find all outgoing links
			for (vector<pair<char, int>>::iterator links_iterator = this->adjacency_list[*nfa_node_iterator].begin(); links_iterator != this->adjacency_list[*nfa_node_iterator].end(); links_iterator++)
			{
				// We are only interested in non epsilon links for now
				if (links_iterator->first != '\0')
				{
					// Save the neighbor
					map<char, set<int>>::iterator found = outgoing_neighbors.find(links_iterator->first);
					if (found == outgoing_neighbors.end())
					{
						set<int> empty;
						outgoing_neighbors.insert(pair<int, set<int>>(links_iterator->first, empty));
					}

					outgoing_neighbors[links_iterator->first].insert(links_iterator->second);
				}
			}
		}

		// Step 2: Compute the epsilon closure for the neighbors and record all found edges
		for (map<char, set<int>>::iterator outgoing_neighbors_iterator = outgoing_neighbors.begin(); outgoing_neighbors_iterator != outgoing_neighbors.end(); outgoing_neighbors_iterator++)
		{
			set<int> outgoing_neighbors_epsilon_closure = epsilon_closure(outgoing_neighbors_iterator->second);

			// Step 3: Check if the node set is seen before
			map<set<int>, int>::iterator found = nfa_nodes_to_index.find(outgoing_neighbors_epsilon_closure);
			if (found == nfa_nodes_to_index.end())
			{				
				// If not - push to stack for further processing
				int outgoing_neighbors_epsilon_closure_node_index = nfa_nodes_to_index.size();
				links.push_back(pair<int,pair<char, int>>(visiting, pair<char, int>(outgoing_neighbors_iterator->first, outgoing_neighbors_epsilon_closure_node_index)));
				nfa_nodes_to_index.insert(pair<set<int>, int>(outgoing_neighbors_epsilon_closure, outgoing_neighbors_epsilon_closure_node_index));
				index_to_nfa_nodes.insert(pair<int, set<int>>(outgoing_neighbors_epsilon_closure_node_index, outgoing_neighbors_epsilon_closure));

				// Push into DFS stack
				stack.push(outgoing_neighbors_epsilon_closure_node_index);
			}
			else 
			{
				// Otherwise just record the link
				links.push_back(pair<int,pair<char, int>>(visiting, pair<char, int>(outgoing_neighbors_iterator->first, found->second)));
			}
		}
	}

	// Step 3: Generate the output
	for (int i = 0; i < nfa_nodes_to_index.size(); i++)
	{
		result.adjacency_list.push_back(vector<pair<char, int>>());
	}

	for (vector<pair<int,pair<char, int>>>::iterator links_iterator = links.begin(); links_iterator != links.end(); links_iterator++)
	{
		result.adjacency_list[links_iterator->first].push_back(links_iterator->second);
	}

	for (map<int, set<int>>::iterator index_to_nfa_nodes_iterator = index_to_nfa_nodes.begin(); index_to_nfa_nodes_iterator != index_to_nfa_nodes.end(); index_to_nfa_nodes_iterator++)
	{
		if (index_to_nfa_nodes_iterator->second.find(index_to_nfa_nodes.size()-1) != index_to_nfa_nodes_iterator->second.end())
		{
			result.final_states.push_back(index_to_nfa_nodes_iterator->first);
		}
	}

	return result;
}

set<int> non_deterministic_finite_automata::epsilon_closure(set<int> input_set)
{
	set<int> solution;
	stack<int> stack;
	set<int> pushed;
	for (set<int>::iterator input_iterator = input_set.begin(); input_iterator != input_set.end(); input_iterator++)
	{
		pushed.insert(*input_iterator);
		stack.push(*input_iterator);
	}

	while (stack.size() > 0)
	{
		int visiting = stack.top();
		stack.pop();
		solution.insert(visiting);

		for (vector<pair<char, int>>::iterator links_iterator = this->adjacency_list[visiting].begin(); links_iterator != this->adjacency_list[visiting].end(); links_iterator++)
		{
			if (links_iterator->first == '\0')
			{
				if (pushed.find(links_iterator->second) == pushed.end()) /* i.e. the node is not pushed */
				{
					pushed.insert(links_iterator->second);
					stack.push(links_iterator->second);
				}
			}
		}
	}

	return solution;
}
