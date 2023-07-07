#pragma once

#include "Ast.h"

#include <ostream>

void generate_output(const std::vector<Syntax::Ast::Node> &nodes, std::ostream &out);
