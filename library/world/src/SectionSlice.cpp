#include <minecpp/world/SectionSlice.h>
#include <unordered_map>
#include <utility>

namespace minecpp::world {

mb::result<game::LightValue> SectionSlice::light_value_at(game::LightType light_type,
                                                          const game::BlockPosition &pos)
{
   auto chunk_section_pos = pos.chunk_section_position();
   auto sec               = m_sections.find(chunk_section_pos.hash());
   if (sec == m_sections.end()) {
      return mb::error("no such section");
   }

   return sec->second.get_light(light_type, pos);
}

mb::emptyres SectionSlice::set_light_value_at(game::LightType light_type, const game::BlockPosition &pos,
                                              game::LightValue value)
{
   auto chunk_section_pos = pos.chunk_section_position();
   auto sec               = m_sections.find(chunk_section_pos.hash());
   if (sec == m_sections.end()) {
      return mb::error("no such section");
   }

   sec->second.set_light(light_type, pos, value);
   return mb::ok;
}

mb::result<mb::empty> SectionSlice::set_block_at(const game::BlockPosition &pos, game::BlockStateId state)
{
   auto chunk_section_pos = pos.chunk_section_position();
   auto sec               = m_sections.find(chunk_section_pos.hash());
   if (sec == m_sections.end()) {
      return mb::error("no such section");
   }

   sec->second.set_block(pos, state);
   return mb::ok;
}

mb::result<game::BlockStateId> SectionSlice::block_at(const game::BlockPosition &pos)
{
   auto chunk_section_pos = pos.chunk_section_position();
   auto sec               = m_sections.find(chunk_section_pos.hash());
   if (sec == m_sections.end()) {
      return mb::error("no such section");
   }

   return sec->second.get_block(pos);
}

world::Section &SectionSlice::operator[](game::SectionPosition position)
{
   if (not m_sections.contains(position.hash())) {
      m_sections.emplace(position.hash(), position.y());
   }
   return m_sections.at(position.hash());
}

SectionSlice::SectionSlice(const game::SectionRange &range, std::unordered_map<mb::u64, Section> sections) :
    m_range(range),
    m_sections(std::move(sections))
{
}

game::SectionRange SectionSlice::range() const
{
   return m_range;
}

}// namespace minecpp::world