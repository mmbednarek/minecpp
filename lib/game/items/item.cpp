//
// Created by ego on 5/14/20.
//

#include "item.h"
Game::Item::Item(ItemId id, std::string_view tag_name, ItemGroup group)
    : id(id), tag_name(tag_name), group(group), max_stack_size(64),
      max_damage(0) {}

std::string_view Game::Item::tag() { return tag_name; }
