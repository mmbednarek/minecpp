#pragma once
#include <minecpp/container/BasicBuffer.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/IBlockController.hpp>

namespace minecpp::world::testing {

class BlockContainer : public game::IBlockContainer
{
   struct Block {
      game::BlockStateId state;
      std::array<game::LightValue, 2> light_values;
   };

 public:
   explicit BlockContainer(game::BlockRange range);


   mb::result<game::LightValue> get_light(game::LightType light_type,
                                          const game::BlockPosition &pos) override;
   mb::emptyres set_light(game::LightType light_type, const game::BlockPosition &pos,
                          game::LightValue value) override;
   mb::emptyres set_block(const game::BlockPosition &pos, game::BlockStateId state) override;
   mb::result<game::BlockStateId> get_block(const game::BlockPosition &pos) override;
   mb::emptyres fill(game::BlockRange range, game::BlockStateId state);
   mb::emptyres put_box(game::BlockRange range, game::BlockStateId state);

   [[nodiscard]] int light_changes() const {
      return m_light_changes;
   }

 private:
   [[nodiscard]] Block& access_block_at(game::BlockPosition position);

   game::BlockRange m_range;
   std::vector<Block> m_blocks;
   int m_light_changes{};
};

}// namespace minecpp::world::testing