#include <iostream>
#include <string>

#include "ApplicationHelp.hpp"
#include "CommandLineArgument.hpp"
#include "Print.hpp"

int main() {
	ApplicationHelp help = ApplicationHelp::Builder()
	                           .setName("MediaConverter")
	                           .setAuthor("Matus Talcik")
	                           .setAbout("Converts file from one media "
	                                     "format to another")
	                           .addArgument(
	                               CommandLineArgument::Builder()
	                                   .setShortName('i')
	                                   .setLongName("input")
	                                   .setHelp("Path to input file")
	                                   .setTakesValue(true)
	                                   .build())
	                           .addArgument(
	                               CommandLineArgument::Builder()
	                                   .setShortName('o')
	                                   .setHelp("Path to output file")
	                                   .setTakesValue(true)
	                                   .build())
	                           .addArgument(
	                               CommandLineArgument::Builder()
	                                   .setLongName("codec")
	                                   .setHelp("Codec of output file")
	                                   .setTakesValue(true)
	                                   .build())
	                           .addArgument(
	                               CommandLineArgument::Builder()
	                                   .setShortName('f')
	                                   .setLongName("fast")
	                                   .build())
	                           .build();

	printApplicationHelp(help, std::cout);

	return 0;
}
