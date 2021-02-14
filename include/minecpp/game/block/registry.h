#pragma once
#include "block.h"
#include <minecpp/nbt/tag.h>

namespace minecpp::game::block {
extern std::array<const Block, 763> blocks;
size_t total_num_states();
uint32_t encode_state(std::string_view tag, const nbt::CompoundContent &attribs);
void debug_block_info();
std::string_view tag_from_state_id(uint32_t state);
const Block &block_by_tag(std::string_view tag);
}// namespace minecpp::game::block