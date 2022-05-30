#include <minecpp/game/item/item.h>

namespace minecpp::game::item {

Item::Item(Item::Details details) :
    m_tag(std::string(details.tag)),
    m_group(details.group),
    m_max_stack_size(details.max_stack_size),
    m_is_block(details.is_block),
    m_corresponding_block_tag(details.corresponding_block_tag)
{
}

}// namespace minecpp::game::item
