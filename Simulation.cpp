#include "Simulation.h"
#include "Field.h"
#include "Species.h"
#include <math.h>
#include <vector>
#include <iostream>

Simulation::Simulation(const po::variables_map& vm): field(this->initializeField(vm)), species(this->initializeSpecies(vm)){}

Simulation::~Simulation(){}

Field Simulation::initializeField(const po::variables_map& vm){
	if(vm.count("mode") && vm["mode"].as<int>() == 1){
		return Field(4*M_PI,30,1);
	}
	return Field(0, 0, 0);
}

std::vector<Species> Simulation::initializeSpecies(const po::variables_map& vm){
	if(vm.count("mode") && vm["mode"].as<int>() == 1){
		std::vector<Species> tempSpecies{};
		tempSpecies.emplace_back(5000, 1, -1);
		tempSpecies.emplace_back(5000, 2000, 1);
		for (Species& s: tempSpecies){
			s.initializePositions(4*M_PI);
			s.initializeVelocities(0.00001, 1);
		}
		return tempSpecies;
	}
	return std::vector<Species>{};
}

void Simulation::run(){}
