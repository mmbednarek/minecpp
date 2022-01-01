#ifndef MINECPP_STRUCTGEN_H
#define MINECPP_STRUCTGEN_H
#include <mb/codegen/component.h>
#include "generator.h"

namespace minecpp::tool::nbt_idl {

class Generator {
   std::string m_header_name;
   mb::codegen::component m_component;
 public:
   explicit Generator(Semantics::Structure &structure, const std::string &module_name, const std::string &header_path);

   void write_header(std::ostream &out);
   void write_source(std::ostream &out);
};

std::string make_header_constant(const std::string &package_name, const std::string &module_name);
void put_deserialize_logic(const Semantics::Message &msg, mb::codegen::statement::collector &col);
void put_deserialize_list_logic(const Semantics::ListDeserializer &deserializer, mb::codegen::statement::collector &col, mb::size depth = 0);
void put_deserialize_list_logic_static(const Semantics::StaticDeserializer &deserializer, mb::codegen::statement::collector &col, mb::size depth, mb::size target_depth);
void put_deserialize_list_logic_compound(const Semantics::CompoundDeserializer::Elem &elem, mb::codegen::statement::collector &col, mb::size depth, mb::size target_depth);
void put_serialize_logic(mb::codegen::statement::collector &col, Semantics::Type type, const mb::codegen::expression &value);

}


#endif//MINECPP_STRUCTGEN_H
