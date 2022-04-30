#ifndef MINECPP_REPOSITORY_BLOCK_H
#define MINECPP_REPOSITORY_BLOCK_H
#include "repository.h"
#include <minecpp/game/block/block.h>
#include <minecpp/game/state.h>

namespace minecpp::repository {

class Block : public Repository<game::block::Block> {
   static Block g_instance;
 public:
   constexpr static Block &the() {
      return g_instance;
   }
};

class BlockState : public Repository<game::State> {
   static BlockState g_instance;
 public:
   constexpr static BlockState &the() {
      return g_instance;
   }
};

mb::emptyres load_blocks_from_file(std::string_view filename);

}

#endif//MINECPP_REPOSITORY_BLOCK_H
