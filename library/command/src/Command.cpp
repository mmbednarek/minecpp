#include <minecpp/command/Command.h>

namespace minecpp::command {

NullStream g_null_stream;

std::size_t CommandInput::arg_count() const
{
   return m_arguments.size();
}

std::string CommandInput::string_arg(std::size_t index) const
{
   if (index >= m_arguments.size())
      return {};

   return m_arguments[index]->to_string();
}

Object::Ptr CommandInput::obj_org(std::size_t index) const
{
   if (m_arguments.size() >= index)
      return nullptr;
   return m_arguments[index];
}

CommandInput::iterator CommandInput::begin()
{
   return m_arguments.begin();
}

CommandInput::iterator CommandInput::end()
{
   return m_arguments.end();
}

CommandInput::CommandInput(RuntimeContext &ctx, const std::vector<ast::Expression::Ptr> &arguments,
                           const std::unordered_set<std::string> &flags,
                           const std::unordered_map<std::string, ast::Expression::Ptr> &params) :
    m_flags(flags)
{
   m_arguments.resize(arguments.size());
   std::transform(arguments.begin(), arguments.end(), m_arguments.begin(),
                  [&ctx](const ast::Expression::Ptr &expr) { return expr->execute(ctx); });

   for (const auto &[param, expr] : params) {
      m_params[param] = expr->execute(ctx);
   }
}

bool CommandInput::has_flag(const std::string &flag) const
{
   return m_flags.contains(flag);
}

}// namespace minecpp::command
