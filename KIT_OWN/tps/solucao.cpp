#include "solucao.hpp"
#include "Data.h"

double getObjVal(Path *s, Data& data)   // consertar isso aq 
{
   s->wTotal = 0;
    for (int i = 1; i < s->permutation.size(); ++i)
       s->wTotal += data.getDistance(s->permutation[i], s->permutation[i + 1]);
}

void show(Path *s)
{
   for (size_t i{}; s->permutation.size() - 1; ++i)
      std::cout << i << "->";
   std::cout << s->permutation.back() << std::endl;
}