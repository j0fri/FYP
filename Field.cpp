#include <algorithm>
#include <cmath>
#include <math.h>
#include "Field.h"
#include "Species.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#define F77NAME(x) x##_
extern "C" {
	void F77NAME(dgesv)(const int& n, const int& nrhs, const double * A,
		const int& lda, int * ipiv, double * B,
		const int& ldb, int& info);
}

Field::Field(float Lx, int Nx, float c, float e0): Lx{Lx}, Nx{Nx}, dx{Lx/Nx}, c{c}, e0{e0}{
	this->E = new double[Nx];
	this->Et = new double[Nx];
	this->J = new float[Nx];
	this->Mgg = new float[Nx];
	this->Mggp = new float[Nx];
	this->A = new double[Nx*Nx];
	this->C = new double[Nx];
}

Field::Field(const Field& other): Lx{other.Lx}, Nx{other.Nx}, dx{other.dx}, c{other.c}, e0{other.e0}{
	this->E = new double[Nx];
	std::memcpy(this->E, other.E, Nx*sizeof(double));
	this->Et = new double[Nx];
	this->J = new float[Nx];
	this->Mgg = new float[Nx];
	this->Mggp = new float[Nx];
	this->A = new double[Nx*Nx];
	this->C = new double[Nx];
}

Field::~Field(){
	delete[] this->E;
	delete[] this->Et;
	delete[] this->J;
	delete[] this->Mgg;
	delete[] this->Mggp;
	delete[] this->A;
	delete[] this->C;
}

void Field::initializeFixed(float pert){
	for(int i = 0; i<Nx; ++i){
		E[i] = pert*std::sin(i*dx);
	}
	std::fill(Et, Et+Nx, 0);
	std::fill(A, A+Nx*Nx, 0);	
}

void Field::initializeWithChargeDistribution(std::vector<Species>& species, bool saveInitial){
	float* rhoDist = new float[Nx];
	std::fill(rhoDist, rhoDist+Nx, 0);
	
	for(Species& s: species){
		s.calculateGridIndices(dx, Nx);
		const int* g = s.getG();
		for(int i = 0; i < s.Np; ++i){
			rhoDist[g[i]] += s.q/dx; 
		}
	}
	
	E[0] = 0;
	double shifting = 0;
	for(int i = 1; i < Nx; ++i){
		E[i] = E[i-1] + rhoDist[i]/e0*dx; //Not sure if *dx
		shifting += E[i]/Nx;
	}
	for(int i = 0; i < Nx; ++i){
		E[i] -= shifting;
	}
	
	if(saveInitial){
		std::ofstream initialFile;
		initialFile.open("MATLAB/initial.txt");
		for(int i = 0; i < Nx; ++i){
			initialFile << i*dx << " " << rhoDist[i] << " " << E[i] << std::endl;
		}
	}
	delete[] rhoDist;
	
	std::fill(Et, Et+Nx, 0);
	std::fill(A, A+Nx*Nx, 0);	
}

void Field::initializeWithFile(){
	std::ifstream fieldFile("MATLAB/initialField.txt");
	for(int i = 0; i < Nx; ++i){
		fieldFile >> E[i];
	}
	fieldFile.close();
	std::fill(Et, Et+Nx, 0);
	std::fill(A, A+Nx*Nx, 0);	
}

const double* Field::getE() const{
	return const_cast<double*>(this->E);
}

const double* Field::getEt() const{
	return const_cast<double*>(this->Et);
}

void Field::calculateJ(const std::vector<Species>& species){
	//Clear J 
	std::fill(this->J, this->J + Nx, 0);
	
	int Np;
	float q;
	const float* v;
	const int* g;
	const int* gp;
	const float* wg;
	const float* wgp;
	
	for (int s = 0; s < (int)species.size(); ++s){
		Np = species[s].Np;
		q = species[s].q;
		v = species[s].getV();
		g = species[s].getG();
		gp = species[s].getGp();
		wg = species[s].getWg();
		wgp = species[s].getWgp();
		for (int p = 0; p < Np; ++p){
			J[g[p]] += q*v[p]*wg[p]/dx;
			J[gp[p]] += q*v[p]*wgp[p]/dx;
		}
	}
}

void Field::calculateM(const std::vector<Species>& species, float dt){
	//Clear Mgg and Mggp 
	std::fill(this->Mgg, this->Mgg + Nx, 0);
	std::fill(this->Mggp, this->Mggp + Nx, 0);
	
	int Np;
	float m;
	float q;
	float beta;
	const int* g;
	const int* gp;
	const float* wg;
	const float* wgp;
	
	for (int s = 0; s < (int)species.size(); ++s){
		Np = species[s].Np;
		m = species[s].m;
		q = species[s].q;
		beta = q/m*dt/2;
		g = species[s].getG();
		gp = species[s].getGp();
		wg = species[s].getWg();
		wgp = species[s].getWgp();
		for (int p = 0; p < Np; ++p){
			Mgg[g[p]] += q*beta*wg[p]*wg[p]/dx;
			Mgg[gp[p]] += q*beta*wgp[p]*wgp[p]/dx;
			Mggp[g[p]] += q*beta*wg[p]*wgp[p]/dx;
		}
	}
}

void Field::solve(double dt){
	double c2 = 2/(c*dt);
	double c3 = 4*M_PI/c;
	for(int i = 0; i < Nx; ++i){
		A[i*(Nx+1)] = -c2;
		A[i*(Nx+1)] -= c3*Mgg[i];
		A[i*Nx+(i+1)%Nx] = -c3*Mggp[i];
		A[((i+1)%Nx)*Nx+i] = -c3*Mggp[i];
	}
	for(int i = 0; i < Nx; ++i){
		C[i] = -c2*E[i]+c3*J[i];
	}
	int* pivots = new int[Nx];
	int info;
	F77NAME(dgesv)(Nx, 1, A, Nx, pivots, C, Nx, info);
	std::copy(C, C+Nx, Et);
	delete[] pivots;
}

void Field::advanceField(double dt){
	for(int i = 0; i < Nx; ++i){
		E[i] = 2*Et[i]-E[i];
	}
}

float Field::getPotentialEnergy() const{
	float output = 0;
	for(int i = 0; i < Nx; ++i){
		output += E[i]*E[i];
	}
	return output/this->e0*dx/(8*M_PI);
}