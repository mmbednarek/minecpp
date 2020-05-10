#pragma once
#include <boost/iostreams/filtering_stream.hpp>
#include <istream>

namespace Utils {
	class GZipInputStream : public boost::iostreams::filtering_stream<boost::iostreams::input> {
	public:
		explicit GZipInputStream(std::istream& s);
	};

	class ZlibInputStream : public boost::iostreams::filtering_stream<boost::iostreams::input> {
	public:
		explicit ZlibInputStream(std::istream& s);
	};
}