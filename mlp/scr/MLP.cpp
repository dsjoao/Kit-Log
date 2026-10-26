#include "MLP.hpp"

Path MLP::solve(int maxIter, int maxIterIls)
{

   Path bestOfAll;
   bestOfAll.lat = INFINITY;
    for (int i = 0; i < maxIter; i++)
   {
       Path s = Construcao();
       Path best = s;

       getLat(best); // calcula o custo do caminho

       int iterIls = 0;
       while (iterIls <= maxIterIls)
      {
          buscaLocal(&s);

          getLat(s);

          if (s.lat < best.lat)
         {
             best = s;
             iterIls = 0;

         }
          s = perturbacao(best);

          getLat(s);

          iterIls++;

      }
       if (best.lat < bestOfAll.lat)
        bestOfAll = best;

   }
    return bestOfAll;
}

void MLP::getLat(Path &s)
{
    s.lat = 0;

    for (int i = 1; i < s.permutation.size() - 1; i++)
        s.lat += s.lat + data->getDistance(s.permutation[i], s.permutation[i + 1]);
}



void MLP::show(Path &s)
{
    for (size_t i{}; i < s.permutation.size() - 1; ++i)
        std::cout << s.permutation[i] << "->";
    std::cout << s.permutation.back() << "\ncusto: ";

    std::cout << s.lat << std::endl;
}

void MLP::updateAllSubseq(Path *s)
{

    int n = s->permutation.size();

    // seqs de um nó
    for (size_t i = 0; i < n; i++)
    {
        subseq_matrix[i][i].W = (i > 0);
        subseq_matrix[i][i].C = 0;
        subseq_matrix[i][i].T = 0;
        subseq_matrix[i][i].first = s->permutation[i];
        subseq_matrix[i][i].last = s->permutation[i];
    }

    // seqs de mais de um nó contatenado
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
        {
            subseq_matrix[i][j] = Subseq::concatenate(this->subseq_matrix[i][j - 1], this->subseq_matrix[j][j], this->data);
        }

    // seqs inversas para 2-opt
    for (size_t i = n - 1; i >= 0; i--)
        for (size_t j = i - 1; j >= 0; j--)
        {
            subseq_matrix[i][j] = Subseq::concatenate(this->subseq_matrix[i][j - 1], this->subseq_matrix[j][j], this->data);
        }

}
