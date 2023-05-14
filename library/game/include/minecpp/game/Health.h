#pragma once
#include <mb/enum.h>
#include <minecpp/game/Types.hpp>
#include <minecpp/math/Vector3.h>

namespace minecpp::game {

enum class DamageSourceValue
{
   PlayerAttack,
   MobAttack,
   FallDamage,
   Projectile,
   VoidDamage,
   CommandKill,
};

using DamageSource_Base = mb::enum_wrapper<DamageSourceValue, "PlayerAttack", "MobAttack", "FallDamage",
                                           "Projectile", "VoidDamage", "CommandKill">;

class DamageSource : public DamageSource_Base
{
 public:
   MB_ENUM_TRAITS(DamageSource)

   MB_ENUM_FIELD(PlayerAttack)
   MB_ENUM_FIELD(MobAttack)
   MB_ENUM_FIELD(FallDamage)
   MB_ENUM_FIELD(Projectile)
   MB_ENUM_FIELD(VoidDamage)
   MB_ENUM_FIELD(CommandKill)
};

using Health = float;

struct Damage
{
   Health amount{};
   DamageSource source;
   std::optional<EntityId> source_entity;
   EntityId target_entity{};
   math::Vector3 vector{};
};

}// namespace minecpp::game