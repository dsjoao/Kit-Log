#include "Data.hpp"
#include "hungarian.hpp"

int main(int argc,char *argv[])
{
    Data data = Data(argc, argv[1]);

    hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;




	return 0;
}
