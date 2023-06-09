#include <minecpp/game/ChunkPosition.h>
#include <minecpp/world/TemporaryWorld.h>

namespace minecpp::world {

TemporaryWorld::TemporaryWorld(IChunkSystem &chunk_system) :
    m_chunk_system{chunk_system}
{
}

mb::result<game::LightValue> TemporaryWorld::light_value_at(game::LightType light_type,
                                                            const game::BlockPosition &pos)
{
   auto chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("no such chunk");
   }
   return chunk->light_value_at(light_type, pos);
}

mb::emptyres TemporaryWorld::set_light_value_at(game::LightType light_type, const game::BlockPosition &pos,
                                                game::LightValue value)
{
   auto chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("no such chunk");
   }
   return chunk->set_light_value_at(light_type, pos, value);
}

mb::result<mb::empty> TemporaryWorld::set_block_at(const game::BlockPosition &pos, game::BlockStateId state)
{
   auto chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("no such chunk");
   }
   return chunk->set_block_at(pos, state);
}

mb::result<game::BlockStateId> TemporaryWorld::block_at(const game::BlockPosition &pos)
{
   auto chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("no such chunk");
   }
   return chunk->block_at(pos);
}

mb::result<int> TemporaryWorld::height_at(game::HeightType type, const game::BlockPosition &pos)
{
   auto chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("no such chunk");
   }
   return chunk->height_at(type, pos);
}

}// namespace minecpp::world
