#ifndef COMMAND_LINE_ARGUMENT_HPP
#define COMMAND_LINE_ARGUMENT_HPP
#include <string>

struct CommandLineArgument {
	class Builder;
	const char short_name;
	const std::string long_name;
	const std::string help;
	const bool takes_value;
	CommandLineArgument(char short_name, const std::string& long_name,
	    const std::string& help, bool takes_value)
	    : short_name(short_name)
	    , long_name(long_name)
	    , help(help)
	    , takes_value(takes_value) {
	}
};

class CommandLineArgument::Builder {
	char _short_name = ' ';
	std::string _long_name;
	std::string _help;
	bool _takes_value = false;

public:
	Builder& setShortName(char short_name) {
		_short_name = short_name;
		return *this;
	}

	Builder& setLongName(const std::string& long_name) {
		_long_name = long_name;
		return *this;
	}

	Builder& setHelp(const std::string& help) {
		_help = help;
		return *this;
	}

	Builder& setTakesValue(bool takes_value) {
		_takes_value = takes_value;
		return *this;
	}

	CommandLineArgument build() {
		return CommandLineArgument(_short_name, _long_name, _help, _takes_value);
	}
};

#endif // COMMAND_LINE_ARGUMENT_HPP
