#include <vector>
#include "Data.h"
#include "ILS.hpp"
#include <cstdlib> 
#include <ctime>
#include <algorithm>

Path TSP_ILS::Construcao()
{
   puts("CONSTRUCAO \n");
   Path s;
   s.permutation = escolher3NosAleatorios();
   
   std::vector<int> CL = NosRestantes(s);

   getObjVal(s);

   while (!CL.empty())
   {
      std::vector<insertionInfo> custoInsercao = calcularCustoInsercao(s, CL);
      ordenarEmOrdemCrescente(custoInsercao);
      
      double alpha = (double)rand() / RAND_MAX;
      int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size()));
      
      inserirNaSolucao(s, custoInsercao[selecionado], CL);
   
   }
   return s;
}

std::vector<int> TSP_ILS::escolher3NosAleatorios()
{
   puts("3 ALEATORIOS \n");
   int dim = data->getDimension();

   generate : int rand1 = rand() % (dim - 2 + 1) + 2; // pega aleatório em range 2 ate dim
   int rand2 = rand() % (dim - 2 + 1) + 2;
   int rand3 = rand() % (dim - 2 + 1) + 2;

   if ((rand1 == rand2) || (rand1 == rand3) || (rand2 == rand3)) goto generate; // gotos não boa prática mas as vezes dá pra usar

   return {1,rand1,rand2,rand3,1};

   
}

std::vector<int> TSP_ILS::NosRestantes(Path &s)
{
   puts("NOSRESANTES \n");
   int dim = data->getDimension();
   
   std::vector<int> restantes(dim);

   for (int i = 0; i < dim; ++i)
      restantes[i] = i + 1;

   for (int i : s.permutation)
      std::erase(restantes, i);
      

   
   return restantes;
}

void TSP_ILS::ordenarEmOrdemCrescente(std::vector<insertionInfo> &custoInsercao)
{
   puts("SORT \n");
   std::sort(custoInsercao.begin(), custoInsercao.end(), [](const insertionInfo &a, const insertionInfo &b)
             { return a.custo < b.custo; });


}

std::vector<TSP_ILS::insertionInfo> TSP_ILS::calcularCustoInsercao(Path& s, std::vector<int>& CL)
{
   puts("CALCULAR CUSTO INSERCAO \n");
   

   std::vector<insertionInfo>custoInsercao = std::vector<insertionInfo>((s.permutation.size() - 1) * CL.size());

   
   int l = 0;
   for (int a = 0; a < s.permutation.size() - 1 ; a++)
   {
    
       int i = s.permutation[a];
       int j = s.permutation[a + 1];
       for (auto k : CL)
      {
         custoInsercao[l].custo = data->getDistance(i, k) + data->getDistance(j, k) - data->getDistance(i,j);
         custoInsercao[l].noInserido = k;
         custoInsercao[l].arestaRemovida = a;
         l++;
         
      }
      
   }
   puts("terminou o calculo \n");
   return custoInsercao;
   
}

void TSP_ILS::inserirNaSolucao(Path& s, TSP_ILS::insertionInfo& inserted, std::vector<int>& CL)
{
   puts("INSERIR NA SOL \n");
   s.permutation.insert(s.permutation.begin() + inserted.arestaRemovida + 1, inserted.noInserido);
   std::erase(CL, inserted.noInserido);

}
