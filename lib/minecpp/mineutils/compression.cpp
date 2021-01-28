#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <minecpp/mineutils/compression.h>

namespace Utils {

GZipInputStream::GZipInputStream(std::istream &s) {
   push(boost::iostreams::gzip_decompressor());
   push(s);
}

ZlibInputStream::ZlibInputStream(std::istream &s) {
   push(boost::iostreams::zlib_decompressor());
   push(s);
}

ZlibOutputStream::ZlibOutputStream(std::istream &s) {
   push(boost::iostreams::zlib_compressor());
   push(s);
}

void compress_zlib(std::vector<char> &sink, std::istream &s) {
   boost::iostreams::filtering_ostream filter;
   filter.push(boost::iostreams::zlib_compressor());
   filter.push(boost::iostreams::back_inserter(sink));
   boost::iostreams::copy(s, filter);
}

}// namespace Utils
