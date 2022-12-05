#ifndef MATH_HELPER_H
#define MATH_HELPER_H

namespace math_helper{
	double erfinv( double y);
	void generateSinePerturbedDistribution(float* destination, int N, double Lx, double pertRho0);
}

#endif // MATH_HELPER_H
