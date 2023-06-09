#include "minecpp/repository/Block.h"
#include <minecpp/controller/block/Wood.h>

namespace minecpp::controller::block {

namespace {
std::string_view face_to_axis(game::Face face)
{
   switch (face) {
   case game::Face::Bottom:
   case game::Face::Top: return "y";
   case game::Face::North:
   case game::Face::South: return "z";
   case game::Face::West:
   case game::Face::East: return "x";
   }
   return "x";
}

}// namespace

bool Wood::on_player_place_block(game::IWorld &world, game::PlayerId /*player_id*/, int block_id,
                                 game::BlockPosition position, game::Face face,
                                 const math::Vector3f & /*crosshair_position*/)
{
   const auto neighbour_position = position.neighbour_at(face);
   if (not verify_source_block(world, neighbour_position)) {
      return false;
   }

   auto block = repository::Block::the().get_by_id(block_id);
   auto state = repository::encode_block_by_tag(block->tag(), std::make_pair("axis", face_to_axis(face)));

   return world.set_block_at(neighbour_position, state).ok();
}
}// namespace minecpp::controller::block