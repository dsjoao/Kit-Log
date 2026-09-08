#include "Data.h"
#include "ILS.hpp"
#include <vector>
#include <algorithm>

void TSP_ILS::buscaLocal(Path *s)
{
    puts("BUSCAR LOCAL \n");
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;
   
    while (NL.empty() == false) 
   {
       int n = rand() % NL.size();
       switch (NL[n]) 
      {
       case 1:
          improved = bestImprovementSwap(s);
          break;
       case 2:
          improved = bestImprovement2Opt(s);
          break;
       case 3:
          improved = bestImprovementOrOpt(s, 1); // Reinsertion
          break;
       case 4:
          improved = bestImprovementOrOpt(s, 2); // Or-opt2
          break;
       case 5:
          improved = bestImprovementOrOpt(s, 3); // Or-opt3
          break;
         
      }
       if (improved)  NL = {1, 2, 3, 4, 5};
       else  NL.erase(NL.begin() + n);
      
   }
   
} 

bool TSP_ILS::bestImprovementSwap(Path *s) 
{
    puts("SWAP\n");
    double bestDelta = 0;
    int best_i, best_j;
    for (int i = 1; i < s->permutation.size() - 1; i++) 
   {
       int vi = s->permutation[i];
       int vi_next = s->permutation[i + 1];
       int vi_prev = s->permutation[i - 1];
       for (int j = i + 2; j < s->permutation.size() - 1; j++) 
      {
          int vj = s->permutation[j];
          int vj_next = s->permutation[j + 1];
          int vj_prev = s->permutation[j - 1];

          double delta;

          if (j == i + 1) // adjacentes sao um caso a parte pois a soma deles na forma padrão inflaria o delta para numeros negativos falsos
          {
              delta = data->getDistance(vi_prev, vj) + data->getDistance(vi, vj_next) - data->getDistance(vi_prev, vi) - data->getDistance(vj, vj_next) 
                    + data->getDistance(vi, vj) - data->getDistance(vj, vi);
          }
          else
          {
              delta = - data->getDistance(vi_prev, vi) - data->getDistance(vi, vi_next) + data->getDistance(vi_prev, vj) // distancias do ponto x pra x - 1 e x + 1 (na sequencia) comparadas antes de dps da troca
                         + data->getDistance(vj, vi_next) - data->getDistance(vj_prev, vj) - data->getDistance(vj, vj_next) 
                         + data->getDistance(vj_prev, vi) + data->getDistance(vi, vj_next);
          }
          if (delta < bestDelta)
          {
              bestDelta = delta;
              best_i = i;
              best_j = j;
          }
         
      }
      
   }
    if (bestDelta < 0) 
    {
       std::swap(s->permutation[best_i], s->permutation[best_j]);

       return true;
      
    }
    return false;
   
}

bool TSP_ILS::bestImprovement2Opt(Path *s)
{
    puts("2OPT\n");
    double bestDelta = 0;
    int best_i, best_j;
    for (int i = 0; i < s->permutation.size() - 2; i++)
    {
        int vi = s->permutation[i];
        int vi_next = s->permutation[i + 1];
        for (int j = i + 2; j < s->permutation.size() - 1; j++)
        {
            int vj = s->permutation[j];
            int vj_next = s->permutation[j + 1];
            double delta = - data->getDistance(vi, vi_next) + data->getDistance(vj, vi_next) // compara a distancia de x com y + 1 e y com x - 1, pois a mudança é somente neles.
                           - data->getDistance(vj, vj_next) + data->getDistance(vi, vj_next);

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }
    if (bestDelta < 0)
    {

        if(best_i >= best_j)
        {
            std::swap(best_i,best_j);
        }

        std::reverse(s->permutation.begin() + best_i, s->permutation.begin() + best_j + 1);

        return true;
    }
    return false;
}

bool TSP_ILS:: bestImprovementOrOpt(Path *s, int count)
{
    printf("ORPT %d\n",count);
    double bestDelta = 0;
    int best_i, best_j;
    count--; // corrigir off by one
    

        for (int i = 1; i <=  - count - 2; i++)
        {
            int vi_start = s->permutation[i];
            int vi_end = s->permutation[i + count];
            int vi_start_prev = s->permutation[i - 1];
            int vi_end_next = s->permutation[i + count + 1];

            for (int j = i + 1; j < s->permutation.size() - count - 3; j++) // -2 pq o 1 no final n conta
            {
                int vj = s->permutation[j];
                int vj_next = s->permutation[j + 1];
           
                double delta = - data->getDistance(vi_start, vi_start_prev) - data->getDistance(vi_end, vi_end_next) - data->getDistance(vj, vj_next) 
                               + data->getDistance(vi_start, vj) + data->getDistance(vi_end, vj_next) + data->getDistance(vi_start_prev, vi_end_next);
                
                               if (delta < bestDelta)
                {
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if (bestDelta < 0)
        {
                // "gira" a sequencia ate o termo escolhio (do meio) seja o primeiro do range especificado (esquerda ate direita)
                // EX.: 1 2 3 4 5 6 7 8 de 3 ate 7 faça com que 6 seja o primeiro, ele retorna 1 2 6 7 3 4 5 8

            if (best_j > best_i + count)
            {
                std::rotate(s->permutation.begin() + best_i, s->permutation.begin() + best_i + count + 1, s->permutation.begin() + best_j + 1);
            }
            else if (best_j < best_i)
            {
                std::rotate(s->permutation.begin() + best_j, s->permutation.begin() + best_i, s->permutation.begin() + best_i + count + 1);
            }

            return true;
        }
        return false;
    
}