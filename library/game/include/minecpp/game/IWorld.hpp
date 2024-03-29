#pragma once
#include "Entity.h"
#include "Health.h"
#include "IDispatcher.hpp"
#include "Light.h"
#include <mb/result.h>
#include <minecpp/game/player/Provider.hpp>

namespace minecpp::game {

class IEntitySystem;

class IBlockContainer
{
 public:
   virtual ~IBlockContainer() = default;

   virtual mb::result<game::BlockStateId> block_at(const game::BlockPosition &pos)                      = 0;
   virtual mb::result<mb::empty> set_block_at(const game::BlockPosition &pos, game::BlockStateId state) = 0;
   virtual mb::result<LightValue> light_value_at(LightType light_type, const BlockPosition &pos)        = 0;
   virtual mb::emptyres set_light_value_at(game::LightType light_type, const game::BlockPosition &pos,
                                           game::LightValue value)                                      = 0;
};

class ISection
{
 public:
   virtual std::vector<game::LightSource> &light_sources() = 0;
   virtual void reset_light(LightType light_type)          = 0;
};

class ISectionSlice : public IBlockContainer
{
 public:
   virtual ISection &operator[](game::SectionPosition position) = 0;
};

class ILightSystem
{
 public:
   virtual ~ILightSystem() noexcept = default;

   virtual mb::emptyres add_light_source(game::BlockPosition position, game::LightValue value) = 0;
   virtual mb::emptyres recalculate_light(game::LightType light_type, game::BlockPosition position,
                                          game::FaceMask solid_faces)                          = 0;
   virtual mb::emptyres reset_light(game::LightType light_type, game::BlockPosition position)  = 0;
};

class IWorld : public IBlockContainer
{
 public:
   virtual IDispatcher &dispatcher()      = 0;
   virtual IEntitySystem &entity_system() = 0;
   virtual ILightSystem &light_system()   = 0;
   virtual player::Provider &players()    = 0;

   virtual mb::result<mb::empty> add_refs(PlayerId player, std::vector<game::ChunkPosition> refs)     = 0;
   virtual mb::result<mb::empty> free_refs(PlayerId player, std::vector<game::ChunkPosition> refs)    = 0;
   virtual mb::result<int> height_at(int x, int z)                                                    = 0;
   virtual mb::emptyres recalculate_light(game::LightType light_type, const game::BlockPosition &pos) = 0;
   virtual mb::result<std::unique_ptr<ISectionSlice>> get_slice(game::SectionRange range)             = 0;
   virtual mb::emptyres apply_slice(ISectionSlice &slice)                                             = 0;
   virtual mb::emptyres send_chunk_to_player(game::PlayerId player_id, const game::ChunkPosition &position,
                                             bool is_initial)                                         = 0;
   virtual bool is_movement_blocked_at(const math::Vector3 &position)                                 = 0;
   virtual void kill_entity(game::EntityId id)                                                        = 0;
   virtual void apply_damage_or_kill_entity(game::EntityId id, const game::Damage &damage)            = 0;
   virtual void destroy_block(const BlockPosition &position)                                          = 0;

   virtual mb::result<game::Entity> player_entity(PlayerId player_id) = 0;

   template<typename TEntityFactory, typename... TArgs>
   auto spawn(const math::Vector3 &position, TArgs &&...args)
   {
      TEntityFactory factory{std::forward<TArgs>(args)...};
      auto entity = factory.create_entity(position, this->entity_system());
      this->dispatcher().spawn_entity(entity.id());
      return entity;
   }
};

}// namespace minecpp::game
