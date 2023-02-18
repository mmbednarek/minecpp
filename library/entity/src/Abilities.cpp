#include <minecpp/entity/Abilities.h>

namespace minecpp::entity {

Abilities Abilities::from_proto(const proto::entity::v1::Abilities &abilities)
{
   return {
           .fly_speed     = abilities.fly_speed(),
           .flying        = abilities.flying(),
           .instant_build = abilities.instant_build(),
           .invulnerable  = abilities.invulnerable(),
           .may_build     = abilities.may_build(),
           .may_fly       = abilities.may_fly(),
           .walk_speed    = abilities.walk_speed(),
   };
}

minecpp::proto::entity::v1::Abilities Abilities::to_proto() const
{
   minecpp::proto::entity::v1::Abilities abilities;
   abilities.set_walk_speed(this->walk_speed);
   abilities.set_fly_speed(this->fly_speed);
   abilities.set_flying(this->flying);
   abilities.set_instant_build(this->instant_build);
   abilities.set_invulnerable(this->invulnerable);
   abilities.set_may_build(this->may_build);
   abilities.set_may_fly(this->may_fly);
   return abilities;
}

}// namespace minecpp::entity