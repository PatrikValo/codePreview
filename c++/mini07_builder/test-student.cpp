#include "ApplicationHelp.hpp"
#include "CommandLineArgument.hpp"
#include "Print.hpp"
#include "catch.hpp"
#include <sstream>

inline void testPrintCLA(const CommandLineArgument& arg, const char* required) {
	std::ostringstream out;
	printCommandLineArgument(arg, out);
	CHECK(out.str() == required);
}

inline void testPrintAH(const ApplicationHelp& arg, const char* required) {
	std::ostringstream out;
	printApplicationHelp(arg, out);
	CHECK(out.str() == required);
}

inline CommandLineArgument buildCLA(int which) {
	CommandLineArgument::Builder builder;
	if (which % 2 == 1) {
		builder.setTakesValue(true);
	}
	which /= 2;
	if (which % 2 == 1) {
		builder.setHelp("Help about X");
	}
	which /= 2;
	if (which < 2) {
		builder.setShortName('x');
	}
	if (which > 0) {
		builder.setLongName("xlong");
	}
	return builder.build();
}

TEST_CASE("Print CommandLineArgument") {
	static const char* solutions[] = {
		" -x\n",
		" -x ARG\n",
		" -x Help about X\n",
		" -x ARG Help about X\n",
		" -x, --xlong\n",
		" -x, --xlong ARG\n",
		" -x, --xlong Help about X\n",
		" -x, --xlong ARG Help about X\n",
		"     --xlong\n",
		"     --xlong ARG\n",
		"     --xlong Help about X\n",
		"     --xlong ARG Help about X\n"
	};

	for (int i = 0; i < 12; ++i) {
		CAPTURE(i);
		auto arg = buildCLA(i);
		testPrintCLA(arg, solutions[i]);
	}
}

TEST_CASE("Print ApplicationHelp with all optional information") {
	auto help = ApplicationHelp::Builder()
	                .setName("AppName")
	                .setVersion({ 3, 11 })
	                .setAuthor("Author")
	                .setAbout("This is an app.")
	                .addArgument(CommandLineArgument::Builder()
	                                 .setShortName('x')
	                                 .setLongName("xlong")
	                                 .setHelp("Help about X")
	                                 .setTakesValue(false)
	                                 .build())
	                .addArgument(CommandLineArgument::Builder()
	                                 .setShortName('y')
	                                 .setLongName("ylong")
	                                 .setHelp("Help about Y")
	                                 .setTakesValue(true)
	                                 .build())
	                .build();
	testPrintAH(help, "AppName 3.11\nAuthor\nThis is an app.\n\nOptions:\n"
	                  " -y, --ylong ARG Help about Y\n\nFlags:\n"
	                  " -x, --xlong Help about X\n");
}

TEST_CASE("Print ApplicationHelp with no optional information") {
	auto help = ApplicationHelp::Builder().setName("AppName").build();
	testPrintAH(help, "AppName 1.0\n");
}

TEST_CASE("Print ApplicationHelp with some optional information (flags only)") {
	auto help = ApplicationHelp::Builder()
	                .setName("AppName")
	                .setAbout("This is a boring app.")
	                .addArgument(CommandLineArgument::Builder()
	                                 .setShortName('x')
	                                 .build())
	                .build();
	testPrintAH(help, "AppName 1.0\nThis is a boring app.\n\nFlags:\n -x\n");
}

TEST_CASE("Print ApplicationHelp with some optional information (opts only)") {
	auto help = ApplicationHelp::Builder()
	                .setName("AppName")
	                .setAbout("This is a boring app.")
	                .addArgument(CommandLineArgument::Builder()
	                                 .setShortName('x')
	                                 .setTakesValue(true)
	                                 .build())
	                .build();
	testPrintAH(help, "AppName 1.0\nThis is a boring app.\n\nOptions:\n"
	                  " -x ARG\n");
}
