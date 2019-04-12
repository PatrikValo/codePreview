#include "Print.hpp"
#include "ApplicationHelp.hpp"
#include "CommandLineArgument.hpp"

void printCommandLineArgument(const CommandLineArgument& arg, std::ostream& stream) {
	if (arg.short_name != ' ') {
		stream << " -" << arg.short_name;
	} else {
		stream << "    ";
	}

	if (arg.short_name != ' ' && !arg.long_name.empty()) {
		stream << ",";
	}
	if (!arg.long_name.empty()) {
		stream << " --" << arg.long_name;
	}
	if (arg.takes_value) {
		stream << " ARG";
	}
	if (!arg.help.empty()) {
		stream << ' ' << arg.help << '\n';
	} else {
		stream << '\n';
	}
}

void printApplicationHelp(const ApplicationHelp& app, std::ostream& stream) {
	stream << app.name << ' ' << app.version.m_major << '.' << app.version.m_minor << '\n';
	if (!app.author.empty()) {
		stream << app.author << '\n';
	}
	if (!app.about.empty()) {
		stream << app.about << '\n';
	}

	bool options = false;

	for (const CommandLineArgument& arg : app.arguments) {
		if (arg.takes_value) {
			if (!options) {
				stream << '\n'
				       << "Options:\n";
				options = true;
			}
			printCommandLineArgument(arg, stream);
		}
	}

	options = false;

	for (const CommandLineArgument& arg : app.arguments) {
		if (!arg.takes_value) {
			if (!options) {
				stream << '\n'
				       << "Flags:\n";
				options = true;
			}
			printCommandLineArgument(arg, stream);
		}
	}
}
