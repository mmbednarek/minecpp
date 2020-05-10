#pragma once
#include <streambuf>

namespace Utils {

class MemBuf : public std::streambuf {
public:
	MemBuf(char *ptr, size_t size);
};

}


