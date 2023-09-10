#include "block/Block.h"
#include "block/Door.h"
#include "block/Fence.h"
#include "block/Foliage.h"
#include "block/Grass.h"
#include "block/Slab.h"
#include "block/Stairs.h"
#include "block/Torch.h"
#include "block/TrapDoor.h"
#include "block/Wood.h"
#include "BlockManager.h"
#include "minecpp/repository/Block.h"
#include <spdlog/spdlog.h>

namespace minecpp::controller::block {

void register_block_controllers(BlockManager &block_manager)
{
   for (auto wood_type_value : game::WoodType::Values) {
      game::WoodType wood_type{wood_type_value};

      if (auto wood_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_wood", wood_type.to_string()));
          wood_id.ok()) {
         block_manager.register_controller<controller::block::Wood>(*wood_id);
      } else {
         spdlog::error("no such block id minecraft:{}_wood", wood_type.to_string());
      }

      if (auto log_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_log", wood_type.to_string()));
          log_id.ok()) {
         block_manager.register_controller<controller::block::Wood>(*log_id);
      } else {
         spdlog::error("no such block id minecraft:{}_log", wood_type.to_string());
      }

      if (auto log_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:stripped_{}_log", wood_type.to_string()));
          log_id.ok()) {
         block_manager.register_controller<controller::block::Wood>(*log_id);
      } else {
         spdlog::error("no such block id minecraft:stripped_{}_log", wood_type.to_string());
      }

      if (auto door_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_door", wood_type.to_string()));
          door_id.ok()) {
         block_manager.register_controller<controller::block::Door>(*door_id);
      } else {
         spdlog::error("no such block id minecraft:{}_door", wood_type.to_string());
      }

      if (auto fence_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_fence", wood_type.to_string()));
          fence_id.ok()) {
         block_manager.register_controller<controller::block::Fence>(*fence_id);
      } else {
         spdlog::error("no such block id minecraft:{}_fence", wood_type.to_string());
      }

      if (auto stairs_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_stairs", wood_type.to_string()));
          stairs_id.ok()) {
         block_manager.register_controller<controller::block::Stairs>(*stairs_id);
      } else {
         spdlog::error("no such block id minecraft:{}_stairs", wood_type.to_string());
      }

      if (auto slab_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_slab", wood_type.to_string()));
          slab_id.ok()) {
         block_manager.register_controller<controller::block::Slab>(*slab_id);
      }

      if (auto trapdoor_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_trapdoor", wood_type.to_string()));
          trapdoor_id.ok()) {
         block_manager.register_controller<controller::block::TrapDoor>(*trapdoor_id);
      }
   }

   if (auto stairs_id = repository::Block::the().find_id_by_tag("minecraft:stone_stairs"); stairs_id.ok()) {
      block_manager.register_controller<controller::block::Stairs>(*stairs_id);
   }
   if (auto stairs_id = repository::Block::the().find_id_by_tag("minecraft:cobblestone_stairs");
       stairs_id.ok()) {
      block_manager.register_controller<controller::block::Stairs>(*stairs_id);
   }
   if (auto stairs_id = repository::Block::the().find_id_by_tag("minecraft:stone_brick_stairs");
       stairs_id.ok()) {
      block_manager.register_controller<controller::block::Stairs>(*stairs_id);
   }
   if (auto stairs_id = repository::Block::the().find_id_by_tag("minecraft:mossy_stone_brick_stairs");
       stairs_id.ok()) {
      block_manager.register_controller<controller::block::Stairs>(*stairs_id);
   }

   if (auto torch_id = repository::Block::the().find_id_by_tag("minecraft:torch"); torch_id.ok()) {
      block_manager.register_controller<controller::block::Torch>(*torch_id);
   }
   if (auto torch_id = repository::Block::the().find_id_by_tag("minecraft:wall_torch"); torch_id.ok()) {
      block_manager.register_controller<controller::block::Torch>(*torch_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:tall_grass"); block_id.ok()) {
      block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:poppy"); block_id.ok()) {
      block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:dandelion"); block_id.ok()) {
      block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:blue_orchid"); block_id.ok()) {
      block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:snow"); block_id.ok()) {
      block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:stone_slab"); block_id.ok()) {
      block_manager.register_controller<controller::block::Slab>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:cobblestone_slab"); block_id.ok()) {
      block_manager.register_controller<controller::block::Slab>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:stone_brick_slab"); block_id.ok()) {
      block_manager.register_controller<controller::block::Slab>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:mossy_stone_brick_slab");
       block_id.ok()) {
      block_manager.register_controller<controller::block::Slab>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:grass_block"); block_id.ok()) {
      block_manager.register_controller<controller::block::Grass>(*block_id);
   }
}

}// namespace minecpp::controller::block
