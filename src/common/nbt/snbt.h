#pragma once
#include <string>
#include <ostream>
#include "parser.h"

namespace NBT {

void encode_snbt(std::ostream& s, TagPtr& p);
std::string as_string(TagPtr& p);

}

