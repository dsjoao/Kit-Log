#pragma once

#include "Data.hpp"
#include "hungarian.hpp"
#include <queue>
#include <stack>
#include <utility>
#include <vector>
#include <cassert>

struct Node
	{
		std::vector<std::pair<int, int>> excluded_arcs;
		std::vector<std::vector<int>> subtours;

		double LB;
		int choosen;
		bool feasible;

		bool operator<(const Node &node) const;
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
	int heuristic;

	BnB(Data& data_, hungarian_problem_t &p_, int modeHung, int modeBnB, int heuristic);

	void updateNode(Node *node);

	int solve();
	int solve(std::priority_queue<Node> &tree);
	int solve(std::stack<Node> &tree);
	int solve(std::queue<Node> &tree);

	std::vector<std::vector<int>> getSubtours(hungarian_problem_t *p);
	int getChoosen(Node *node);
	bool isFeasible(Node *node);

	Node* BranchOut();

};
