#include "BnB.hpp"
#include "ILS.hpp"
#include "hungarian.hpp"
#include <cassert>
#include <list>
#include <queue>
#include <set>
#include <string>
#include <vector>

BnB::BnB(Data data_, hungarian_problem_t &p_, int mode) {
  this->data = &data_;
  this->p = &p_;

  assert((this->data != NULL && this->p != NULL) && "erro iniciando data");

  this->data->read();

  this->dim = data->getDimension();

  this->cost = new double *[dim];
  for (int i = 0; i < dim; i++) {
    cost[i] = new double[dim];
    for (int j = 0; j < dim; j++) {
      cost[i][j] = data->getDistance(i + 1, j + 1);
    }
  }

  hungarian_init(p, this->cost, this->dim, this->dim, mode);

  hungarian_solve(this->p);

  this->assig = new int *[dim];
  for (int i = 0; i < dim; i++) {
    assig[i] = new int[dim];
    for (int j = 0; j < dim; j++) {
      assig[i][j] = p->assignment[i][j];
    }
  }

  TSP_ILS temp(&data_);
  this->heuristic = &temp;

  assert(this->heuristic != NULL && "heuristica nao inicializada");
}

void BnB::updateNode(node *node) {

  hungarian_problem_t p;

  int mode = HUNGARIAN_MODE_MINIMIZE_COST;
  hungarian_init(&p, this->cost, this->dim, this->dim, mode);

  node->LB = hungarian_solve(&p);

  node->subtours = getSubtours();
  node->choosen = getChoosen(node);
  node->feasible = isFeasible(node);

  hungarian_free(&p);
}

int BnB::solve(int mode) {
  if (mode == 2) {
    std::priority_queue<node> tree;
    return this->solve(tree);
  }

  std::list<node> tree;

  return this->solve(tree, mode);
}

int BnB::solve(std::list<node> &tree, int mode) {
  node root;
  updateNode(&root);

  tree.push_back(root);
  double UP =
      this->heuristic->solve(50, (this->dim >= 150) ? this->dim / 2 : this->dim)
          .objVal;

  while (!tree.empty()) {
    auto node = BranchOut();

    if (node->feasible) {
      if (node->LB < UP)
        UP = node->LB;
      continue;
    }

    for (size_t i = 0; i < node->subtours[node->choosen].size() - 1; i++) {
      struct node n;
      n.excluded_arcs = node->excluded_arcs;

      std::pair<int, int> excluded_arcs = {
          node->subtours[node->choosen][i],
          node->subtours[node->choosen][i + 1]};

      n.excluded_arcs.push_back(excluded_arcs);
      updateNode(&n);

      if (n.LB <= UP)
        tree.push_back(n);
    }
  }

  return UP;
}

// change method for BBS
int BnB::solve(std::priority_queue<node> &tree) {
  node root;
  updateNode(&root);

  tree.push(root);
  double UP = std::stod("12,1");

  while (!tree.empty()) {
    auto node = BranchOut();

    if (node->feasible) {
      if (node->LB < UP)
        UP = node->LB;
      continue;
    }

    for (size_t i = 0; i < node->subtours[node->choosen].size() - 1; i++) {
      struct node n;
      n.excluded_arcs = node->excluded_arcs;

      std::pair<int, int> excluded_arcs = {
          node->subtours[node->choosen][i],
          node->subtours[node->choosen][i + 1]};

      n.excluded_arcs.push_back(excluded_arcs);
      // node::updateNode()

      if (n.LB <= UP)
        ; //	tree.push_back(n);
    }
  }

  return UP;
}

int BnB::getChoosen(node *node) {

  int min_idx = 0, min_size = node->subtours[0].size();
  for (int i = 1; i < node->subtours.size(); i++) {
    if (node->subtours[i].size() < min_size) {
      min_idx = i;
      min_size = node->subtours[i].size();
    }
  }

  return min_idx;
}

bool BnB::isFeasible(node *node) { return node->subtours.size() == 1; }

std::vector<std::vector<int>> BnB::getSubtours() {

  std::vector<std::vector<int>> subtours;
  std::vector<int> temp;
  std::set<int> seen;

  int x;

  int i = 0;
  int idx = i;
  for (int j = i; seen.size() <= this->dim; j++) {
    if (j == this->dim || i == this->dim)
      break;
    if (this->assig[i][j]) {
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
