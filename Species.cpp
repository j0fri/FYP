#include "Species.h"
#include <cmath>
#include <math.h>
#include "Field.h"
#include <cstdlib>
#include <climits>
#include <ctime>

Species::Species(int Np, float m, float q): Np{Np}, m{m}, q{q}{
	this->x = new float[Np];
	this->v = new float[Np];
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

void Species::initializePositions(float Lx){
	std::srand(std::time(NULL));
	for(int i = 0; i < Np; ++i){
		x[i] = std::rand()/RAND_MAX*Lx;
	}
}

void Species::initializeVelocities(float Kb, float T0){
	float a = m/(2*Kb*T0);
	for(int i = 0; i < Np; ++i){
		v[i] = math_helper::erfinv(2*std::rand/RAND_MAX-1)/std::sqrt(a);
	}
}

void Species::advancePositions(float dt, float Lx){
	//Solve finite-grid instability avoiding movement of more than dx
	for(int i = 0; i < this->Np; ++i){
		x[i] += v[i];
		//Periodic boundary conditions
		while (x[i] > Lx){
			x[i] -= Lx;
		}
		while (x[i] < Lx){
			x[i] += Lx;
		}
	}
}

void Species::advanceVelocities(float dt, Field& field){
	double* E = field.getEt();
	float beta = q/m*dt/2;
	for(int i = 0; i < Np; ++i){
		v[i] += 2*beta*(E[g[i]]*wg[i]+E[gp[i]]*wgp[i]);
	}
}

void Species::calculateGridIndices(float dx, int Nx){
	for(int i = 0; i < this->Np; ++i){
		g[i] = std::floor(x[i]/dx);
		gp[i] = g[i]+1 % Nx;
	}
}

void Species::calculateGridWeights(float dx){
	for(int i = 0; i < this->Np; ++i){
		wg[i] = std::fmod(x[i], dx)/dx;
		wgp[i] = 1-wg[i];
	}
}

const float* Species::getV(){
	return const_cast<float*>(this->v);
}

const int* Species::getG(){
	return const_cast<int*>(this->g);
}

const int* Species::getGp(){
	return const_cast<int*>(this->gp);
}

const float* Species::getWg(){
	return const_cast<float*>(this->wg);
}

const float* Species::getWgp(){
	return const_cast<float*>(this->wgp);
}

namespace math_helper{
	double erfinv( double y) //REferenceeeee: https://github.com/antelopeusersgroup/antelope_contrib/blob/master/lib/location/libgenloc/erfinv.c
	{
        double x,z,num,dem; /*working variables */
        /* coefficients in rational expansion */
        double a[4]={ 0.886226899, -1.645349621,  0.914624893, -0.140543331};
        double b[4]={-2.118377725,  1.442710462, -0.329097515,  0.012229801};
        double c[4]={-1.970840454, -1.624906493,  3.429567803,  1.641345311};
        double d[2]={ 3.543889200,  1.637067800};
        if(fabs(y) > 1.0) return (atof("NaN"));  /* This needs IEEE constant*/
        if(fabs(y) == 1.0) return((copysign(1.0,y))*DBL_MAX); 
        if( fabs(y) <= 0.7 ) 
        {
                z = y*y;
                num = (((a[3]*z + a[2])*z + a[1])*z + a[0]);
                dem = ((((b[3]*z + b[2])*z + b[1])*z +b[0])*z + 1.0);
                x = y*num/dem;
        }
        else if( (fabs(y) > 0.7) && (fabs(y) < 1.0) )
        {
                z = sqrt(-log((1.0-fabs(y))/2.0));
                num = ((c[3]*z + c[2])*z + c[1])*z + c[0];
                dem = (d[1]*z + d[0])*z + 1.0;
                x = (copysign(1.0,y))*num/dem;
        }
        /* Two steps of Newton-Raphson correction */
        x = x - (erf(x) - y)/( (2.0/sqrt(M_PI))*exp(-x*x));
        x = x - (erf(x) - y)/( (2.0/sqrt(M_PI))*exp(-x*x));

        return(x);
	}
}
