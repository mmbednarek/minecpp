#pragma once
#include "IChunkSystem.h"
#include <minecpp/game/IWorld.h>

namespace minecpp::world {

class TemporaryWorld : public game::IBlockContainer
{
 public:
   explicit TemporaryWorld(IChunkSystem &chunk_system);

   mb::result<game::LightValue> get_light(game::LightType light_type,
                                          const game::BlockPosition &pos) override;
   mb::emptyres set_light(game::LightType light_type, const game::BlockPosition &pos,
                          game::LightValue value) override;
   mb::result<mb::empty> set_block(const game::BlockPosition &pos, game::BlockStateId state) override;
   mb::result<game::BlockStateId> get_block(const game::BlockPosition &pos) override;

   mb::result<int> height_at(game::HeightType type, const game::BlockPosition &pos);

 private:
   IChunkSystem &m_chunk_system;
};

}// namespace minecpp::world
