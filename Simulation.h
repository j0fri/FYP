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
	Field initializeField(const po::variables_map& vm);
	std::vector<Species> initializeSpecies(const po::variables_map& vm);
	float getTotalKineticEnergy() const;
public:
	Simulation(const po::variables_map& vm);
	~Simulation();
	void run(const po::variables_map& vm);
};

#endif // SIMULATION_H
