#include <minecpp/command/Object.h>
#include <sstream>

namespace minecpp::command {

std::string ArrayObject::to_string()
{
   if (this->value.empty())
      return "[]";

   std::stringstream ss;
   ss << '[';

   auto it = this->value.begin();
   ss << (*it)->to_string();
   ++it;

   for (; it != this->value.end(); ++it) {
      ss << ", " << (*it)->to_string();
   }
   ss << ']';

   return ss.str();
}

}// namespace minecpp::command