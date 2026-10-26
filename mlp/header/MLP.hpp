#ifndef TSP_ILS_h
#define TSP_ILS_h

#include "Data.h"
#include <vector>

struct Path
{
   std::vector<int> permutation;
   double lat;
};

class MLP
{

struct Subseq
{
    double T,C;
    int W;
    int first, last;

    inline static Subseq concatenate(Subseq &sigma1, Subseq &sigma2, Data *data)
    {
        Subseq sigma;

        double temp = data->getDistance(sigma1.last, sigma2.first);
        sigma.W = sigma1.W + sigma2.W;
        sigma.T = sigma1.T + temp + sigma2.T;
        sigma.C = sigma1.C + sigma2.W * (sigma1.T + temp) + sigma2.C;

        sigma.first = sigma1.first;
        sigma.last = sigma2.last;

        return sigma;
    }

};


public:
   MLP(Data *data)
   {
      this->data = data;
      this->c = this->data->getMatrixCost();
      this->subseq_matrix =
          std::vector<std::vector<Subseq>>
          (this->data->getDimension() + 1,
           std::vector<Subseq>(this->data->getDimension() + 1));
   }

   ~MLP() {}

   Data *data;
   double **c;
   std::vector<std::vector<Subseq>> subseq_matrix;

   Path solve(int maxIter, int maxIterIls);

   void getLat(Path &s);

   void show(Path &s);

   void updateAllSubseq(Path *s);



      // ----------- construcao -----------

      Path Construcao();

      std::vector<int> NosRestantes(Path &s);

      void ordenarEmOrdemCrescente(std::vector<int> &custo, int r);

      // -----------------------



      // ---------- busca local -----------------------

      void buscaLocal(Path *s);

      bool bestImprovementSwap(Path *s);

      bool bestImprovement2Opt(Path *s);

      bool bestImprovementOrOpt(Path *s, int count);


      // -----------------------------------


      // -------------- perturbação --------------

      Path perturbacao(Path& s);

      void swapRanges(Path &s, int begin1, int end1, int begin2, int end2);
   };

#endif
