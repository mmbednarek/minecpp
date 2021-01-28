#include <minecpp/game/item/item.h>

namespace Game {

Item::Item(ItemId id, std::string_view tag_name, ItemGroup group)
    : _id(id), tag_name(tag_name), group(group), max_stack_size(64),
      max_damage(0) {}

std::string_view Item::tag() const { return tag_name; }

ItemId Item::id() const { return _id; }

}
