#include <minecpp/util/scriptw.h>

namespace minecpp::util {

ScriptWriter::ScriptWriter(std::ostream &os) : os(os) {}

void ScriptWriter::ident() { ++ident_level; }

void ScriptWriter::deindent()
{
   if (ident_level == 0)
      return;
   --ident_level;
}

std::ostream &ScriptWriter::raw() { return os; }

void ScriptWriter::line() { os << "\n"; }

void ScriptWriter::descope_flat() { os << "}\n"; }

void ScriptWriter::line(std::string_view sv)
{
   apply_indent(os, ident_level);
   os << sv << '\n';
}

void ScriptWriter::descope()
{
   deindent();
   apply_indent(os, ident_level);
   os << "}\n";
}

}// namespace minecpp::util
