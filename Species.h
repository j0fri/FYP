#ifndef SPECIES_H
#define SPECIES_H

#include <string>	

//Forward declare due to circular dependency
class Field;

class Species
{
public:
	const int Np;
	const float m;
	const float q;
private:
	float* x;
	float* v;
	int* g;
	int* gp;
	float* wg;
	float* wgp;
	float* Ep;
	//float* Bp; //No magnetic field in 1D1V simulation
public:
	Species(int Np, float m, float q);
	Species(const Species& other); //Copy constructor: copies onto new memory
	~Species();
	void initializePositions(float Lx, float pertRho0); //Perturbation in sine of rho0 for given species.
	void initializeVelocities(float a, float u, bool saveInitialVelocities); //For now only boltzmann
	void initializeWithFile(std::string fileName); //Initializes both positions and velocities with the provided file
	void advancePositions(float dt, float Lx);
	void advanceVelocities(float dt, const Field& field);
	void calculateGridIndices(float dx, int Nx);
	void calculateGridWeights(float dx);
	const float* getV() const;
	const int* getG() const;
	const int* getGp() const;
	const float* getWg() const;
	const float* getWgp() const;
	float getKineticEnergy() const;
};

#endif // SPECIES_H
