#ifndef solucao
#define solucao

// soluções são vetores de ints, com peso em double e metodo de vizualizar junto 
// com um método extra definido como getOBjVal para pegar valor objetivo

#include <vector>
#include <iostream>
#include "Data.h"

struct Path
{  
   std::vector<int> permutation;
   double wTotal;
};

void show(Path *s);

double getObjVal(Path *s, Data data);

#endif // solucao.