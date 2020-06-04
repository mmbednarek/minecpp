#include "block.h"

namespace Game::Block {

std::array<Block, 1> blocks{
    Block("stone", with_hardness(1.5F)),
};

} // namespace Game::Block
