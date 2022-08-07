#pragma once
#include "EntityManager.hpp"
#include "Game.h"
#include "Notifier.h"
#include <mb/result.h>
#include <minecpp/game/player/Provider.hpp>

namespace minecpp::game {

class ISection
{
 public:
   virtual std::vector<game::LightSource> &light_sources() = 0;
   virtual void reset_light(LightType light_type)          = 0;
};

class ISectionSlice
{
 public:
   virtual mb::result<LightValue> get_light(LightType light_type, const BlockPosition &pos) = 0;
   virtual mb::emptyres set_light(game::LightType light_type, const game::BlockPosition &pos,
                                  game::LightValue value)                                   = 0;

   virtual ISection &operator[](game::ChunkSectionPosition position) = 0;
};

class ILightSystem
{
 public:
   virtual ~ILightSystem() noexcept                                                  = default;
   virtual mb::emptyres add_light_source(game::BlockPosition position, int strength) = 0;
};

class World
{
 public:
   virtual Notifier &notifier()                                                                       = 0;
   virtual EntityManager &entities()                                                                  = 0;
   virtual player::Provider &players()                                                                = 0;
   virtual mb::result<mb::empty> add_refs(PlayerId player, std::vector<game::ChunkPosition> refs)     = 0;
   virtual mb::result<mb::empty> free_refs(PlayerId player, std::vector<game::ChunkPosition> refs)    = 0;
   virtual mb::result<int> height_at(int x, int z)                                                    = 0;
   virtual mb::result<mb::empty> set_block(const game::BlockPosition &pos, game::BlockStateId state)  = 0;
   virtual mb::result<game::BlockStateId> get_block(const game::BlockPosition &pos)                   = 0;
   virtual mb::emptyres recalculate_light(game::LightType light_type, const game::BlockPosition &pos) = 0;
   virtual mb::result<game::LightValue> get_light(game::LightType light_type,
                                                  const game::BlockPosition &pos)                     = 0;
   virtual mb::emptyres set_light(LightType light_type, const BlockPosition &pos, LightValue level)   = 0;
   virtual mb::result<std::unique_ptr<ISectionSlice>> get_slice(game::SectionRange range)             = 0;
   virtual mb::emptyres apply_slice(ISectionSlice &slice)                                             = 0;
   virtual ILightSystem &light_system()                                                               = 0;
};

}// namespace minecpp::game
