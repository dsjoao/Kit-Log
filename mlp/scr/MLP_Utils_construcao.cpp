#include <vector>
#include "Data.h"
#include "MLP.hpp"
#include <cstdlib>
#include <algorithm>


// quase a mesma coisa to tsp eu acredito, a mdança foi nos números aleatórios que ao invés de 3 é 1
Path MLP::Construcao()
{

   Path s;
   s.permutation = {1};

   std::vector<int> CL = NosRestantes(s);


   int r = 1;

   while (!CL.empty())
   {

      ordenarEmOrdemCrescente(CL, r);


      double alfa = ((rand() % this->data->getDimension()) / 100);
      int selecionado =  CL[rand() % (std::max(1, (int)std::ceil(alfa * CL.size())))];

      s.permutation.push_back(selecionado);

      std::erase(CL, selecionado);

      r = selecionado;

   }

   s.permutation.push_back(1);

   return s;
}


std::vector<int> MLP::NosRestantes(Path &s)
{

   int dim = data->getDimension();

   std::vector<int> restantes;

   for (int i = 2; i <= dim; ++i)
      restantes.push_back(i);

   return restantes;
}

void MLP::ordenarEmOrdemCrescente(std::vector<int> &custo, int r)
{


    std::sort(custo.begin(), custo.end(), [r, this](int a, int b)
                 { return this->data->getDistance(r, a) < this->data->getDistance(r, b); });

}
