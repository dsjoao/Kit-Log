#pragma once

#include "Data.hpp"
#include "hungarian.hpp"
#include <list>
#include <queue>
#include <utility>
#include <vector>

struct node
	{
		std::vector<std::pair<int, int>> excluded_arcs;
		std::vector<std::vector<int>> subtours;

		double LB;
		int choosen;
		bool feasible;

	};

class BnB
{

	double **cost;
	int dim;

	public:

	void updateNode(node *node);

	int solve(int mode, std::list<node>);
	int solve(int mode, std::priority_queue<node>);

	std::vector<std::vector<int>> getSubtours();
	std::pair<int, int> getChosen();
	bool isFeasible();



	node* BranchOut();

};
