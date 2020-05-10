#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include "compression.h"

namespace Utils {

GZipInputStream::GZipInputStream(std::istream& s) {
	push(boost::iostreams::gzip_decompressor());
	push(s);
}

ZlibInputStream::ZlibInputStream(std::istream& s) {
	push(boost::iostreams::zlib_decompressor());
	push(s);
}

}
