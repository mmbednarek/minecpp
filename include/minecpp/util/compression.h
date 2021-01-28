#pragma once
#include <boost/iostreams/filtering_stream.hpp>
#include <iostream>

namespace minecpp::util {
class GZipInputStream
    : public boost::iostreams::filtering_stream<boost::iostreams::input> {
 public:
   explicit GZipInputStream(std::istream &s);
};

class ZlibInputStream
    : public boost::iostreams::filtering_stream<boost::iostreams::input> {
 public:
   explicit ZlibInputStream(std::istream &s);
};

class ZlibOutputStream
    : public boost::iostreams::filtering_stream<boost::iostreams::input> {
 public:
   explicit ZlibOutputStream(std::istream &s);
};

void compress_zlib(std::vector<char> &sink, std::istream &s);

} // namespace minecpp::util