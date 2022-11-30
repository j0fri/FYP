#ifndef SPECIES_H
#define SPECIES_H

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
	void initializePositions(float Lx); //For now only uniform
	void initializeVelocities(float Kb, float T0); //For now only boltzmann
	void advancePositions(float dt, float Lx);
	void advanceVelocities(float dt, Field& field);
	void calculateGridIndices(float dx, int Nx);
	void calculateGridWeights(float dx);
	const float* getV();
	const int* getG();
	const int* getGp();
	const float* getWg();
	const float* getWgp();
};

#endif // SPECIES_H
