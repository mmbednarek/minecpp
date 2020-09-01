#pragma once
#include "token.h"
#include <string>
#include <variant>
#include <vector>

namespace Syntax::Ast {

struct Location {
   int line, col;

   Location() = default;
   explicit Location(Lex::Token t) : line(t.line), col(t.col) {}
};

struct SyntaxInfo {
   std::string version;
   Location loc;
};

struct PackageInfo {
   std::vector<std::string> package;
   Location loc;
};

enum class TypeName {
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

struct Attribute {
   int repeated = 0;
   std::string type;
   std::string name;  // C++ attribute name
   std::string label; // NBT label
   int pos;
   Location loc;
};

struct Message {
   std::string name;
   std::vector<Attribute> attributes;
   Location loc;
};

using Node = std::variant<
        SyntaxInfo,
        PackageInfo,
        Message>;

}// namespace Syntax::Ast