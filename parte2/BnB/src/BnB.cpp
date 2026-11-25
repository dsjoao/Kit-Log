#include "BnB.hpp"
#include "hungarian.hpp"
#include <cassert>
#include <cstring>
#include <queue>
#include <set>
#include <stack>
#include <vector>

BnB::BnB(Data& data_, hungarian_problem_t &p_, int modeHung, int modeBnB, int heuristic) {
  this->data = &data_;
  this->heuristic = heuristic;

  assert((this->data != NULL) && "erro iniciando data");

  this->data->read();

  this->dim = data->getDimension();

  this->cost = new double *[dim];
  for (int i = 0; i < dim; i++) {
    cost[i] = new double[dim];
    for (int j = 0; j < dim; j++) {
      cost[i][j] = data->getDistance(i + 1, j + 1);
    }
  }

  this->Bstrat = modeBnB;

}


void BnB::updateNode(Node *node) {

  hungarian_problem_t p;

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      this->cost[i][j] = data->getDistance(i + 1, j + 1);
    }
  }

  for (auto &var : node->excluded_arcs)
      this->cost[var.first - 1][var.second - 1] = 99999999;


  int mode = HUNGARIAN_MODE_MINIMIZE_COST;
  hungarian_init(&p, this->cost, this->dim, this->dim, mode);

  node->LB = hungarian_solve(&p);

  node->subtours = getSubtours(&p);
  node->choosen  = getChoosen(node);
  node->feasible = isFeasible(node);

  hungarian_free(&p);
}

int BnB::solve()
{
  if (this->Bstrat == 0)
  {
      std::priority_queue<Node> tree;
      return this->solve(tree);
  }
  else if(this->Bstrat == 1)
  {
      std::stack<Node> tree;
    return this->solve(tree);
  }
  else if(this->Bstrat == 2)
  {
      std::queue<Node> tree;
      return this->solve(tree);
  }

  return 0;

}

int BnB::solve(std::queue<Node> &tree) {
  Node root;
  updateNode(&root);

  tree.push(root);
  double UP = this->heuristic + 1;

  while (!tree.empty()) {
    auto node = tree.front();
    tree.pop();


    if (node.feasible)
    {
      if (node.LB < UP)
        UP = node.LB;
      continue;
    }

    for (size_t i = 0; i < node.subtours[node.choosen].size() - 1; i++) {
        Node n = node;
      n.excluded_arcs = node.excluded_arcs;

      std::pair<int, int> excluded_arcs = {
          node.subtours[node.choosen][i],
          node.subtours[node.choosen][i + 1]};

      n.excluded_arcs.push_back(excluded_arcs);
      updateNode(&n);

      if (n.LB <= UP)
        tree.push(n);
    }
  }

  return UP;
}

int BnB::solve(std::stack<Node> &tree)
{
  Node root;
  updateNode(&root);

  tree.push(root);
  double UP = this->heuristic + 1;

  while (!tree.empty()) {
    auto node = tree.top();
    tree.pop();


    if(node.LB > UP) continue;


    if (node.feasible)
    {
        //std::cout << node.LB << endl;
      if (node.LB < UP)
      {
          UP = node.LB;
      }
      continue;
    }


    for (size_t i = 0; i < node.subtours[node.choosen].size() - 1; i++) {
        Node n;
      n.excluded_arcs = node.excluded_arcs;

      std::pair<int, int> excluded_arcs = {
          node.subtours[node.choosen][i],
          node.subtours[node.choosen][i + 1]};

      n.excluded_arcs.push_back(excluded_arcs);
      updateNode(&n);

      if (n.LB <= UP)
        tree.push(n);
    }
  }
  return UP;
}

// change method for BBS
int BnB::solve(std::priority_queue<Node> &tree) {
  Node root;
  updateNode(&root);

  tree.push(root);
  double UP = this->heuristic + 1;

  while (!tree.empty()) {
    auto node = tree.top();
    tree.pop();

    if (node.feasible) {
      if (node.LB < UP)
        UP = node.LB;
      continue;
    }

    for (size_t i = 0; i < node.subtours[node.choosen].size() - 1; i++) {
      struct Node n;
      n.excluded_arcs = node.excluded_arcs;

      std::pair<int, int> excluded_arcs = {
          node.subtours[node.choosen][i],
          node.subtours[node.choosen][i + 1]};

      n.excluded_arcs.push_back(excluded_arcs);
      updateNode(&n);

      if (n.LB <= UP)
        tree.push(n);
    }
  }

  return UP;
}

int BnB::getChoosen(Node *node) {

  int min_idx = 0, min_size = node->subtours[0].size();
  for (int i = 1; i < node->subtours.size(); i++) {
    if (node->subtours[i].size() < min_size) {
      min_idx = i;
      min_size = node->subtours[i].size();
    }
  }

  return min_idx;
}

bool BnB::isFeasible(Node *node) { return node->subtours.size() == 1; }

std::vector<std::vector<int>> BnB::getSubtours(hungarian_problem_t *p) {

  std::vector<std::vector<int>> subtours;
  std::vector<int> temp;
  std::set<int> seen;



  int i = 0;
  int idx = i;
  for (int j = i; seen.size() <= this->dim; j++) {
    if (j == this->dim || i == this->dim)
      break;
    if (p->assignment[i][j]) {
      seen.insert(i);

      temp.push_back(i + 1);
      i = j;
      j = -1;

      if (temp.back() == temp.front() && temp.size() > 1) {
        subtours.push_back(temp);
        temp.clear();
        while (seen.contains(idx))
          idx++;
        i = idx;
      }
    }
  }
  return subtours;
}

bool Node::operator<(const Node &node) const
{
    return this->LB > node.LB;
}
