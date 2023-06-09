#pragma once
#include "IChunkSystem.h"
#include <minecpp/game/IWorld.hpp>

namespace minecpp::world {

class TemporaryWorld : public game::IBlockContainer
{
 public:
   explicit TemporaryWorld(IChunkSystem &chunk_system);

   mb::result<game::LightValue> light_value_at(game::LightType light_type,
                                               const game::BlockPosition &pos) override;
   mb::emptyres set_light_value_at(game::LightType light_type, const game::BlockPosition &pos,
                          game::LightValue value) override;
   mb::result<mb::empty> set_block_at(const game::BlockPosition &pos, game::BlockStateId state) override;
   mb::result<game::BlockStateId> block_at(const game::BlockPosition &pos) override;

   mb::result<int> height_at(game::HeightType type, const game::BlockPosition &pos);

 private:
   IChunkSystem &m_chunk_system;
};

}// namespace minecpp::world
