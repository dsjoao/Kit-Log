#include "ILS.hpp"
#include <cstdlib>
#include <ctime>

Path TSP_ILS::Utils::perturbacao(Path s) // talvez refazer como vector return
{
   puts("PERTUBARCAO \n");
   int dim = this->data->getDimension();

   srand(time(0));

   generate:
   int size1 = rand() % (dim / 10 - 2 + 1) + 2;   // formula pra pegar aletatorio em range [2, dimension], suponho q dimension seja maior q 2 quando dividir por 10

   int size2 = rand() % (dim / 10 - 2 + 1) + 2;

   int idx1 = (rand() % (dim / 10 - 2 + 1) + 2) - 1;  // indices nos vetores 

   int idx2 = (rand() % (dim / 10 - 2 + 1) + 2) - 1;

   if((size1 == size2) || (idx1 + size1 >= dim || idx2 + size2 >= dim)) goto generate;


   Path r = s;
   for (size_t i{}; i < size1; i++)
   {
      r.permutation[idx1 + i] = s.permutation[idx2 + i];
   }
   for (size_t i{}; i < size2; i++)
   {
      r.permutation[idx2 + i] = s.permutation[idx1 + i];
   }

   return r;

}