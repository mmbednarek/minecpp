#include "reader.h"

namespace Utils {

Reader::Reader(std::istream& s) : stream(s) {
}

std::vector<uint8_t> Reader::read_byte_vec() const {
	auto size = read_bswap<int>();
	std::vector<uint8_t> v(size);
	stream.read((char*) v.data(), size);
	return v;
}

std::string Reader::read_string() const {
	auto size = read_bswap<short>();
	char s[size];
	stream.read(s, size);
	return std::string(s, size);
}

float Reader::read_float() const {
	int v;
	stream.read((char*) &v, sizeof(int));
	v = boost::endian::big_to_native(v);
	return *reinterpret_cast<float*>(&v);
}

double Reader::read_double() const {
	long long v;
	stream.read((char*) &v, sizeof(long long));
	v = boost::endian::big_to_native(v);
	return *reinterpret_cast<double*>(&v);
}

std::istream& Reader::get_stream() {
	return stream;
}

}
