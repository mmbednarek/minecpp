#pragma once
#include "Token.h"
#include <string>
#include <variant>
#include <vector>

namespace Syntax::Ast {

struct Location
{
   int line, col;

   Location() = default;

   explicit Location(const Lex::Token &t) :
       line(t.line),
       col(t.col)
   {
   }
};

struct SyntaxInfo
{
   std::string version;
   Location loc;
};

struct PackageInfo
{
   std::vector<std::string> package;
   Location loc;
};

enum class TypeName
{
   // native proto
   String,
   Double,
   Float,
   Int32,
   Int64,
   Bool,
   Bytes,

   // nbt extension
   Int8,
   Int16,
   Ints,
   Longs,
};

struct Attribute
{
   int repeated  = 0;
   bool optional = false;
   std::string type;
   std::vector<std::string> package;
   std::string name;   // C++ attribute name
   std::string label;  // NBT label
   std::string subtype;// Subtype for map
   int pos;
   Location loc;
};

struct Message
{
   std::string name;
   std::vector<Attribute> attributes;
   Location loc;
};

struct Import
{
   std::string path;
   Location loc;
};

using Node = std::variant<SyntaxInfo, PackageInfo, Message, Import>;

}// namespace Syntax::Ast