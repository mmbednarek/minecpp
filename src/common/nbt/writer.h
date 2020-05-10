#pragma once
#include <ostream>

namespace NBT {

class Writer {
public:
	Writer(std::ostream& s);
private:
	std::ostream& stream;
};

}


