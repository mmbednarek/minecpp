#include "state.h"
#include <cstdarg>

namespace Game::Block {

BoolProperty::BoolProperty(std::string_view name) : Property(name) {}

int BoolProperty::num_states() const { return 2; }

bool BoolProperty::value(int state) const { return state; }

} // namespace Game::Block