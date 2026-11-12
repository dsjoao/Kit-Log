#include "Data.hpp"
#include "hungarian.hpp"
#include "BnB.hpp"


int main(int argc,char *argv[])
{
    Data data = Data(argc, argv[1]);

    hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;

	BnB solver(data, p, mode);


	return 0;
}
