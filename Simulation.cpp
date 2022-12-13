#include "Simulation.h"
#include "Field.h"
#include "Species.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

Simulation::Simulation(const po::variables_map& vm): species(this->initializeSpecies(vm)), field(this->initializeField(vm)){}

Simulation::~Simulation(){}

Field Simulation::initializeField(const po::variables_map& vm){
	if(!vm.count("mode")){
		float Lx = vm["Lx"].as<float>();
		int Nx = vm["Nx"].as<int>();
		float c = vm["c"].as<float>();
		float e0 = vm["e0"].as<float>();
		bool saveInitial = vm["saveInitial"].as<bool>();
		bool loadInitialField = vm["loadInitialField"].as<bool>();
		Field tempField{(float)Lx, Nx, (float)c, (float)e0};
		
		if(!loadInitialField){
			tempField.initializeWithChargeDistribution(species, saveInitial);
		}else{
			tempField.initializeWithFile();
		}
		
		//tempField.initializeFixed(0);
		return tempField;
	}
	if(vm.count("mode") && vm["mode"].as<int>() == 1){
		Field tempField{4*M_PI,30,1,1};
		tempField.initializeWithChargeDistribution(species, false);
		return tempField;
	}
	if(vm.count("mode") && vm["mode"].as<int>() == 2){
		Field tempField{4*M_PI,30,1,1};
		tempField.initializeFixed(0.5);
		return tempField;	
	}
	return Field(0, 0, 0, 0);
}

std::vector<Species> Simulation::initializeSpecies(const po::variables_map& vm){
	if(!vm.count("mode")){
		int Np = vm["Np"].as<int>();
		float Lx = vm["Lx"].as<float>();
		float qe = vm["qe"].as<float>();
		float qi = vm["qi"].as<float>();
		float me = vm["me"].as<float>();
		float mi = vm["mi"].as<float>();
		float ue = vm["ue"].as<float>();
		float ui = vm["ui"].as<float>();
		float Kb = vm["Kb"].as<float>();
		float T0 = vm["T0"].as<float>();
		float rho0 = vm["rho0"].as<float>();
		float ePertMag = vm["ePertMag"].as<float>();
		bool saveInitialVelocities = vm["saveInitialVelocities"].as<bool>();
		bool loadInitialParticles = vm["loadInitialParticles"].as<bool>();
		
		std::vector<Species> tempSpecies{};
		float scaling = Lx/(Np/2*std::fabs(qi)+Np/2*std::fabs(qe));
		tempSpecies.emplace_back(Np/2, me*scaling, qe*scaling);
		tempSpecies.emplace_back(Np/2, mi*scaling, qi*scaling);
		
		if(!loadInitialParticles){
			tempSpecies[0].initializePositions(Lx, -ePertMag/rho0); //Not sure is should divide rho0 as it's only electrons
			tempSpecies[1].initializePositions(Lx, 0);
			tempSpecies[0].initializeVelocities(me/(2*Kb*T0), ue, saveInitialVelocities);
			tempSpecies[1].initializeVelocities(mi/(2*Kb*T0), ui, saveInitialVelocities);
		}else{
			std::cout << "Loading particles from files" << std::endl;
			tempSpecies[0].initializeWithFile("MATLAB/initialElectrons.txt");
			tempSpecies[1].initializeWithFile("MATLAB/initialIons.txt");
		}
		
		return tempSpecies;
	}
	if(vm.count("mode") && vm["mode"].as<int>() == 1){
		std::vector<Species> tempSpecies{};
		float scaling = M_PI*4/100000;
		tempSpecies.emplace_back(50000, 1*scaling, -1*scaling);
		tempSpecies.emplace_back(50000, 2000*scaling, 1*scaling);
		tempSpecies[0].initializeWithFile("MATLAB/initialElectrons.txt");
		tempSpecies[1].initializeWithFile("MATLAB/initialIons.txt");
		return tempSpecies;
	}
	if(vm.count("mode") && vm["mode"].as<int>() == 2){
		std::vector<Species> tempSpecies{};
		float scaling = M_PI*4/10000;
		tempSpecies.emplace_back(5000, 1*scaling, -1*scaling);
		tempSpecies.emplace_back(5000, 2000*scaling, 1*scaling);
		for (Species& s: tempSpecies){
			s.initializePositions(4*M_PI, 0.0);
			s.initializeVelocities(1, 0, false);
		}
		return tempSpecies;
	}
	return std::vector<Species>{};
}

void Simulation::run(const po::variables_map& vm){
	float T;
	float dt;
	bool saveEnergy;
	
	if(vm.count("mode") && vm["mode"].as<int>() == 1){
		T = 10.0;
		dt = 0.01;
		saveEnergy = true;
	}else{
		T = vm["T"].as<float>();
		dt = vm["dt"].as<float>();
		saveEnergy = vm["saveEnergy"].as<bool>();
	}
	
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
