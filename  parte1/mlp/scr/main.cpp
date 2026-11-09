#include "MLP.hpp"
#include "Data.h"
#include <iostream>

// codigo pode ser bem refatorado em algumas partes

int main(int argc, char** argv) {

   Data data = Data(argc, argv[1]);
   data.read();

   MLP ils(&data);

   srand(time(0)); // gera aleatoriedade

   int dim = data.getDimension();

   int MaxIterILS = std::min(100, dim);
   int MaxIter = 10;



   Path opt = ils.solve(MaxIter, MaxIterILS);

   std::cout << "Soulucao encontrada:\n";
   ils.show(opt);


   return 0;
}
