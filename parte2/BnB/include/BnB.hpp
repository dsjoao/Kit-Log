#pragma once

#include "Data.hpp"
#include "hungarian.hpp"
#include "ILS.hpp"
#include <queue>
#include <stack>
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

		bool operator>(const node &node) const;
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
	TSP_ILS *heuristic = NULL;

	BnB(Data data_, hungarian_problem_t &p_, int mode);

	void updateNode(node *node);

	int solve();
	int solve(std::priority_queue<node> &tree);
	int solve(std::stack<node> &tree);
	int solve(std::queue<node> &tree);

	std::vector<std::vector<int>> getSubtours();
	int getChoosen(node *node);
	bool isFeasible(node *node);

	node* BranchOut();

};
