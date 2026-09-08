#ifndef TSP_ILS_h
#define TSP_ILS_h

#include "Data.h"
#include <vector>

struct Path
{
   std::vector<int> permutation;
   double objVal;
};

class TSP_ILS
{

public:
   TSP_ILS(Data *data) 
   {
      this->data = data;
      this->c = this->data->getMatrixCost();
   }

   ~TSP_ILS() {}

   Path solve(int maxIter, int maxIterIls);

   void getObjVal(Path &s);

   void show(Path &s);

   Data *data;
   double **c;

   struct insertionInfo
   {
      int noInserido;
      int arestaRemovida;
      double custo;
   };

      // ----------- construcao -----------

      Path Construcao(int ran);

      std::vector<int> escolher3NosAleatorios(long long ran);

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