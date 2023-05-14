#include <gtest/gtest.h>
#include <minecpp/entity/EntitySystem.h>
#include <minecpp/entity/factory/Player.h>
#include <minecpp/game/player/Id.h>
#include <minecpp/world/IChunkSystem.h>

using minecpp::entity::EntitySystem;

class MockChunkSystem : public minecpp::world::IChunkSystem
{
 public:
   minecpp::world::Chunk *create_empty_chunk_at(const minecpp::game::ChunkPosition & /*position*/) override
   {
      return nullptr;
   }

   minecpp::world::Chunk *
   create_chunk_with_terrain_at(const minecpp::game::ChunkPosition & /*position*/) override
   {
      return nullptr;
   }

   minecpp::world::Chunk *chunk_at(const minecpp::game::ChunkPosition & /*position*/) override
   {
      return nullptr;
   }

   minecpp::world::ChunkState chunk_state_at(const minecpp::game::ChunkPosition & /*position*/) override
   {
      return minecpp::world::EMPTY;
   }

   void set_chunk_state_at(const minecpp::game::ChunkPosition & /*position*/,
                           minecpp::world::ChunkState /*state*/) override
   {
   }

   void save_chunk_at(const minecpp::game::ChunkPosition & /*position*/) override {}
};

TEST(Entity, EntitySystem_Nearest)
{
   MockChunkSystem chunk_system;
   EntitySystem system(chunk_system);

   auto id1 = system.create_spatial_entity({4, 5, 6}, {0.6, 1.8, 0.6});
   auto id2 = system.create_spatial_entity({-14, -15, -16}, {0.6, 1.8, 0.6});
   auto id3 = system.create_spatial_entity({-14, 15, -16}, {0.6, 1.8, 0.6});

   auto id_near = system.find_nearest_to({-12, -13, -15});

   EXPECT_TRUE(id_near.has_value());
   EXPECT_EQ(*id_near, id2.id());

   auto list1 = system.list_entities_in({-20, -20, -20}, {8, 8, 8});
   EXPECT_EQ(list1.size(), 2);
   EXPECT_NE(std::find(list1.begin(), list1.end(), id1.id()), list1.end());
   EXPECT_NE(std::find(list1.begin(), list1.end(), id2.id()), list1.end());

   auto list2 = system.list_entities_in({-20, -20, -20}, {-10, 20, -10});
   EXPECT_EQ(list2.size(), 2);
   EXPECT_NE(std::find(list2.begin(), list2.end(), id2.id()), list2.end());
   EXPECT_NE(std::find(list2.begin(), list2.end(), id3.id()), list2.end());
}

TEST(Entity, ProtoSerialize)
{
   MockChunkSystem chunk_system;
   EntitySystem system(chunk_system);
   auto entity = system.create_spatial_entity({4, 5, 6}, {1, 1, 1});

   minecpp::proto::entity::v1::Entity proto_entity;
   entity.serialize_to_proto(&proto_entity);

   EXPECT_EQ(proto_entity.entity_id(), entity.id());
   EXPECT_EQ(proto_entity.position().x(), 4);
   EXPECT_EQ(proto_entity.position().y(), 5);
   EXPECT_EQ(proto_entity.position().z(), 6);

   system.destroy_entity(entity.id());
   system.apply_pending_kills();
}

TEST(Entity, ProtoPlayerSerialize)
{
   MockChunkSystem chunk_system;
   EntitySystem system(chunk_system);
   minecpp::entity::factory::Player player(minecpp::game::player::read_id_from_nbt({1, 2, 3, 4}), "test");
   auto entity = player.create_entity({4, 5, 6}, system);

   minecpp::proto::entity::v1::PlayerEntity proto_entity;
   entity.serialize_player_to_proto(&proto_entity);

   EXPECT_EQ(proto_entity.entity_id(), entity.id());
   EXPECT_EQ(proto_entity.uuid().lower(), 8589934593);
   EXPECT_EQ(proto_entity.uuid().upper(), 17179869187);
   EXPECT_EQ(proto_entity.position().x(), 4);
   EXPECT_EQ(proto_entity.position().y(), 5);
   EXPECT_EQ(proto_entity.position().z(), 6);

   system.destroy_entity(entity.id());
   system.apply_pending_kills();
}
