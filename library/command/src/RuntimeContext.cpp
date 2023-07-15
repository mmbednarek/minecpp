#include <minecpp/command/Object.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/game/IEntitySystem.hpp>

namespace minecpp::command {

RuntimeContext::RuntimeContext(const CommandManager &manager, InputStream &input, OutputStream &output,
                               game::IWorld *world) :
    m_manager(manager),
    m_input(input),
    m_output(output),
    m_world(world)
{
}

Object::Ptr RuntimeContext::obj_variable(const std::string &name)
{
   if (!m_variables.contains(name)) {
      return {};
   }
   return m_variables.at(name);
}

void RuntimeContext::set_variable(const std::string &name, std::shared_ptr<Object> value)
{
   m_variables[name] = std::move(value);
}

std::optional<game::EntityId> RuntimeContext::entity_id()
{
   auto result = this->variable<int>("entity_id");
   if (not result.has_value())
      return std::nullopt;
   return static_cast<game::EntityId>(*result);
}

std::optional<game::Entity> RuntimeContext::entity()
{
   auto id = this->entity_id();
   if (not id.has_value())
      return std::nullopt;

   auto *world = this->world();
   if (world == nullptr)
      return std::nullopt;

   return world->entity_system().entity(*id);
}

std::optional<game::PlayerId> RuntimeContext::player_id()
{
   auto player_id = this->variable<util::Uuid>("player_id");
   if (not player_id.has_value())
      return std::nullopt;
   return static_cast<game::PlayerId>(*player_id);
}

std::optional<game::BlockPosition> RuntimeContext::current_position()
{
   return this->variable<game::BlockPosition>("here");
}

}// namespace minecpp::command