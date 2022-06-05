#ifndef MINECPP_RUNTIME_CONTEXT_H
#define MINECPP_RUNTIME_CONTEXT_H
#include <memory>
#include <string>
#include <unordered_map>

namespace minecpp::command {

class CommandManager;
class Object;
class InputStream;
class OutputStream;

class RuntimeContext
{
   std::unordered_map<std::string, std::shared_ptr<Object>> m_variables;
   const CommandManager &m_manager;
   InputStream &m_input;
   OutputStream &m_output;

 public:
   explicit RuntimeContext(const CommandManager &manager, InputStream &input, OutputStream &output);

   std::shared_ptr<Object> variable(const std::string &name);
   void set_variable(const std::string &name, std::shared_ptr<Object> object);

   [[nodiscard]] constexpr const CommandManager &commands() const
   {
      return m_manager;
   }

   [[nodiscard]] constexpr InputStream &in()
   {
      return m_input;
   }

   [[nodiscard]] constexpr OutputStream &out()
   {
      return m_output;
   }
};

}// namespace minecpp::command

#endif//MINECPP_RUNTIME_CONTEXT_H
