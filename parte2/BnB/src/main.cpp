#include "hungarian.hpp"
#include "BnB.hpp"
#include "Data.hpp"
#include <string>


int main(int argc,char *argv[])
{
    Data data = Data(argc, argv[1]);

    hungarian_problem_t p;
	int modeHung = HUNGARIAN_MODE_MINIMIZE_COST;

	int modeBnB = std::stoi(argv[2]);

	BnB solver(data, p, modeHung, modeBnB, std::stoi(argv[3]));

	std::cout << solver.solve();

	return 0;
}
