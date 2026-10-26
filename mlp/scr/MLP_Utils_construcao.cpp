#include <vector>
#include "Data.h"
#include "MLP.hpp"
#include <cstdlib>
#include <algorithm>


// quase a mesma coisa to tsp eu acredito, a mdança foi nos números aleatórios que ao invés de 3 é 1
Path MLP::Construcao()
{

   int alfa = rand() % this->data->getDimension();

   Path s;
   s.permutation = {1,1};

   std::vector<int> CL = NosRestantes(s);

   getLat(s);

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


std::vector<int> MLP::NosRestantes(Path &s)
{

   int dim = data->getDimension();

   std::vector<int> restantes(dim);

   for (int i = 0; i < dim; ++i)
      restantes[i] = (i + 1) + 1;

   return restantes;
}

void MLP::ordenarEmOrdemCrescente(std::vector<insertionInfo> &custoInsercao)
{

   std::sort(custoInsercao.begin(), custoInsercao.end(), [](const insertionInfo &a, const insertionInfo &b)
             { return a.custo < b.custo; });


}

std::vector<MLP::insertionInfo> MLP::calcularCustoInsercao(Path& s, std::vector<int>& CL)
{



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

   return custoInsercao;

}

void MLP::inserirNaSolucao(Path& s, MLP::insertionInfo& inserted, std::vector<int>& CL)
{

   s.permutation.insert(s.permutation.begin() + inserted.arestaRemovida + 1, inserted.noInserido);
   std::erase(CL, inserted.noInserido);

}
