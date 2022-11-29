#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
	po::options_description opts("Available options.");
	opts.add_options() 
		("saveParticles", po::value<bool>()->default_value(false), "Save particle position.")
		("Nx", po::value<int>()->default_value(30), "Field grid discretization points in x.")
		("Lx", po::value<int>()->default_value(30), "Field non-dimensional length in x.")
		("Kb", po::value<float>()->default_value(1), "Boltzmann constant.")
		

}