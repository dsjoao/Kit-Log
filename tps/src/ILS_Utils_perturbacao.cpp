#include "ILS.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

Path TSP_ILS::perturbacao(Path& s) // talvez refazer como vector return
{
   puts("PERTUBARCAO \n");
   
   int dim = data->getDimension();
   int max = (int)ceil(dim / 10.0);

   max = (max < 2) ? 2 : max;

   srand(time(0));

   generate:
   int idx1 = rand() % (dim - 2 + 1) + 2; // numeros entre 2 e dim / 10 se a divisao der mais de 1, se der menos os numeros serao todos 2 

   int idx2 = rand() % (dim - 2 + 1) + 2;

   int size1 = rand() % (max - 2 + 1) + 2; 

   int size2 = rand() % (max - 2 + 1) + 2;

   if(idx1 > idx1) std::swap(idx1, idx2);
   if(size1 > size2) std::swap(size1,size2);

   if ((idx1 + size1 >= idx2 - 1) || (idx2 + size2 >= dim - 1)) goto generate; // estrutura meio feia e com goto mas funciona

   int end1 = idx1 + size1;
   int end2 = idx2 + size2;

   Path r = s;

   swapRanges(s, idx1, end1, idx2, end2);

   return r;
}

void TSP_ILS::swapRanges(Path &s, int begin1, int end1, int begin2, int end2)
{

   std::reverse(s.permutation.begin() + begin1, s.permutation.begin() + end1); // algorimto de trocar ranges que gira o vetor varias vezes como foi descrito em bestimprovement
   std::reverse(s.permutation.begin() + end1, s.permutation.begin() + begin2);
   std::reverse(s.permutation.begin() + begin2, s.permutation.begin() + end2);
   std::reverse(s.permutation.begin() + begin1, s.permutation.begin() + end2);
}

