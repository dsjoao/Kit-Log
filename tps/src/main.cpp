#include "ILS.hpp"
#include "Data.h"
#include <iostream>


int main(int argc, char** argv) {
   
   puts("INICIANDO \n");
   Data data = Data(argc, argv[1]);

   data.read();
   puts("DADOS LIDOS \n");

   TSP_ILS ils(&data);

   srand(time(0)); // gera aleatoriedade

   int dim = data.getDimension();

   int MaxIterILS = (dim >= 150 ? dim / 2 : dim);

   int MaxIter = 50;


   puts("INICIANDO RESOLUCAO \n");
   Path opt = ils.solve(MaxIter, MaxIterILS);

   std::cout << "Soulucao encontrada: \n";
   ils.show(opt);
   

   return 0;
}