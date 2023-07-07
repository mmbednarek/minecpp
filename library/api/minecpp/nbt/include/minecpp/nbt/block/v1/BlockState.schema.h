#pragma once
#include "minecpp/nbt/common/v1/Common.schema.h"
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::block::v1 {

class BlockState {
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
