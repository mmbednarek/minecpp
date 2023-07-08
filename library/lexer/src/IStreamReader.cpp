#include "IStreamReader.h"

namespace minecpp::lexer {

IStreamReader::IStreamReader(std::istream &stream) :
   m_stream(stream)
{
}

bool IStreamReader::has_next()
{
   return m_stream.readsome(&m_next_char, sizeof(char)) == 1;
}

char IStreamReader::next()
{
   return m_next_char;
}

void IStreamReader::step_back() {
   m_stream.seekg(-1, std::ios::cur);
}

}

