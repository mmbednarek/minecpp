#include <minecpp/command/Object.h>
#include <minecpp/command/RuntimeContext.h>

namespace minecpp::command {

RuntimeContext::RuntimeContext(const CommandManager &manager, InputStream &input, OutputStream &output,
                               game::IWorld *world) :
    m_manager(manager),
    m_input(input),
    m_output(output),
    m_world(world)
{
}

Object::Ptr RuntimeContext::variable(const std::string &name)
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

}// namespace minecpp::command