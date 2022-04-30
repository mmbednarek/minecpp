#include <minecpp/game/state.h>
#include <minecpp/repository/state.h>
#include <minecpp/repository/block.h>
#include <gtest/gtest.h>

TEST(State, intstate) {
   minecpp::game::State state("t", 5, 10);
   ASSERT_EQ(state.value_count(), 5);
   ASSERT_EQ(state.index_from_value("7"), 2);
   ASSERT_EQ(state.value_from_index(3), "8");
}

TEST(State, boolstate) {
   minecpp::game::State state("t");
   ASSERT_EQ(state.value_count(), 2);
   ASSERT_EQ(state.index_from_value("true"), 1);
   ASSERT_EQ(state.value_from_index(0), "false");
}

TEST(State, enumstate) {
   minecpp::game::State state("t", {"foo", "bar", "test"});
   ASSERT_EQ(state.value_count(), 3);
   ASSERT_EQ(state.index_from_value("bar"), 1);
   ASSERT_EQ(state.value_from_index(2), "test");
}

TEST(State, stateValues) {
   std::vector<int> val{5, 3, 2};
   std::vector<int> result(3);

   for (int i = 0; i < 5*3*2; ++i) {
      minecpp::repository::parse_state(val.begin(), val.end(), result.begin(), i);
      std::cout << result[0] << " " << result[1] << "  " << result[2] << "\n";
   }
}

TEST(State, loadStates) {
   ASSERT_TRUE(minecpp::repository::load_blocks_from_file("repository.bin").ok());

   for (int i = 0; i < 100; ++i) {
      auto [block_id, state] = minecpp::repository::StateManager::the().parse_block_id(i);
      auto block = minecpp::repository::Block::the().get_by_id(block_id).unwrap();
      std::cout << block.tag() << "\n";
   }
}