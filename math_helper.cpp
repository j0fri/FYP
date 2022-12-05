#include "math_helper.h"
#include <random>
#include <climits>
#include <ctime>
#include <cmath>
#include <math.h>
#include <cfloat>
#include <iostream>

double math_helper::erfinv(double y){//REferenceeeee: https://github.com/antelopeusersgroup/antelope_contrib/blob/master/lib/location/libgenloc/erfinv.c
	if(y == 0 || y == 1){
		std::cout << "Inverse error function out of bounds exception" << std::endl;
	}
	double x,z,num,dem; /*working variables */
	x = 0; //Useless statement if y is in valid range.
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

const int SINE_PERTURBED_DISTRIBUTION_ITERATIONS = 4;
void math_helper::generateSinePerturbedDistribution(float* destination, int N, double Lx, double pertRho0){
	std::srand(std::time(NULL));
	double r, x;
	for(int i = 0; i < N; ++i){
		r = (double)std::rand()/RAND_MAX;
		x = r; //Initial approximation
		//Newton-Raphson iterations:
		for(int j = 0; j < SINE_PERTURBED_DISTRIBUTION_ITERATIONS; ++j){
			x = x - (x/Lx-pertRho0/(2*M_PI)*(std::cos(2*M_PI*x/Lx)-1)-r) / (1/Lx+pertRho0/Lx*std::sin(2*M_PI*x/Lx)); 
		}
		while(x >= Lx){
			x -= Lx;
		}
		while(x < 0){
			x += Lx;
		}
		destination[i] = (float)x;
	}
}

