#include "Simulation.h"
#include "Field.h"
#include "Species.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

Simulation::Simulation(const po::variables_map& vm): field(this->initializeField(vm)), species(this->initializeSpecies(vm)) {}

Simulation::~Simulation(){}

Field Simulation::initializeField(const po::variables_map& vm){
	if(vm.count("mode") && vm["mode"].as<int>() == 1){
		return Field(4*M_PI,30,1,1);
	}
	return Field(0, 0, 0, 0);
}

std::vector<Species> Simulation::initializeSpecies(const po::variables_map& vm){
	if(vm.count("mode") && vm["mode"].as<int>() == 1){
		std::vector<Species> tempSpecies{};
		tempSpecies.emplace_back(5000, 1, -1);
		tempSpecies.emplace_back(5000, 2000, 1);
		for (Species& s: tempSpecies){
			s.initializePositions(4*M_PI);
			s.initializeVelocities(0.001, 1);
		}
		return tempSpecies;
	}
	return std::vector<Species>{};
}

void Simulation::run(const po::variables_map& vm){
	float T = vm["T"].as<float>();
	float dt = vm["dt"].as<float>();
	bool saveEnergy = vm["saveEnergy"].as<bool>();
	
	std::ofstream energyFile;
	if(saveEnergy){
		energyFile.open("MATLAB/energy.txt");
	}
	
	float t = 0;
	while (t < T){
		if(saveEnergy){
			energyFile << t << " ";
			energyFile << this->getTotalKineticEnergy() << " ";
			energyFile << this->field.getPotentialEnergy() << std::endl;
		}
		
		std::cout << "t: " << t << std::endl;;
		for(Species& s: this->species){
			s.advancePositions(dt, field.Lx);
			s.calculateGridIndices(field.dx, field.Nx);
			s.calculateGridWeights(field.dx);
		}
		this->field.calculateJ(this->species);
		this->field.calculateM(this->species, dt);
		this->field.solve(dt);
		for(Species& s: this->species){
			s.advanceVelocities(dt, field);
		}
		this->field.advanceField(dt);
		t += dt;
	}
	
	if(saveEnergy){
		energyFile.close();
	}
}

float Simulation::getTotalKineticEnergy() const{
	float output = 0;
	for(const Species& s: this->species){
		output += s.getKineticEnergy();
	}
	return output;
}
