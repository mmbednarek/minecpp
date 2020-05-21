#pragma once
#include "reader.h"
#include "tag.h"
#include <map>
#include <string>

namespace NBT {

template <TagID t>
class CompoundMap : public std::map<std::string, tagid_type(t)> {
 public:
   explicit CompoundMap(Reader &r) {
      r.read_compound([this] (Reader &r, TagID type, std::string name) {
        assert(t == type);
        this->operator[](name) = r.read_payload<t>();
      });
   }
};

} // namespace NBT
