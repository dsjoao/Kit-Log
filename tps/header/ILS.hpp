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

   Path ILS(int maxIter, int maxIterIls, Data *data);

public:
   TSP_ILS() {}

   ~TSP_ILS() {}

   class Utils
   {

      public:
      Data *data;

      Utils(Data *data) { this->data = data; };
      ~Utils() {};

      void getObjVal(Path &s);
      void show(Path &s);

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

      std::vector<insertionInfo> calcularCustoInsercao(Path &s, std::vector<int> &CL, Data *data);

      void inserirNaSolucao(Path &s, insertionInfo &inserted);

      // -----------------------



      // ---------- busca local -----------------------

      
   };
  
};

#endif 