#pragma once
#include "Section.h"
#include <minecpp/game/Game.h>
#include <minecpp/game/World.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <unordered_map>

namespace minecpp::world {

class SectionSlice : public game::ISectionSlice
{
 public:
   SectionSlice(const game::SectionRange &range, std::unordered_map<mb::u64, Section> sections);

   mb::result<game::LightValue> get_light(game::LightType light_type,
                                          const game::BlockPosition &pos) override;
   mb::emptyres set_light(game::LightType light_type, const game::BlockPosition &pos,
                          game::LightValue value) override;

   world::Section &operator[](game::ChunkSectionPosition position) override;

   [[nodiscard]] constexpr game::SectionRange range() const
   {
      return m_range;
   }

   [[nodiscard]] static SectionSlice from_proto(const proto::chunk::v1::SectionSlice& slice);
   [[nodiscard]] proto::chunk::v1::SectionSlice to_proto();

 private:
   game::SectionRange m_range;
   std::unordered_map<mb::u64, Section> m_sections;
};

}// namespace minecpp::world