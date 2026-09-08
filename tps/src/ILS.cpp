#include "ILS.hpp"

Path TSP_ILS::solve(int maxIter, int maxIterIls)
{

   puts("DENTRO DA SOLUCAO \n");
   Path bestOfAll;
   bestOfAll.objVal = INFINITY;
    for (int i = 0; i < maxIter; i++) 
   {
       Path s = Construcao();
       Path best = s;

       getObjVal(best); // calcula o custo do caminho

       int iterIls = 0;
       while (iterIls <= maxIterIls) 
      {
          buscaLocal(&s);

          getObjVal(s);

          if (s.objVal < best.objVal) 
         {
             best = s;
             iterIls = 0;
            
         }
          s = perturbacao(best);

          getObjVal(best);

          iterIls++;
         
      }
       if (best.objVal < bestOfAll.objVal) 
        bestOfAll = best;
      
   }
    return bestOfAll;
}

void TSP_ILS::getObjVal(Path &s)
{
    s.objVal = 0;
    for (size_t i{}; i < s.permutation.size() - 1; ++i)
        s.objVal += data->getDistance(s.permutation[i], s.permutation[i + 1]);

}

void TSP_ILS::show(Path &s)
{
    for (size_t i{}; i < s.permutation.size() - 1; ++i)
        std::cout << s.permutation[i] << "->";
    std::cout << s.permutation.back() << "\n";

    std::cout << s.objVal << std::endl;
}