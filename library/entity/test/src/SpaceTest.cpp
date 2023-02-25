#include <gtest/gtest.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/EntitySystem.h>
#include <minecpp/entity/factory/Player.h>

using minecpp::entity::EntitySystem;

TEST(Entity, EntitySystem_Nearest)
{
   EntitySystem system;

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
   EntitySystem system;
   auto entity = system.create_spatial_entity({4, 5, 6}, {1, 1, 1});

   minecpp::proto::entity::v1::Entity proto_entity;
   entity.serialize_to_proto(&proto_entity);

   EXPECT_EQ(proto_entity.entity_id(), entity.id());
   EXPECT_EQ(proto_entity.position().x(), 4);
   EXPECT_EQ(proto_entity.position().y(), 5);
   EXPECT_EQ(proto_entity.position().z(), 6);
}

TEST(Entity, ProtoPlayerSerialize)
{
   EntitySystem system;
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
}
