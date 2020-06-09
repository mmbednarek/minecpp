#pragma once
#include <istream>
#include <memory>
#include <cstdint>
#include <vector>
#include "../game/chunk/chunk.h"

namespace Region {

class Reader {
public:
	explicit Reader(std::istream& s);

	std::vector<uint8_t> load_chunk(int x, int z);
private:
	std::istream& stream;
};

}
