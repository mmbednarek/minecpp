#include <minecpp/game/block/state.h>
#include <cstdarg>

namespace minecpp::game::block {

BoolAttribute::BoolAttribute(std::string_view name) : Attribute(name) {}

int BoolAttribute::num_states() const { return 2; }

bool BoolAttribute::value(int state) const { return state == 0; }

} // namespace minecpp::game::block