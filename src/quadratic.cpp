#include "quadratic.h"

std::pair<std::complex<double>, std::complex<double>> Quadratic::solve(double a, double b, double c)
{
	std::complex<double> sqrt_func = sqrt(std::complex<double>(b*b - 4*a*c));

	std::complex<double> root1 = (-b + sqrt_func) / (2*a);
	std::complex<double> root2 = (-b - sqrt_func) / (2*a);

	return std::make_pair(root1, root2);
}
