#include "MLP.hpp"
#include <cstdlib>
#include <cmath>
#include <algorithm>

Path MLP::perturbacao(Path& s)
{

    generate:
        int dim = this->data->getDimension();
        int max = std::max(2, (int)std::ceil(dim / 10.0));

        int size1 = rand() % (max - 2 + 1) + 2;
        int size2 = rand() % (max - 2 + 1) + 2;

        int idx1 = rand() % (dim - 2) + 2;
        int idx2 = rand() % (dim - 2) + 2;

        if (idx1 > idx2) std::swap(idx1, idx2);

        if (idx1 + size1 > idx2) goto generate;
        if (idx2 + size2 > dim)  goto generate;


   Path r = s;

   swapRanges(r, idx1, idx1 + size1, idx2, idx2 + size2);

   updateAllSubseq(&r);

   return r;
}

void MLP::swapRanges(Path &s, int begin1, int end1, int begin2, int end2)
{

   // algorimto de trocar ranges de tamanhos diferentes, ele inverte diferentes ranges e 4 vezes para deixar o bloco selecionado na posição, pois inverte e inverte novamente sem o bloco, deixando ele na posição
   std::reverse(s.permutation.begin() + begin1,   s.permutation.begin() + end1);
   std::reverse(s.permutation.begin() + end1  , s.permutation.begin() + begin2);
   std::reverse(s.permutation.begin() + begin2,   s.permutation.begin() + end2);
   std::reverse(s.permutation.begin() + begin1,   s.permutation.begin() + end2);


}
