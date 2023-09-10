#include <minecpp/game/Game.h>

namespace minecpp::game {

FaceMask face_mask_from_nbt(const nbt::common::FaceMask &nbt_mask)
{
   FaceMask result{};
   result |= nbt_mask.down ? FaceMask::Bottom : FaceMask::None;
   result |= nbt_mask.up ? FaceMask::Top : FaceMask::None;
   result |= nbt_mask.north ? FaceMask::North : FaceMask::None;
   result |= nbt_mask.south ? FaceMask::South : FaceMask::None;
   result |= nbt_mask.west ? FaceMask::West : FaceMask::None;
   result |= nbt_mask.east ? FaceMask::East : FaceMask::None;
   return result;
}

}// namespace minecpp::game