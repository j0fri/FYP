#include "Species.h"
#include <cmath>
#include <math.h>
#include "Field.h"
#include <cstdlib>
#include <limits>
#include <climits>
#include <ctime>
#include <float.h>
#include <iostream>
#include <cstring>
#include "math_helper.h"
#include <fstream>

Species::Species(int Np, float m, float q): Np{Np}, m{m}, q{q}{
	this->x = new float[Np];
	this->v = new float[Np];
	this->g = new int[Np];
	this->gp = new int[Np];
	this->wg = new float[Np];
	this->wgp = new float[Np];
}

Species::Species(const Species& other): Np{other.Np}, m{other.m}, q{other.q}{
	this->x = new float[Np];
	std::memcpy(this->x, other.x, Np*sizeof(float));
	this->v = new float[Np];
	std::memcpy(this->v, other.v, Np*sizeof(float));
	this->g = new int[Np];
	this->gp = new int[Np];
	this->wg = new float[Np];
	this->wgp = new float[Np];
}

Species::~Species(){
	delete[] this->x;
	delete[] this->v;
	delete[] this->g;
	delete[] this->gp;
	delete[] this->wg;
	delete[] this->wgp;
}

void Species::initializeWithFile(std::string fileName){
	std::ifstream initialFile(fileName);
	for(int i = 0; i < Np; ++i){
		initialFile >> x[i] >> v[i];
	}
}

void Species::initializePositions(float Lx, float pertRho0){
	math_helper::generateSinePerturbedDistribution(x, Np, Lx, pertRho0);
}

void Species::initializeVelocities(float Kb, float T0, float u, bool saveInitialVelocities){
	std::srand(std::time(NULL));
	float a = m/(2*Kb*T0);
	//float max = 0;
	for(int i = 0; i < Np; ++i){
		v[i] = math_helper::erfinv(2*(float)std::rand()/RAND_MAX-1)/std::sqrt(a) + u;
		//max = std::max(max, std::fabs(v[i]));
	}
	//std::cout << "max velocity magnitude: " << max << std::endl;
	if(saveInitialVelocities){
		std::ofstream velocityFile;
		velocityFile.open("MATLAB/initialVelocities.txt");
		for(int i = 0; i < Np; ++i){
			velocityFile << v[i] << std::endl;
		}
	}
}

void Species::advancePositions(float dt, float Lx){
	//Solve finite-grid instability avoiding movement of more than dx
	for(int i = 0; i < this->Np; ++i){
		x[i] += v[i]*dt;
		//Periodic boundary conditions
		while (x[i] >= Lx){
			x[i] -= Lx;
		}
		while (x[i] < 0){
			x[i] += Lx;
		}
	}
}

void Species::advanceVelocities(float dt, const Field& field){
	const double* Et = field.getEt();
	float beta = q/m*dt/2;
	for(int i = 0; i < Np; ++i){
		v[i] += 2*beta*(Et[g[i]]*wg[i]+Et[gp[i]]*wgp[i]);
	}
}

void Species::calculateGridIndices(float dx, int Nx){
	for(int i = 0; i < this->Np; ++i){
		g[i] = std::floor(x[i]/dx);
		gp[i] = (g[i]+1) % Nx;
		if(g[i]<0 || g[i]>=Nx || gp[i]<0 || gp[i]>=Nx){
			std::cout << "Problem, i = " << i << ", x[i] = " << x[i] << ", g[i] = " << g[i] << "v[i] = " << v[i] << std::endl;
			break;
		}
	}
}

void Species::calculateGridWeights(float dx){
	for(int i = 0; i < this->Np; ++i){
		wg[i] = std::fmod(x[i], dx)/dx;
		wgp[i] = 1-wg[i];
	}
}

const float* Species::getV() const{
	return const_cast<float*>(this->v);
}

const int* Species::getG() const{
	return const_cast<int*>(this->g);
}

const int* Species::getGp() const{
	return const_cast<int*>(this->gp);
}

const float* Species::getWg() const{
	return const_cast<float*>(this->wg);
}

const float* Species::getWgp() const{
	return const_cast<float*>(this->wgp);
}

float Species::getKineticEnergy() const{
	float output = 0;
	for(int i = 0; i < Np; ++i){
		output += v[i]*v[i];
	}
	return output*m/2;
}
