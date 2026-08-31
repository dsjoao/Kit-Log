#include "solucao.hpp" 
 

Path ILS(int maxIter, int maxIterIls) 
{
   Path bestOfAll;
   bestOfAll.wTotal = INFINITY;
    for (int i = 0; i < maxIter; i++) 
   {
       Path s = construcao();
       Path best = s;
       int iterIls = 0;
       while (iterIls <= maxIterIls) 
      {
          buscaLocal(&s);
          if (s.wTotal < best.wTotal) 
         {
             best = s;
             iterIls = 0;
            
         }
          s = perturbacao(best);
          iterIls++;
         
      }
       if (best.wTotal < bestOfAll.wTotal) 
        bestOfAll = best;
      
   }
    return bestOfAll;