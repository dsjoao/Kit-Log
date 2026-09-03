#include <vector>
#include "Data.h"
#include "ILS.hpp"
#include <cstdlib> 
#include <ctime>

Path TSP_ILS::Utils::Construcao()
{
   Path s;
   s.permutation = escolher3NosAleatorios(this->data);
   std::vector<int> CL = NosRestantes(this->data, s);

   while (!CL.empty())
   {
      std::vector<insertionInfo> custoInsercao = calcularCustoInsercao(s, CL, this->data);
      ordenarEmOrdemCrescente(custoInsercao);
      double alpha = (double)rand() / RAND_MAX;
      int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size()));
      inserirNaSolucao(s, custoInsercao[selecionado]);
   }
   return s;
}

void TSP_ILS::Utils::getObjVal(Path &s)
{
   s.objVal = 0;
   for (size_t i{1}; i < s.permutation.size() - 1; ++i)
      s.objVal += this->data->getDistance(s.permutation[i], s.permutation[i + 1]);

   std::cout << s.objVal << std::endl;
}

void TSP_ILS::Utils::show(Path &s)
{
   for (size_t i{}; s.permutation.size() - 1; ++i)
      std::cout << i << "->";
   std::cout << s.permutation.back() << std::endl;
}

std::vector<int> TSP_ILS::Utils::escolher3NosAleatorios(Data *data)
{
   
   int dim {data->getDimension()};

   srand(time(0));

   generate:
   int rand1 = rand() % dim;
   int rand2 = rand() % dim;
   int rand3 = rand() % dim;

   if ((rand1 == rand2) || (rand1 == rand3) || (rand2 == rand3)) goto generate;

   return {1,rand1,rand2,rand3,1};

}

std::vector<int> TSP_ILS::Utils::NosRestantes(Data *data, Path &s)
{

   int dim = data->getDimension();
   
   std::vector<int> restantes(dim);

   while(dim)
   {
      restantes.insert(restantes.begin() + dim - 1, dim);
      --dim;
   }

   for(int i : s.permutation)
   {
      restantes.erase(std::remove(restantes.begin(), restantes.end(), i), restantes.end());
   }

   return restantes;
}

void TSP_ILS::Utils::ordenarEmOrdemCrescente(std::vector<insertionInfo> &custoInsercao)
{

   std::sort(custoInsercao.begin(), custoInsercao.end(), [](const insertionInfo &a, const insertionInfo &b)
             { return a.custo < b.custo; });


}

std::vector<TSP_ILS::Utils::insertionInfo> TSP_ILS::Utils::calcularCustoInsercao(Path& s, std::vector<int>& CL, Data *data)
{

   double **c = data->getMatrixCost();

   std::vector<insertionInfo>custoInsercao = std::vector<insertionInfo>((s.permutation.size() - 1) * CL.size());
   
   int l = 0;
   for (int a{}; a < s.permutation.size() - 1; ++a)
   {
       int i = s.permutation[a];
       int j = s.permutation[a + 1];
       for (auto k : CL)
      {
          custoInsercao[l].custo = c[i][k] + c[j][k] - c[i][j];
          custoInsercao[l].noInserido = k;
          custoInsercao[l].arestaRemovida = a;
          l++;
         
      }
      
   }
    return custoInsercao;
   
}

void TSP_ILS::Utils::inserirNaSolucao(Path& s, TSP_ILS::Utils::insertionInfo& inserted)
{

   for(size_t i{}; i < s.permutation.size() - 1; ++i)
   {
      if(s.permutation[i] == inserted.arestaRemovida)
      {
         s.permutation.insert(s.permutation.begin() + i + 1, inserted.noInserido);
         break;
      }   
   }
}
