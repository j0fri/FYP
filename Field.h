#ifndef FIELD_H
#define FIELD_H

#include "Species.h"
#include <vector>

class Field
{
public:
	const float Lx;
	const int Nx;
	const float dx;
	const float c;
	const float e0;
	
private:
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
	Field(float Lx, int Nx, float c, float e0);
	Field(const Field& other); //Copy constructor: copies onto new memory
	~Field();
	const double* getE() const;
	const double* getEt() const;
	void initializeFixed(float pert); //Initialize with a fixed sinusoidal perturbation
	void initializeWithChargeDistribution(std::vector<Species>& species, bool saveInitial); //Initialize to satisfy Maxwell's divergence equation
	void calculateJ(const std::vector<Species>& species); //Optimise: many operations to optimise in J calc.
	void calculateM(const std::vector<Species>& species, float dt); //Optimise: join J and M calulation
	void solve(double dt); //Optimise: a lot
	void advanceField(double dt);
	float getPotentialEnergy() const;
};

#endif // FIELD_H
