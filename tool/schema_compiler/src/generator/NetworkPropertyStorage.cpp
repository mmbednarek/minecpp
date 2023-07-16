#include "NetworkPropertyStorage.h"
#include "../IGenerator.h"

namespace minecpp::tool::schema_compiler::generator {

INetworkProperty &NetworkPropertyStorage::property_of(TypeClass type_class, int line, int col)
{
   generator_verify(m_properties.contains(type_class), line, col,
                    "no generator for type class: {}", static_cast<int>(type_class));
   return *m_properties[type_class];
}

}// namespace minecpp::tool::schema_compiler::generator