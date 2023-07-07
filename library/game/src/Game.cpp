#include <minecpp/game/Game.h>

namespace minecpp::game {

namespace pb_common  = proto::common;
namespace pb_entity  = proto::entity;
namespace nbt_common = nbt::common;

FaceMask face_mask_from_nbt(const nbt_common::FaceMask &nbt_mask)
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

pb_entity::EquipmentSlot EquipmentSlot::to_proto() const
{
   using pb_entity::EquipmentSlot;

   switch (this->value()) {
   case EquipmentSlotValue::MainHand: return EquipmentSlot::MAIN_HAND;
   case EquipmentSlotValue::OffHand: return EquipmentSlot::OFF_HAND;
   case EquipmentSlotValue::Boots: return EquipmentSlot::BOOTS;
   case EquipmentSlotValue::Leggings: return EquipmentSlot::LEGGINGS;
   case EquipmentSlotValue::Chestplate: return EquipmentSlot::CHESTPLATE;
   case EquipmentSlotValue::Helmet: return EquipmentSlot::HELMET;
   }

   assert(false);
   return {};
}

pb_common::EntityAnimation EntityAnimation::to_proto()
{
   return static_cast<pb_common::EntityAnimation>(index());
}

InteractionType InteractionType::from_proto(pb_common::InteractionType type)
{
   if (type == pb_common::Attack)
      return Attack;

   return Standard;
}

}// namespace minecpp::game