#pragma once
#include "item.h"

namespace minecpp::game::item {

const Item &item_by_id(int id);
ItemId item_id_from_tag(std::string_view tag);

}// namespace minecpp::game::item
