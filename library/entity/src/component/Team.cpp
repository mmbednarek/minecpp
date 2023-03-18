#include <minecpp/entity/component/Team.h>
#include <minecpp/repository/Item.h>

namespace minecpp::entity::component {

Team::Team(game::Team team) :
    m_team(team)
{
}

game::Team Team::team() const
{
   return m_team;
}

void Team::serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const
{
   auto material = m_team.material();

   auto helmet_id = repository::Item::the().lookup_id(fmt::format("minecraft:{}_helmet", material));
   assert(helmet_id.ok());
   auto *helmet = entity->add_equipment();
   helmet->set_slot(proto::entity::v1::EquipmentSlot::HELMET);
   helmet->mutable_item()->mutable_item_id()->set_id(static_cast<uint32_t>(*helmet_id));
   helmet->mutable_item()->set_count(1);

   auto chestplate_id = repository::Item::the().lookup_id(fmt::format("minecraft:{}_chestplate", material));
   assert(chestplate_id.ok());
   auto *chestplate = entity->add_equipment();
   chestplate->set_slot(proto::entity::v1::EquipmentSlot::CHESTPLATE);
   chestplate->mutable_item()->mutable_item_id()->set_id(static_cast<uint32_t>(*chestplate_id));
   chestplate->mutable_item()->set_count(1);

   auto leggings_id = repository::Item::the().lookup_id(fmt::format("minecraft:{}_leggings", material));
   assert(leggings_id.ok());
   auto *leggings = entity->add_equipment();
   leggings->set_slot(proto::entity::v1::EquipmentSlot::LEGGINGS);
   leggings->mutable_item()->mutable_item_id()->set_id(static_cast<uint32_t>(*leggings_id));
   leggings->mutable_item()->set_count(1);

   auto boots_id = repository::Item::the().lookup_id(fmt::format("minecraft:{}_boots", material));
   assert(boots_id.ok());
   auto *boots = entity->add_equipment();
   boots->set_slot(proto::entity::v1::EquipmentSlot::BOOTS);
   boots->mutable_item()->mutable_item_id()->set_id(static_cast<uint32_t>(*boots_id));
   boots->mutable_item()->set_count(1);
}

void Team::send_team_equipment(game::IDispatcher &dispatcher, game::PlayerId player_id)
{
   auto material = m_team.material();

   auto helmet_id = repository::Item::the().lookup_id(fmt::format("minecraft:{}_helmet", material));
   assert(helmet_id.ok());
   dispatcher.set_inventory_slot(player_id, *helmet_id, 5, 1);

   auto chestplate_id = repository::Item::the().lookup_id(fmt::format("minecraft:{}_chestplate", material));
   assert(chestplate_id.ok());
   dispatcher.set_inventory_slot(player_id, *chestplate_id, 6, 1);

   auto leggings_id = repository::Item::the().lookup_id(fmt::format("minecraft:{}_leggings", material));
   assert(leggings_id.ok());
   dispatcher.set_inventory_slot(player_id, *leggings_id, 7, 1);

   auto boots_id = repository::Item::the().lookup_id(fmt::format("minecraft:{}_boots", material));
   assert(boots_id.ok());
   dispatcher.set_inventory_slot(player_id, *boots_id, 8, 1);
}

void Team::increment_used_apples()
{
   ++m_used_apple_count;
}

void Team::increment_used_arrows()
{
   ++m_used_arrow_count;
}

int Team::used_apple_count() const
{
   return m_used_apple_count;
}

int Team::used_arrow_count() const
{
   return m_used_arrow_count;
}

void Team::reset_counters()
{
   m_used_apple_count = 0;
   m_used_arrow_count = 0;
}

}// namespace minecpp::entity::component
