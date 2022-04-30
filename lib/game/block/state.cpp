#include <minecpp/game/block/state.h>
#include <cstdarg>
#include "minecpp/repository/state.h"


namespace minecpp::game::block {

std::vector<BoolAttribute *> g_bool_attribs;
std::vector<Attribute *> g_int_attribs;
std::vector<Attribute *> g_enum_attribs;

BoolAttribute::BoolAttribute(std::string_view tag, std::string_view name) : Attribute(tag, name) {
   g_bool_attribs.push_back(this);
}

int BoolAttribute::num_states() const { return 2; }

bool BoolAttribute::value(int state) const { return state == 0; }

}
// namespace minecpp::game::block