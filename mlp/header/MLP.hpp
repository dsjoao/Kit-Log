#ifndef TSP_ILS_h
#define TSP_ILS_h

#include "Data.h"
#include <vector>

struct Path
{
   std::vector<int> permutation;
   double lat;
};

struct subSeq
{
  double t, c;
  int w;
  int first, last;
};

class MLP
{

public:
   MLP(Data *data)
   {
      this->data = data;
   }

   ~MLP() {}

   Path solve(int maxIter, int maxIterIls);

   void getLat(Path &s);

   void show(Path &s);

   inline subSeq concatenate(subSeq& sigma_1, subSeq& sigma_2);

   void updateAllSubSeq(Path *s);

   Data *data;
   std::vector<std::vector<subSeq>>subSeq_matrix;

   struct insertionInfo
   {
      int noInserido;
      int arestaRemovida;
      double custo;
   };

      // ----------- construcao -----------

      Path Construcao();

      std::vector<int> escolher3NosAleatorios();

      std::vector<int> NosRestantes(Path &s);

      void ordenarEmOrdemCrescente(std::vector<insertionInfo> &custoInsercao);

      std::vector<insertionInfo> calcularCustoInsercao(Path &s, std::vector<int>& CL);

      void inserirNaSolucao(Path &s, insertionInfo &inserted, std::vector<int>& CL);

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
