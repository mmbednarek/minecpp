#pragma once
#include <string_view>
#include <ostream>

namespace Log {

class Logger {
public:
	Logger(std::string level, std::ostream& s);
	void operator <<(std::string_view msg);
private:
	void print_padded(int num);

	std::string level;
	std::ostream& s;
};

Logger& info();
Logger& debug();

}
