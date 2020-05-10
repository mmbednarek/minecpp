#include "reader.h"
#include "../utils/endian.h"

namespace Region {

Reader::Reader(std::istream &s) : stream(s) {
}

std::vector<uint8_t> Reader::load_chunk(uint32_t x, uint32_t z) {
	stream.seekg(((x&31u) + ((z&31u) << 5u)) << 2u);

	uint32_t location;
	stream.read((char*) &location, sizeof(uint32_t));

	uint32_t offset = location << 8u;
	Utils::big_to_native(offset);
	if(!offset)
		return std::vector<uint8_t>();
	stream.seekg(offset << 12u);

	uint32_t data_size;
	stream.read((char*) &data_size, sizeof(uint32_t));
	Utils::big_to_native(data_size);

	uint8_t compression;
	stream.read((char*) &compression, sizeof(uint8_t));

	std::vector<uint8_t> data(data_size);
	stream.read((char*) data.data(), data_size);

	if(stream.gcount() != data_size) {
		throw std::runtime_error("could read enough data");
	}

	return data;
}

}
