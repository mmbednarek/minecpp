#pragma once
#include <minecpp/game/Game.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/State.h>
#include <optional>
#include <string_view>
#include <tuple>
#include <vector>

namespace minecpp::world {

class BlockState
{
 public:
   explicit BlockState(game::BlockStateId id);
   BlockState(game::BlockId block_id, game::StateOffset state_offset);

   template<typename TResult>
   [[nodiscard]] std::optional<TResult> get(std::string_view name) const
   {
      auto block = repository::Block::the().get_by_id(m_block_id);
      if (block.has_failed())
         return std::nullopt;

      return TResult::from_string(block->state_value(name, m_state_offset));
   };

   template<typename TValue>
   bool set(std::string_view name, TValue value)
   {
      auto block = repository::Block::the().get_by_id(m_block_id);
      if (block.has_failed())
         return false;

      std::vector<std::pair<int, int>> values;
      values.reserve(block->state_count());

      for (auto const &[state, state_index] : block->state_range(m_state_offset)) {
         if (state.name() != name) {
            values.emplace_back(static_cast<game::BlockStateId>(state.value_count()),
                                static_cast<game::BlockStateId>(state_index));
            continue;
         }

         values.emplace_back(static_cast<game::BlockStateId>(state.value_count()),
                             static_cast<game::BlockStateId>(state.index_from_value(value.to_string())));
      }

      m_state_offset = 0;
      std::for_each(values.crbegin(), values.crend(), [this](auto pair) {
         m_state_offset *= pair.first;
         m_state_offset += pair.second;
      });

      return true;
   };

   [[nodiscard]] constexpr game::BlockId block_id() const
   {
      return m_block_id;
   }

   [[nodiscard]] constexpr game::StateOffset state_offset() const
   {
      return m_state_offset;
   }

   [[nodiscard]] game::BlockStateId block_state_id() const;

 private:
   game::BlockId m_block_id{};
   game::StateOffset m_state_offset{};
};

template<>
[[nodiscard]] std::optional<bool> BlockState::get<bool>(std::string_view name) const;

template<>
bool BlockState::set<bool>(std::string_view name, bool value);

}// namespace minecpp::world