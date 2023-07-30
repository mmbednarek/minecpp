#include "PlayerInteraction.h"
#include "../Dispatcher.h"
#include "../PlayerManager.h"
#include "../World.h"

#include "minecpp/controller/block/Block.h"
#include "minecpp/controller/item/Item.h"
#include "minecpp/entity/Aliases.hpp"
#include "minecpp/entity/component/Abilities.h"
#include "minecpp/entity/component/Inventory.h"
#include "minecpp/entity/component/Location.h"
#include "minecpp/game/IEntitySystem.hpp"
#include "minecpp/repository/Block.h"
#include "minecpp/repository/Item.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine::service {

PlayerInteraction::PlayerInteraction(World &world, Dispatcher &dispatcher,
                                     controller::BlockManager &block_manager,
                                     controller::RootItem &root_item_controller) :
    m_world{world},
    m_dispatcher{dispatcher},
    m_block_manager{block_manager},
    m_root_item_controller{root_item_controller}
{
   controller::block::register_block_controllers(m_block_manager);
   controller::item::register_item_controllers(m_root_item_controller);
}

void PlayerInteraction::handle_start_digging(game::PlayerId player_id, int sequence_id,
                                             const game::BlockPosition &position)
{
   m_dispatcher.acknowledge_block_change(player_id, sequence_id);

   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-interaction: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   assert(entity->has_component<AbilitiesComponent>());

   if (entity->component<AbilitiesComponent>().abilities().may_build) {
      m_world.destroy_block(position);
      return;
   }
}

void PlayerInteraction::handle_cancel_digging(game::PlayerId /*player_id*/, int /*sequence_id*/,
                                              const game::BlockPosition & /*position*/)
{
   // TODO: Implement
}

void PlayerInteraction::handle_finish_digging(game::PlayerId player_id, int sequence_id,
                                              const game::BlockPosition &position)
{
   m_dispatcher.acknowledge_block_change(player_id, sequence_id);
   m_world.destroy_block(position);
}

void PlayerInteraction::handle_drop_active_item(game::PlayerId player_id, bool is_whole_stack)
{
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-interaction: player entity is invalid: {}", entity.err()->msg());
      return;
   }
   if (not entity->has_component<InventoryComponent>())
      return;

   entity->component<InventoryComponent>().drop_active_item(m_world, is_whole_stack);
}

void PlayerInteraction::handle_use_item_on(game::PlayerId player_id, int sequence_id, game::Face face,
                                           const game::BlockPosition &block_position,
                                           const math::Vector3f &cursor_position)
{
   auto state_id = m_world.block_at(block_position);
   if (state_id.has_failed())
      return;

   if (m_block_manager.on_player_action(m_world, player_id, *state_id, block_position, face,
                                        cursor_position)) {
      m_dispatcher.acknowledge_block_change(player_id, sequence_id);
      return;
   }

   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-interaction: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto &inventory = entity->component<entity::component::Inventory>();
   auto item_slot  = inventory.active_item();
   if (item_slot.count == 0)
      return;

   auto item = repository::Item::the().get_by_id(item_slot.item_id);
   if (item.has_failed())
      return;

   if (not item->is_block())
      return;

   auto block_id = repository::Block::the().find_id_by_tag(item->corresponding_block_tag());
   if (block_id.has_failed())
      return;

   if (not inventory.take_from_active_slot(m_dispatcher, 1))
      return;

   if (m_block_manager.on_player_place_block(m_world, player_id, static_cast<int>(*block_id), block_position,
                                             face, cursor_position)) {
      m_dispatcher.acknowledge_block_change(player_id, sequence_id);
   }
}

void PlayerInteraction::handle_interact(game::PlayerId player_id, game::EntityId entity_id,
                                        game::InteractionType interaction_type, math::Vector3f position,
                                        bool is_off_hand)
{
   spdlog::info("player-interaction: player {} is attacking entity {}", boost::uuids::to_string(player_id),
                entity_id);

   auto player_entity = this->m_world.player_entity(player_id);
   if (player_entity.has_failed()) {
      spdlog::warn("player-interaction: player entity is invalid: {}", player_entity.err()->msg());
      return;
   }
   if (not player_entity->has_component<LocationComponent>())
      return;

   auto interacted_entity = m_world.entity_system().entity(entity_id);
   if (not interacted_entity.is_valid()) {
      spdlog::warn("player-interaction: attacked entity is invalid: {}", player_entity.err()->msg());
      return;
   }

   if (not player_entity->has_component<InventoryComponent>())
      return;

   auto slot_item = player_entity->component<InventoryComponent>().active_item();
   m_root_item_controller.on_interact(m_world, slot_item.item_id, interaction_type, player_entity->id(),
                                      interacted_entity.id(), position, is_off_hand);
}

void PlayerInteraction::handle_use_item(game::PlayerId player_id, int sequence_id, bool /*is_off_hand*/)
{
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-interaction: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<InventoryComponent>()) {
      spdlog::error("player-interaction: player entity doesn't have inventory (entity_id:{})", entity->id());
      return;
   }

   auto slot_item = entity->component<InventoryComponent>().active_item();
   m_root_item_controller.on_item_use(m_world, player_id, entity->id(), slot_item.item_id);

   m_dispatcher.acknowledge_block_change(player_id, sequence_id);
}

void PlayerInteraction::handle_animate_hand(game::PlayerId player_id, game::EntityAnimation hand_animation)
{
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-interaction: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (entity->has_component<entity::component::Location>())
      return;

   m_dispatcher.animate_player_entity(player_id, entity->id(),
                                      entity->component<entity::component::Location>().position(),
                                      hand_animation);
}

void PlayerInteraction::handle_release_used_item(game::PlayerId player_id)
{
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-interaction: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<InventoryComponent>()) {
      spdlog::error("player entity doesn't have inventory (entity_id:{})", entity->id());
      return;
   }

   auto slot_item = entity->component<InventoryComponent>().active_item();
   m_root_item_controller.on_released_item(m_world, slot_item.item_id, entity->id());
}

void PlayerInteraction::handle_swap_held_items(game::PlayerId /*player_id*/)
{
   // TODO: Implement
}

}// namespace minecpp::service::engine::service
