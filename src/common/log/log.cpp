#include "log.h"
#include <iostream>
#include <utility>
#include <chrono>
#include <iomanip>

namespace Log {

Logger::Logger(std::string level, std::ostream &s) :
	level(std::move(level)), s(s) {

}

void Logger::operator<<(std::string_view msg) {
	auto time = std::time(nullptr);
	auto now = std::localtime(&time);
	s << (now->tm_year + 1900) << '-';
	print_padded(now->tm_mon + 1);
	s << '-';
	print_padded(now->tm_mday);
	s << ' ';
	print_padded(now->tm_hour);
	s << ':';
	print_padded(now->tm_min);
	s << ':';
	print_padded(now->tm_sec);
	s << " [" << level << "] ";
	s << msg << std::endl;
}

void Logger::print_padded(int num) {
	s << std::setfill('0') << std::setw(2) << num;
}

static Logger log_info("INFO", std::cerr);
static Logger log_debug("DEBUG", std::cerr);

Logger& info() {
	return log_info;
}

Logger& debug() {
	return log_info;
}

}
