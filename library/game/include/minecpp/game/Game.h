#pragma once

#include "Types.hpp"

#include <mb/enum.h>
#include <mb/int.h>
#include <minecpp/nbt/block/Block.schema.h>
#include <minecpp/nbt/block/BlockState.schema.h>
#include <minecpp/nbt/common/Common.schema.h>
#include <minecpp/proto/common/Common.pb.h>
#include <minecpp/proto/entity/Entity.pb.h>

#include <utility>

namespace minecpp::game {

enum class ItemOperation : int
{
   Digging         = 0,
   CanceledDigging = 1,
   FinishedDigging = 2,
   DropAllItems    = 3,
   DropItem        = 4,
   ReleaseUseItem  = 5,
   SwapHeldItems   = 6,
};

enum class FaceMask : mb::u8
{
   None   = 0,
   Bottom = 1u << 0,
   Top    = 1u << 1,
   North  = 1u << 2,
   South  = 1u << 3,
   West   = 1u << 4,
   East   = 1u << 5,
   All    = 0x40u - 1u,
};

// TODO: Introduce common mask traits

inline FaceMask operator|(FaceMask lhs, FaceMask rhs)
{
   return static_cast<FaceMask>(static_cast<std::underlying_type_t<FaceMask>>(lhs) |
                                static_cast<std::underlying_type_t<FaceMask>>(rhs));
}

inline FaceMask operator~(FaceMask source)
{
   return static_cast<FaceMask>((~static_cast<std::underlying_type_t<FaceMask>>(source)) &
                                static_cast<std::underlying_type_t<FaceMask>>(FaceMask::All));
}

inline FaceMask &operator|=(FaceMask &lhs, FaceMask rhs)
{
   lhs = lhs | rhs;
   return lhs;
}

inline FaceMask operator-(FaceMask lhs, FaceMask rhs)
{
   return static_cast<FaceMask>(static_cast<std::underlying_type_t<FaceMask>>(lhs) &
                                static_cast<std::underlying_type_t<FaceMask>>(~rhs));
}

inline bool operator&(FaceMask lhs, FaceMask rhs)
{
   return (static_cast<std::underlying_type_t<FaceMask>>(lhs) &
           static_cast<std::underlying_type_t<FaceMask>>(rhs)) != 0u;
}

FaceMask face_mask_from_nbt(const nbt::common::FaceMask &nbt_mask);

enum class WoodTypeValue
{
   Oak,
   Spruce,
   Birch,
   Jungle,
   Acacia,
   DarkOak,
   Mangrove
};

using WoodType_Base =
        mb::enum_wrapper<WoodTypeValue, "oak", "spruce", "birch", "jungle", "acacia", "dark_oak", "mangrove">;

class WoodType : public WoodType_Base
{
 public:
   MB_ENUM_TRAITS(WoodType)

   MB_ENUM_FIELD(Oak)
   MB_ENUM_FIELD(Spruce)
   MB_ENUM_FIELD(Birch)
   MB_ENUM_FIELD(Jungle)
   MB_ENUM_FIELD(Acacia)
   MB_ENUM_FIELD(DarkOak)
   MB_ENUM_FIELD(Mangrove)
};

enum class HeightTypeValues
{
   MotionBlocking,
   WorldSurface,
   LightBlocking
};

using HeightType_Base =
        mb::enum_wrapper<HeightTypeValues, "MOTION_BLOCKING", "WORLD_SURFACE", "LIGHT_BLOCKING">;

class HeightType final : public HeightType_Base
{
 public:
   MB_ENUM_TRAITS(HeightType);

   MB_ENUM_FIELD(MotionBlocking)
   MB_ENUM_FIELD(WorldSurface)
   MB_ENUM_FIELD(LightBlocking)
};

struct BlockStateInfo
{
   LightValue luminance{};
   LightValue opacity{};
   bool blocks_movement{};
   FaceMask solid_faces{};

   static BlockStateInfo from_nbt(const nbt::block::BlockState &state)
   {
      return {static_cast<LightValue>(state.luminance), static_cast<LightValue>(state.opacity),
              state.blocks_movement != 0, face_mask_from_nbt(state.solid_faces)};
   }
};

enum class EquipmentSlotValue
{
   MainHand,
   OffHand,
   Boots,
   Leggings,
   Chestplate,
   Helmet
};

using EquipmentSlot_Base = mb::enum_wrapper<EquipmentSlotValue, "MAIN_HAND", "OFF_HAND", "BOOTS", "LEGGINGS",
                                            "CHESTPLATE", "HELMET">;

class EquipmentSlot final : public EquipmentSlot_Base
{
 public:
   MB_ENUM_TRAITS(EquipmentSlot);

   MB_ENUM_FIELD(MainHand)
   MB_ENUM_FIELD(OffHand)
   MB_ENUM_FIELD(Boots)
   MB_ENUM_FIELD(Leggings)
   MB_ENUM_FIELD(Chestplate)
   MB_ENUM_FIELD(Helmet)

   [[nodiscard]] proto::entity::EquipmentSlot to_proto() const;
};

struct ItemSlot
{
   ItemId item_id;
   int count;
};

enum EntityAnimationValue
{
   SwingMainArm,
   TakeDamage,
   LeaveBed,
   SwingOffHand,
   CriticalEffect,
   MagicCriticalEffect,
};

using EntityAnimation_Base = mb::enum_wrapper<EntityAnimationValue, "SwingMainArm", "TakeDamage", "LeaveBed",
                                              "SwingOffHand", "CriticalEffect", "MagicCriticalEffect">;

class EntityAnimation : public EntityAnimation_Base
{
 public:
   MB_ENUM_TRAITS(EntityAnimation)

   MB_ENUM_FIELD(SwingMainArm)
   MB_ENUM_FIELD(TakeDamage)
   MB_ENUM_FIELD(LeaveBed)
   MB_ENUM_FIELD(SwingOffHand)
   MB_ENUM_FIELD(CriticalEffect)
   MB_ENUM_FIELD(MagicCriticalEffect)

   proto::common::EntityAnimation to_proto();
};

enum class InteractionTypeValue
{
   Standard,
   Attack
};

using InteractionType_Base = mb::enum_wrapper<InteractionTypeValue, "standard", "attack">;

class InteractionType : public InteractionType_Base
{
 public:
   MB_ENUM_TRAITS(InteractionType)

   MB_ENUM_FIELD(Standard)
   MB_ENUM_FIELD(Attack)

   [[nodiscard]] static InteractionType from_proto(proto::common::InteractionType type);
};

}// namespace minecpp::game