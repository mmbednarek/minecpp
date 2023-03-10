#pragma once
#include "Game.h"

namespace minecpp::game {

enum class DamageSourceValue
{
   PlayerAttack,
   MobAttack,
   FallDamage,
   Projectile,
};

using DamageSource_Base =
        mb::enum_wrapper<DamageSourceValue, "PlayerAttack", "MobAttack", "FallDamage", "Projectile">;

class DamageSource : public DamageSource_Base
{
 public:
   MB_ENUM_TRAITS(DamageSource)

   MB_ENUM_FIELD(PlayerAttack)
   MB_ENUM_FIELD(MobAttack)
   MB_ENUM_FIELD(FallDamage)
   MB_ENUM_FIELD(Projectile)
};

using Health = float;

struct Damage
{
   Health amount{};
   DamageSource source;
   std::optional<EntityId> source_entity;
   EntityId target_entity{};
   math::Vector3 vector;
};

}// namespace minecpp::game