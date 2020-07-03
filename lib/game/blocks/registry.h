#pragma once
#include "block.h"
#include <nbt/tag.h>

namespace Game::Block {
extern std::array<const Block, 763> blocks;
size_t total_num_states();
uint32_t encode_state(std::string_view tag, NBT::TagMap &attribs);
void debug_block_info();
std::string_view tag_from_state_id(uint32_t state);
const Block &block_by_tag(std::string_view tag);
} // namespace Game::Block