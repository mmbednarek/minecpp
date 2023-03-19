#ifndef MINECPP_NBT_BLOCK_V1_BLOCKSTATE_H
#define MINECPP_NBT_BLOCK_V1_BLOCKSTATE_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <minecpp/nbt/common/v1/Common.nbt.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::block::v1 {

class BlockState {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, common::v1::FaceMask>) {
         if (in_field_name == "SolidFaces") {
            this->solid_faces = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "Luminance") {
            this->luminance = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Opacity") {
            this->opacity = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "BlocksMovement") {
            this->blocks_movement = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t blocks_movement{};
   std::int32_t luminance{};
   std::int32_t opacity{};
   common::v1::FaceMask solid_faces{};
   BlockState() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BlockState deserialize_no_header(minecpp::nbt::Reader &r);
   static BlockState deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_BLOCK_V1_BLOCKSTATE_H
