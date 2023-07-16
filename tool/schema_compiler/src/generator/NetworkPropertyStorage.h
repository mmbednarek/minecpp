#pragma once

#include "../SymbolTable.h"
#include "INetworkProperty.hpp"

#include <map>
#include <memory>

namespace minecpp::tool::schema_compiler::generator {

class NetworkPropertyStorage
{
 public:
   INetworkProperty &property_of(TypeClass type_class, int line = 0, int col = 0);

   template<typename TProp, typename... TArgs>
   void register_property(TypeClass tc, TArgs &&...args)
   {
      m_properties.emplace(tc, std::make_unique<TProp>(std::forward<TArgs>(args)...));
   }

 private:
   std::map<TypeClass, std::unique_ptr<INetworkProperty>> m_properties;
};

}// namespace minecpp::tool::schema_compiler::generator
