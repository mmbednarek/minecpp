#pragma once
#include <boost/endian/conversion.hpp>
#include <iostream>

namespace Front::Packet {

class Reader {
public:
	explicit Reader(std::istream& s);

	uint8_t read_byte();
	int read_varint();
	std::string read_string();

	template<typename T>
	T read_be() {
		T result;
		s.read((char*) &result, sizeof(T));
		result = boost::endian::big_to_native(result);
		return result;
	}
private:
	std::istream& s;
};

}
