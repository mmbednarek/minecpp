#include "Lexer.h"

namespace minecpp::tool::snbt_parser {

[[nodiscard]] inline static bool is_white_space(int ch)
{
   return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

Lexer::Lexer(Reader &reader) :
    m_reader(reader)
{
}

std::vector<Token> Lexer::lex()
{
   while (m_reader.has_next()) {
      auto ch = m_reader.next();
      if ((unsigned char) ch == 0xff)
         break;

      if (m_state == State::String) {
         switch (ch) {
         case '\\': m_state = State::StringEscape; continue;
         case '"':
            m_state = State::Normal;
            m_result.push_back(Token{.type = TokenType::String, .value = m_identifier});
            m_identifier.clear();
            continue;
         }
         m_identifier.push_back(static_cast<char>(ch));
         continue;
      }
      if (m_state == State::StringEscape) {
         switch (ch) {
         case '\\': m_identifier.push_back('\\'); break;
         case 'n': m_identifier.push_back('\n'); break;
         case 't': m_identifier.push_back('\t'); break;
         case 'r': m_identifier.push_back('\r'); break;
         }
         m_state = State::String;
         continue;
      }

      if (is_white_space(ch)) {
         push_identifier();
         continue;
      }

      switch (ch) {
      case ':':
         push_identifier();
         push_special_token(TokenType::Colon);
         continue;
      case '{':
         push_identifier();
         push_special_token(TokenType::LeftBrace);
         continue;
      case '}':
         push_identifier();
         push_special_token(TokenType::RightBrace);
         continue;
      case '[':
         push_identifier();
         push_special_token(TokenType::LeftSquareBracket);
         continue;
      case ']':
         push_identifier();
         push_special_token(TokenType::RightSquareBracket);
         continue;
      case ',':
         push_identifier();
         push_special_token(TokenType::Comma);
         continue;
      case '"':
         push_identifier();
         m_state = State::String;
         continue;
      }

      m_identifier.push_back(static_cast<char>(ch));
   }
   push_identifier();

   return m_result;
}

static TokenType deduce_token_type(const std::string &token)
{
   if (token.starts_with('"')) {
      return TokenType::String;
   }
   if ((token.front() >= '0' && token.front() <= '9') || token.front() == '-') {
      switch (token.back()) {
      case 'f':
      case 'F': return TokenType::Float;
      case 'd':
      case 'D': return TokenType::Double;
      case 'b':
      case 'B': return TokenType::Byte;
      case 's':
      case 'S': return TokenType::Short;
      case 'i':
      case 'I': return TokenType::Int;
      case 'L':
      case 'l': return TokenType::Long;
      }

      return TokenType::Int;
   }
   return TokenType::Identifier;
}

void Lexer::push_identifier()
{
   if (m_identifier.empty())
      return;

   m_result.push_back(Token{
           .type  = deduce_token_type(m_identifier),
           .value = m_identifier,
   });
   m_identifier.clear();
}

void Lexer::push_special_token(TokenType type)
{
   m_result.push_back(Token{.type = type});
}

StringReader::StringReader(std::string_view data) :
    m_data(data)
{
}

bool StringReader::has_next()
{
   return m_at < m_data.size();
}

char StringReader::next()
{
   return m_data[m_at++];
}

IStreamReader::IStreamReader(std::istream &stream) :
    m_stream(stream)
{
}

bool IStreamReader::has_next()
{
   return not m_stream.eof();
}

char IStreamReader::next()
{
   return static_cast<char>(m_stream.get());
}
}// namespace minecpp::tool::snbt_parser