#include "ILS.hpp"
#include "Data.h"
#include <iostream>

void getObjVal(Path &s, Data& data)
{
   s.objVal = 0;
   for (size_t i{}; i < s.permutation.size() - 1; ++i)
      s.objVal += data.getDistance(s.permutation[i], s.permutation[i + 1]);

   std::cout << s.objVal << std::endl;
}

void show(Path &s)
{
   for (size_t i{}; i < s.permutation.size() - 1; ++i)
      std::cout << s.permutation[i] << "->";
   std::cout << s.permutation.back() << std::endl;
}

int main(int argc, char** argv) {
   
   puts("INICIANDO \n");
   Data data = Data(argc, argv[1]);

   data.read();
   puts("DADOS LIDOS \n");

   TSP_ILS ils(&data);

   int dim = data.getDimension();

   int MaxIterILS = (dim >= 150 ? dim / 2 : dim);

   int MaxIter = 50;

   puts("INICIANDO RESOLUCAO \n");
   Path opt = ils.solve(MaxIter, MaxIterILS);

   std::cout << "Soulucao encontrada: \n";
   show(opt);
   std::cout << "com custo: ";
   getObjVal(opt, data);

   return 0;
}