#include <minecpp/game/item/Item.h>

namespace minecpp::game::item {

Item::Item(Item::Details details) :
    m_tag(std::string(details.tag)),
    m_is_block(details.is_block),
    m_corresponding_block_tag(details.corresponding_block_tag)
{
}

}// namespace minecpp::game::item
