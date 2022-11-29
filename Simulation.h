#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include <boost/program_options.hpp>
#include "Field.h"
#include "Species.h"

namespace po = boost::program_options;

class Simulation
{
private:
	Field field;
	std::vector<Species> species;
public:
	Simulation(po::variables_map vm);
	~Simulation();
	void run();
};

#endif // SIMULATION_H
