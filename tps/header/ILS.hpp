#ifndef TSP_ILS_h
#define TSP_ILS_h

#include "Data.h"
#include <vector>

struct Path
{
   std::vector<int> permutation{};
   double objVal{};
};

class TSP_ILS
{

public:
   TSP_ILS() {}

   ~TSP_ILS() {}

   Path solve(int maxIter, int maxIterIls, Data *data);

   class Utils
   {

      public:
      Data *data;

      Utils(Data *data) { this->data = data; };
      ~Utils() {};

      struct insertionInfo
      {
         int noInserido;
         int arestaRemovida;
         double custo;
      };

      // ----------- construcao -----------

      Path Construcao();

      std::vector<int> escolher3NosAleatorios(Data *data);

      std::vector<int> NosRestantes(Data *data, Path &s);

      void ordenarEmOrdemCrescente(std::vector<insertionInfo> &custoInsercao);

      std::vector<insertionInfo> calcularCustoInsercao(Path &s, std::vector<int> & CL, Data *data);

      void inserirNaSolucao(Path &s, insertionInfo &inserted, std::vector<int>& CL);

      // -----------------------



      // ---------- busca local -----------------------

      void buscaLocal(Path *s);

      bool bestImprovementSwap(Path *s);

      bool bestImprovement2Opt(Path *s);

      bool bestImprovementOrOpt(Path *s, int count);
   
   
      // -----------------------------------


      // -------------- perturbação --------------

      Path perturbacao(Path s);

   };

};

#endif 