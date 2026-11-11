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

<<<<<<< HEAD
=======
    public:

>>>>>>> 4fd933d95749c6796ca4bf8c63af0aa44e8d984e
	double **cost;
	double **assig;
	int dim;
	int Bstrat = 0;
	hungarian_problem_t *p = NULL;
	Data *data = NULL;

<<<<<<< HEAD
	public:

	BnB(Data data_, hungarian_problem_t p_, int mode);
=======

	BnB(Data data_, hungarian_problem_t &p_, int mode);
>>>>>>> 4fd933d95749c6796ca4bf8c63af0aa44e8d984e

	void updateNode(node *node);

	int solve(int mode);
	int solve(std::priority_queue<node> &tree);
	int solve(std::list<node> &tree, int mode);

	std::vector<std::vector<int>> getSubtours();
	std::pair<int, int> getChosen();
	bool isFeasible();



	node* BranchOut();

};
