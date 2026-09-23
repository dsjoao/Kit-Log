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

          getLat(best);

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

    for (int i = 0; i < s.permutation.size() ; i++)
        for (size_t j = 0; j < i ; j++)
        {
            if(j == 1) break;
            s.lat += data->getDistance(s.permutation[j], s.permutation[j + 1]);
        }

}

void MLP::show(Path &s)
{
    for (size_t i{}; i < s.permutation.size() - 1; ++i)
        std::cout << s.permutation[i] << "->";
    std::cout << s.permutation.back() << "\ncusto: ";

    std::cout << s.lat << std::endl;
}

inline subSeq MLP::concatenate(subSeq &sigma_1, subSeq& sigma_2)
{

  subSeq sigma;
  double temp = data->getDistance(sigma_1.last,sigma_2.first);
  sigma.w = sigma_1.w + sigma_2.w;
  sigma.t = sigma_1.t + temp + sigma_2.t;
  sigma.c = sigma_1.c + sigma_2.w * (sigma_1.t + temp) + sigma_2.c;
  sigma.first = sigma_1.first;
  sigma.last = sigma_2.last;

  return sigma;
}

void MLP::updateAllSubSeq(Path *s)
{
    int n = s->permutation.size();

    for (int i = 0; i < n; i++)
    {
        this->subSeq_matrix[i][i].w = (i > 0);
        this->subSeq_matrix[i][i].c = 0;
        this->subSeq_matrix[i][i].t = 0;
        this->subSeq_matrix[i][i].first = s->permutation[i];
        this->subSeq_matrix[i][i].last = s->permutation[i];
    }

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            this->subSeq_matrix[i][j] = concatenate(this->subSeq_matrix[i][j - 1],this->subSeq_matrix[j][j]);
        }


    for (int i = n - 1; i >= 0; i--)
        for (int j = i - 1; j >= n; j--)
        {
            this->subSeq_matrix[i][j] = concatenate(this->subSeq_matrix[i][j - 1],this->subSeq_matrix[j][j]);
        }

}
