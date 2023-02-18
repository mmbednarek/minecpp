#pragma once

namespace minecpp::entity::component {

struct Health {
   float health{};
};

struct Food {
   int food{};
   float saturation{};
};

}
