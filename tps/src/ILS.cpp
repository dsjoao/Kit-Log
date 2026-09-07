#include "ILS.hpp"

Path TSP_ILS::solve(int maxIter, int maxIterIls, Data *data)
{

   Utils util{Utils{data}};
   puts("DENTRO DA SOLUÇÃO \n");
   Path bestOfAll;
   bestOfAll.objVal = INFINITY;
    for (int i = 0; i < maxIter; i++) 
   {
       Path s = util.Construcao();
       Path best = s;
       int iterIls = 0;
       while (iterIls <= maxIterIls) 
      {
          util.buscaLocal(&s);
          if (s.objVal < best.objVal) 
         {
             best = s;
             iterIls = 0;
            
         }
          s = util.perturbacao(best);
          iterIls++;
         
      }
       if (best.objVal < bestOfAll.objVal) 
        bestOfAll = best;
      
   }
    return bestOfAll;
}

