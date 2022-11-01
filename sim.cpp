#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
	po::options_description opts("Available options.");
	opts.add_options() 
		("saveParticles", po::value<bool>()->default_value(false), "Save particle position.")

}