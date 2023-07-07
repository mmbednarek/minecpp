#pragma once
#include "Section.h"
#include <minecpp/game/IWorld.hpp>
#include <minecpp/game/SectionRange.h>
#include <minecpp/proto/chunk/Chunk.pb.h>
#include <unordered_map>

namespace minecpp::world {

class SectionSlice : public game::ISectionSlice
{
 public:
   SectionSlice(const game::SectionRange &range, std::unordered_map<mb::u64, Section> sections);

   mb::result<game::LightValue> light_value_at(game::LightType light_type,
                                               const game::BlockPosition &pos) override;
   mb::emptyres set_light_value_at(game::LightType light_type, const game::BlockPosition &pos,
                                   game::LightValue value) override;
   mb::result<mb::empty> set_block_at(const game::BlockPosition &pos, game::BlockStateId state) override;
   mb::result<game::BlockStateId> block_at(const game::BlockPosition &pos) override;
   world::Section &operator[](game::SectionPosition position) override;

   [[nodiscard]] game::SectionRange range() const;

   [[nodiscard]] static SectionSlice from_proto(const proto::chunk::SectionSlice &slice);
   [[nodiscard]] proto::chunk::SectionSlice to_proto();

 private:
   game::SectionRange m_range;
   std::unordered_map<mb::u64, Section> m_sections;
};

}// namespace minecpp::world