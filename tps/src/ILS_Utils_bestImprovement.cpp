#include "Data.h"
#include "ILS.hpp"
#include <vector>
#include <algorithm>

void TSP_ILS::Utils::buscaLocal(Path *s)
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

bool TSP_ILS::Utils::bestImprovementSwap(Path *s) 
{
    puts("SWAP \n");
    double **c = this->data->getMatrixCost(); 
    double bestDelta = 0;
    int best_i, best_j;
    for (int i = 1; i < s->permutation.size() - 1; i++) 
   {
       int vi = s->permutation[i];
       int vi_next = s->permutation[i + 1];
       int vi_prev = s->permutation[i - 1];
       for (int j = i + 1; j < s->permutation.size() - 1; j++) 
      {
          int vj = s->permutation[j];
          int vj_next = s->permutation[j + 1];
          int vj_prev = s->permutation[j - 1];
          double delta = -c[vi_prev][vi] - c[vi][vi_next] + c[vi_prev][vj]  
                         +c[vj][vi_next] - c[vj_prev][vj] - c[vj][vj_next] 
                         +c[vj_prev][vi] + c[vi][vj_next];
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

bool TSP_ILS::Utils::bestImprovement2Opt(Path *s)
{
    puts("2OPT \n");
    double **c = this->data->getMatrixCost();
    double bestDelta = 0;
    int best_i, best_j;
    for (int i = 1; i < s->permutation.size() - 1; i++)
    {
        int vi = s->permutation[i];
        int vi_prev = s->permutation[i - 1];
        for (int j = i + 2; j < s->permutation.size() - 1; j++)
        {
            int vj = s->permutation[j];
            int vj_next = s->permutation[j + 1];
            double delta = -c[vi][vi_prev] + c[vj][vi_prev] -c[vj][vj_next] + c[vi][vj_next];
            
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
        std::reverse(s->permutation.begin() + best_i, s->permutation.begin() + best_j);

        return true;
    }
    return false;
}

bool TSP_ILS::Utils:: bestImprovementOrOpt(Path *s, int count)
{
    puts("ORPT \n");
    double **c = this->data->getMatrixCost();
    double bestDelta = 0;
    int best_i, best_j;
    

        for (int i = 1; i < s->permutation.size() - 1 - count; i++)
        {
            int vi_start = s->permutation[i];
            int vi_end = s->permutation[i + (count - 1)];
            int vi_start_prev = s->permutation[i - 1];
            int vi_end_next = s->permutation[i + count];

            for (int j = i + count - 1; j < s->permutation.size() - 1; j++)
            {
                int vj = s->permutation[j];
                int vj_next = s->permutation[j + 1];
                int vj_prev = s->permutation[j - 1];
            

                double delta = -c[vi_start][vi_start_prev] -c[vi_end][vi_end_next] -c[vj][vj_next]
                               +c[vi_start][vj] +c[vi_end][vj_next] +c[vi_start_prev][vi_end_next];
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
            
            for (size_t i = 1; i < count; i++)
            {
                s->permutation.insert(s->permutation.begin() + best_j + 1, s->permutation[best_i + i]);
            }

            if(count != 1)
                s->permutation.erase(s->permutation.begin() + best_i + 1, s->permutation.begin() + count - 1); 
            
            return true;
        }
        return false;
    
}