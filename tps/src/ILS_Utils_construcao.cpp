#include <vector>
#include "Data.h"
#include "ILS.hpp"
#include <cstdlib> 
#include <ctime>
#include <algorithm>

Path TSP_ILS::Utils::Construcao()
{
   puts("CONSTRUCAO \n");
   Path s;
   s.permutation = escolher3NosAleatorios(this->data);
   std::vector<int> CL = NosRestantes(this->data, s);

   while (!CL.empty())
   {
      std::vector<insertionInfo> custoInsercao = calcularCustoInsercao(s, CL, this->data);
      ordenarEmOrdemCrescente(custoInsercao);
      double alpha = (double)rand() / RAND_MAX;
      int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size()));
      inserirNaSolucao(s, custoInsercao[selecionado], CL);
   
   }
   return s;
}

std::vector<int> TSP_ILS::Utils::escolher3NosAleatorios(Data *data)
{
   puts("3 ALEATORIOS \n");
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
   puts("NOSRESANTES \n");
   int dim = data->getDimension();
   
   std::vector<int> restantes(dim);

   for (int i = 0; i < dim; ++i)
      restantes[i] = i;
   
      for(int i : s.permutation)
   {
      restantes.erase(std::remove(restantes.begin(), restantes.end(), i), restantes.end());
   }

   return restantes;
}

void TSP_ILS::Utils::ordenarEmOrdemCrescente(std::vector<insertionInfo> &custoInsercao)
{
   puts("SORT \n");
   std::sort(custoInsercao.begin(), custoInsercao.end(), [](const insertionInfo &a, const insertionInfo &b)
             { return a.custo < b.custo; });


}

std::vector<TSP_ILS::Utils::insertionInfo> TSP_ILS::Utils::calcularCustoInsercao(Path& s, std::vector<int>& CL, Data *data)
{
   puts("CALCULAR CUSTO INSERCAO \n");
   double **c = data->getMatrixCost();

   std::vector<insertionInfo>custoInsercao = std::vector<insertionInfo>((s.permutation.size() - 1) * CL.size());
   
   int l = 0;
   for (int a{}; a + 1 < s.permutation.size() ; ++a)
   {
      
       int i = s.permutation[a];
       int j = s.permutation[a + 1];
       for (auto k : CL)
      {
         
         printf("%d  %d  %d  %d \n" , a, i , j, k);
          custoInsercao[l].custo = c[i][k] + c[j][k] - c[i][j];
          custoInsercao[l].noInserido = k;
          custoInsercao[l].arestaRemovida = a;
          l++;
         
      }
      puts("opa");
   }
   puts("terminou o calculo \n");
   return custoInsercao;
   
}

void TSP_ILS::Utils::inserirNaSolucao(Path& s, TSP_ILS::Utils::insertionInfo& inserted, std::vector<int>& CL)
{
   puts("INSERIR NA SOL \n");
   for(size_t i{}; i < s.permutation.size() - 1; ++i)
   {
      if(s.permutation[i] == inserted.arestaRemovida)
      {
         s.permutation.insert(s.permutation.begin() + i + 1, inserted.noInserido);
         std::erase(CL,inserted.noInserido); 
         break;
      }   
   }
}
