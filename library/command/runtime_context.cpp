#include <minecpp/command/object.h>
#include <minecpp/command/runtime_context.h>

namespace minecpp::command {

Object::Ptr RuntimeContext::variable(const std::string &name)
{
   if (!m_variables.contains(name)) {
      return {};
   }
   return m_variables.at(name);
}

RuntimeContext::RuntimeContext(const CommandManager &manager, InputStream &input, OutputStream &output) :
    m_manager(manager),
    m_input(input),
    m_output(output)
{
}

void RuntimeContext::set_variable(const std::string &name, std::shared_ptr<Object> value) {
   m_variables[name] = std::move(value);
}

}// namespace minecpp::command