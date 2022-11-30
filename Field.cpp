#include <algorithm>
#include <cmath>
#include <math.h>
#include "Field.h"
#include "Species.h"
#include <cstring>

#define F77NAME(x) x##_
extern "C" {
	void F77NAME(dgesv)(const int& n, const int& nrhs, const double * A,
		const int& lda, int * ipiv, double * B,
		const int& ldb, int& info);
}

Field::Field(float Lx, int Nx, float c): Lx{Lx}, Nx{Nx}, dx{Lx/Nx}, c{c}{
	this->E = new double[Nx];
	this->Et = new double[Nx];
	this->J = new float[Nx];
	this->Mgg = new float[Nx];
	this->Mggp = new float[Nx];
	this->A = new double[Nx*Nx];
	this->C = new double[Nx];
}

Field::Field(const Field& other): Lx{other.Lx}, Nx{other.Nx}, dx{other.dx}, c{other.c}{
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

void Field::initialize(float pert){
	for(int i = 0; i<Nx; ++i){
		E[i] = pert*std::sin(i*dx);
	}
	std::fill(Et, Et+Nx, 0);
	std::fill(A, A+Nx*Nx, 0);	
}

const double* Field::getE(){
	return const_cast<double*>(this->E);
}

const double* Field::getEt(){
	return const_cast<double*>(this->Et);
}

void Field::calculateJ(int Ns, Species* species){
	//Clear J 
	std::fill(this->J, this->J + Nx, 0);
	
	int Np;
	float q;
	const float* v;
	const int* g;
	const int* gp;
	const float* wg;
	const float* wgp;
	
	for (int s = 0; s < Ns; ++s){
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

void Field::calculateM(int Ns, Species* species, float dt){
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
	
	for (int s = 0; s < Ns; ++s){
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
		A[i*Nx+(i+1)%Nx] = c3*Mggp[i];
		A[((i+1)%Nx)*Nx+i] = c3*Mggp[i];
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