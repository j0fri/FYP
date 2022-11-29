#include "Simulation.h"
#include "Field.h"
#include "Species.h"

Simulation::Simulation(po::variables_map vm)
{
	if(vm.count("mode") && vm["mode"].as<int>() == 1){
		throw std::exception();
	}else{
		throw std::exception();
	}
}

Simulation::~Simulation()
{
}

