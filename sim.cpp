#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
	po::options_description opts("Available options.");
	opts.add_options() 
		("mode", po::value<int>()->default_value(1), "1 is Landau, 2 is two-stream")
		("saveParticles", po::value<bool>()->default_value(false), "Save particle position.")
		("saveEnergy", po::value<bool>()->default_value(false), "Save field and kinetic energy.")
		("Nx", po::value<int>()->default_value(30), "Field grid discretization points in x.")
		("Np", po::value<int>()->default_value(30), "Number of particles.")
		("Lx", po::value<int>()->default_value(4*3.141592), "Field non-dimensional length in x.")
		("Kb", po::value<float>()->default_value(0.00001), "Boltzmann constant.")
		("T", po::value<float>()->default_value(15), "Total time.")
		("dt", po::value<float>()->default_value(0.1), "Time step.");
	
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, opts), vm);
}