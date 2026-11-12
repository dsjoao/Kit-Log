#pragma once

#include "Data.hpp"
#include "hungarian.hpp"
#include <list>
#include <queue>
#include <utility>
#include <vector>
#include <cassert>

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


    public:


	double **cost;
	int **assig;
	int dim;
	int Bstrat = 0;
	hungarian_problem_t *p = NULL;
	Data *data = NULL;

	BnB(Data data_, hungarian_problem_t &p_, int mode);


	void updateNode(node *node);

	int solve(int mode);
	int solve(std::priority_queue<node> &tree);
	int solve(std::list<node> &tree, int mode);

	std::vector<std::vector<int>> getSubtours();
	std::vector<int> formSubtour(int begin, int end);

	std::pair<int, int> getChosen();
	bool isFeasible();

	node* BranchOut();

};
