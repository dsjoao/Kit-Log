#include "MLP.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

Path MLP::perturbacao(Path& s) 
{
   
   
   int dim = data->getDimension();
   int max = (int)ceil(dim / 10.0);

   max = (max < 2) ? 2 : max;


   generate:
   int idx1 = rand() % ((dim - 2) - 1 + 1) + 1; // numeros entre 1 e dim - 2  para pegar iterators 

   int idx2 = rand() % ((dim - 2) - 1 + 1) + 1;

   int size1 = rand() % (max - 2 + 1) + 2;  // numeros entre 2 e dim / 10 para o tamanho dos blocos

   int size2 = rand() % (max - 2 + 1) + 2;

   if(idx1 > idx2) std::swap(idx1, idx2);
   if(size1 > size2) std::swap(size1,size2);

   if ((idx1 + size1 > idx2 ) || (idx2 + size2 >= dim  )) goto generate; // estrutura meio feia e com goto mas funciona

   int end1 = idx1 + size1;
   int end2 = idx2 + size2;

   Path r = s;

   swapRanges(r, idx1, end1, idx2, end2);

   return r;
}

void MLP::swapRanges(Path &s, int begin1, int end1, int begin2, int end2)
{

   // algorimto de trocar ranges de tamanhos diferentes, ele inverte diferentes ranges e 4 vezes para deixar o bloco selecionado na posição, pois inverte e inverte novamente sem o bloco, deixando ele na posição 
   std::reverse(s.permutation.begin() + begin1,   s.permutation.begin() + end1 + 1);  
   std::reverse(s.permutation.begin() + end1 + 1, s.permutation.begin() + begin2  );
   std::reverse(s.permutation.begin() + begin2,   s.permutation.begin() + end2 + 1);
   std::reverse(s.permutation.begin() + begin1,   s.permutation.begin() + end2 + 1);


}

