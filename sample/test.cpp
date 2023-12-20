#include "jobstream.h"

int main()
{
	std::cout << "RUNNING 50 CYCLES, \nQUEUE SIZE IS 5\n===============" << std::endl;
	TJobStream job(5);
	job.run(50);
}