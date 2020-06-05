#include "state.h"
#include <cstdarg>

namespace Game::Block {

BoolAttribute::BoolAttribute(std::string_view name) : Attribute(name) {}

int BoolAttribute::num_states() const { return 2; }

bool BoolAttribute::value(int state) const { return state; }

} // namespace Game::Block