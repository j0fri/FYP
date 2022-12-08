#include <iostream>
#include <boost/program_options.hpp>
#include "Simulation.h"
#include "Species.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
	po::options_description opts("Available options.");
	opts.add_options() 
		("mode", po::value<int>(), "1 is Landau, 2 is two-stream")
		("saveParticles", po::value<bool>()->default_value(false), "Save particle position.")
		("saveEnergy", po::value<bool>()->default_value(true), "Save field and kinetic energy.")
		("saveInitial", po::value<bool>()->default_value(true), "Save initial electric field and charge distribution.")
		("saveInitialVelocities", po::value<bool>()->default_value(true), "Save initial velocity distribution.")
		("loadInitialParticles", po::value<bool>()->default_value(true), "Load initial positions and velocities from file.")
		("loadInitialField", po::value<bool>()->default_value(true), "Load initial field from file.")
		("wavePertMag", po::value<float>()->default_value(0.0), "Magnitude of wave perturbation in electric field.")
		("ePertMag", po::value<float>()->default_value(0.5), "Magnitude of perturbation in distribution of electrons.")
		("Nx", po::value<int>()->default_value(30), "Field grid discretization points in x.")
		("Np", po::value<int>()->default_value(10000), "Number of particles.")
		("Lx", po::value<float>()->default_value(4*3.141592), "Field non-dimensional length in x.")
		("Kb", po::value<float>()->default_value(0.00001), "Boltzmann constant.")
		("T0", po::value<float>()->default_value(1), "Initial temperature (K).")
		("c", po::value<float>()->default_value(1), "Speed of light.")
		("e0", po::value<float>()->default_value(1), "Permittivity.")
		("T", po::value<float>()->default_value(15), "Total time.")
		("dt", po::value<float>()->default_value(0.01), "Time step.")
		("qe", po::value<float>()->default_value(-1), "Electron charge.")
		("qi", po::value<float>()->default_value(1), "Ion charge.")
		("me", po::value<float>()->default_value(1), "Electron mass")
		("mi", po::value<float>()->default_value(2000), "Ion mass")
		("ue", po::value<float>()->default_value(0), "Electron average velocity")
		("ui", po::value<float>()->default_value(0), "Ion average velocity")
		("rho0", po::value<float>()->default_value(1), "Initial unperturbed charge density");
	
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, opts), vm);
	
	Simulation sim(vm);
	sim.run(vm);
	
	return 0;
}