#include <minecpp/game/Abilities.h>

namespace minecpp::game {

Abilities Abilities::from_proto(const proto::entity::Abilities &abilities)
{
   return {
           .fly_speed     = abilities.fly_speed(),
           .flying        = abilities.flying(),
           .instant_build = abilities.instant_build(),
           .invulnerable  = abilities.invulnerable(),
           .may_build     = abilities.may_build(),
           .may_fly       = abilities.may_fly(),
           .field_of_view = abilities.walk_speed(),
   };
}

minecpp::proto::entity::Abilities Abilities::to_proto() const
{
   minecpp::proto::entity::Abilities abilities;
   abilities.set_walk_speed(this->field_of_view);
   abilities.set_fly_speed(this->fly_speed);
   abilities.set_flying(this->flying);
   abilities.set_instant_build(this->instant_build);
   abilities.set_invulnerable(this->invulnerable);
   abilities.set_may_build(this->may_build);
   abilities.set_may_fly(this->may_fly);
   return abilities;
}

}// namespace minecpp::game