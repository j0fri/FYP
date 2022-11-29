#ifndef FIELD_H
#define FIELD_H

#include "Species.h"

class Field
{
private:
	const float Lx;
	const int Nx;
	const float dx;
	const float c;
	
	double* E;
	double* Et;
	//float* B; //Only electric field in 1D1V case
	//float* Bt;
	
	float* J;
	float* Mgg;
	float* Mggp;
	
	double* A; //System matrix. Optimisation: avoid direct matrix formulation and use banded matrix
	double* C;
public:
	Field(float Lx, int Nx, float c);
	~Field();
	const double* getE();
	const double* getEt();
	void initialize(float pert);
	void calculateJ(int Ns, Species* species); //Optimise: many operations to optimise in J calc.
	void calculateM(int Ns, Species* species, float dt); //Optimise: join J and M calulation
	void solve(double dt); //Optimise: a lot
	void advanceField(double dt);
};

#endif // FIELD_H
