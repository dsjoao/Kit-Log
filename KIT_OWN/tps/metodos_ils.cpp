#include "solucao.hpp"
#include "Data2.hpp"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <numeric>

// implementar parte do contrução, falta aparentemente insert e aprender mais c++ pra refatorar e ver os métodos

struct insertion
{
  int vertex_add;
  std::pair<int,int> side_rem;
  double cost;
};

Path generateRand(Data& data) // get random starting path 
{

   Path s{{1,1}};

   generate:
   srand(time(0));
   int rand1 = rand() % data.getDimension(); 
   int rand2 = rand() % data.getDimension();
   int rand3 = rand() % data.getDimension();

   if(rand1 == rand2 || rand1 == rand3 || rand2 == rand3) goto generate; // gotos are not good but they can spare some trouble

   std::vector<int> temp {rand1,rand2,rand3};
   s.permutation.insert(s.permutation.begin() + 1, temp.begin(),temp.end());

   return s;
}

std::vector<insertion> getPairs(Path& s, std::vector<int>& rest, Data data) // calculate all possible pairs and their cost
{

   std::vector<insertion> pairs(s.permutation.size() * rest.size());
   
   int counter{};
   for(size_t i{}; i < s.permutation.size() - 1; ++i)
      for(size_t j{}; j < rest.size(); ++j)
      {
         pairs[counter].vertex_add = rest[j];
         pairs[counter].side_rem = {s.permutation[i]}; // maybe make it just an int, just knoeing the firt member is necessary
         pairs[counter].cost = data.getDistance(rest[j], s.permutation[i]) 
         + data.getDistance(rest[j], s.permutation[i + 1])
         - data.getDistance(s.permutation[i], s.permutation[i + 1]);
         counter++;
      }

   return pairs;   
}

void sortStructVector(std::vector<insertion>& p) // sort the array
{  
   std::ranges::sort(p, {}, &insertion::cost);
}

void insert(Path& s, insertion n)
{
   for(int old_vert : s.permutation)
      if(old_vert == n.side_rem.first())
}

Path construcao() // 
{
   Data data(2, "file_path"); //temporary placeholder values
   data.read();
   Path s;
   s = generateRand(data);

   std::vector<int> cl(data.getDimension());

   std::ranges::iota(cl,2);

   for(int vert : s.permutation)
      std::erase(cl, vert);

   

   while (!cl.empty())
   {
      std::vector<insertion> pairs = getPairs(s, cl, data);
      sortStructVector(pairs);
      
      float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

      int selected = rand() % (static_cast<int>(ceil(r * pairs.size())));
      
   }

}

int main()
{

   
   



}