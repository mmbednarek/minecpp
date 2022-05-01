#include <minecpp/game/state.h>
#include <minecpp/repository/state.h>
#include <minecpp/repository/block.h>
#include <gtest/gtest.h>

TEST(State, intstate) {
   minecpp::game::State state("t", 5, 10);
   ASSERT_EQ(state.value_count(), 6);
   ASSERT_EQ(state.index_from_value("7"), 2);
   ASSERT_EQ(state.value_from_index(3), "8");
}

TEST(State, boolstate) {
   minecpp::game::State state("t");
   ASSERT_EQ(state.value_count(), 2);
   ASSERT_EQ(state.index_from_value("true"), 0);
   ASSERT_EQ(state.value_from_index(1), "false");
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
   ASSERT_TRUE(minecpp::repository::load_repository_from_file("repository.bin").ok());

   for (std::size_t i = 0; i < minecpp::repository::StateManager::the().state_count(); ++i) {
      auto [block_id, state] = minecpp::repository::StateManager::the().parse_block_id(static_cast<int>(i));
      auto block = minecpp::repository::Block::the().get_by_id(block_id).unwrap();

      if (state == 0)
         std::cout << block_id << ": " <<  block.tag() << "\n";
      if (!block.is_single_state())
         std::cout << "  state " << state << ":\n";

      minecpp::nbt::CompoundContent cont;

      auto range = block.state_range(state);
      std::for_each(range.begin(), range.end(), [&cont](const std::tuple<minecpp::game::State &, int> &pair) {
         auto [block_state, value_index] = pair;
        cont[std::string(block_state.name())] = minecpp::nbt::make_string(block_state.value_from_index(value_index));
        std::cout << "    " << block_state.name() <<  "="  << block_state.value_from_index(value_index) << '\n';
      });

      auto encoded = minecpp::repository::encode_state(block_id, minecpp::repository::make_compound_encoder(cont)).unwrap();
      ASSERT_EQ(i, encoded);
   }
}