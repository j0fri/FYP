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
	std::vector<Species> species;
	Field field;
	
	std::vector<Species> initializeSpecies(const po::variables_map& vm);
	Field initializeField(const po::variables_map& vm);
public:
	Simulation(const po::variables_map& vm);
	~Simulation();
	void run(const po::variables_map& vm);
	float getTotalKineticEnergy() const;
};

#endif // SIMULATION_H
