#include "hungarian.hpp"
#include "BnB.hpp"
#include "Data.hpp"



int main(int argc,char *argv[])
{
    Data data = Data(argc, argv[1]);

    hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;

	BnB solver(data, p, mode);


auto sb = solver.getSubtours();
for (const auto& s : sb) {
    for (int x : s) std::cout << x << ' ';
    std::cout << '\n';
}



	return 0;
}
