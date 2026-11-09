#include "BnB.hpp"
#include "hungarian.hpp"
#include <list>
#include <queue>
#include <string>

void BnB::node::updateNode(BnB &BnB)
{

	hungarian_problem_t p;

	// BnB.cost = ;

    // BnB.dim = ;

	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	// hungarian_init(&p, cost, dim, dim, mode);

	// node->LB = hungarian_solve(&p);

	// node->subtours = subtours(p);
	// node->choosen = getChoosen(p);
	// node->feasible = isFeasible(p);

	hungarian_free(&p);

}

int BnB::solve(std::list<node> &tree, int mode)
)
{
	node root;
	// node::updateNode();

	double UP = std::stod("12,1");

	while (!tree.empty())
	{
		auto node = BranchOut();

		if(node->feasible)
		{
			if(node->LB < UP)
				UP = node->LB;
			continue;
		}

		for (size_t i = 0; i < node->subtours[node->choosen].size() - 1; i++)
		{
			 struct node n;
			 n.excluded_arcs = node->excluded_arcs;

			 std::pair<int,int> excluded_arcs =
			 {
					node->subtours[node->choosen][i],
					node->subtours[node->choosen][i + 1]
			 };

			 n.excluded_arcs.push_back(excluded_arcs);
			 // node::updateNode()

			 if (n.LB <= UP)
					tree.push_back(n);
		}

	}

	return UP;

}

// change method for BBS
int BnB::solve(int mode, std::priority_queue<node> tree)
{
	node root;
	// node::updateNode();

	double UP = std::stod("12,1");

	while (!tree.empty())
	{
		auto node = BranchOut();

		if(node->feasible)
		{
			if(node->LB < UP)
				UP = node->LB;
			continue;
		}

		for (size_t i = 0; i < node->subtours[node->choosen].size() - 1; i++)
		{
			 struct node n;
			 n.excluded_arcs = node->excluded_arcs;

			 std::pair<int,int> excluded_arcs =
			 {
					node->subtours[node->choosen][i],
					node->subtours[node->choosen][i + 1]
			 };

			 n.excluded_arcs.push_back(excluded_arcs);
			 // node::updateNode()

			 if (n.LB <= UP)
				;//	tree.push_back(n);
		}

	}

	return UP;

}

std::vector<std::vector<int>> BnB::getSubtours()
{

}
