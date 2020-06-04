#include "block.h"

#include <utility>

namespace Game::Block {

std::string_view Block::tag() const { return _tag; }

Block::Block(std::string_view tag, State properties) : _tag(tag), _state(std::move(properties)) {}

} // namespace Game::Block
