#pragma once
#include <boost/uuid/uuid.hpp>
#include <cstring>
#include <mb/int.h>
#include <mb/result.h>
#include <string>

namespace minecpp::util {

using uuid = boost::uuids::uuid;

inline uuid read_uuid(mb::u64 lower, mb::u64 upper) {
   uuid id;
   *reinterpret_cast<mb::u64 *>(id.data) = lower;
   *reinterpret_cast<mb::u64 *>(id.data + sizeof(mb::u64)) = upper;
   return id;
}

inline std::pair<mb::u64, mb::u64> write_uuid(uuid id) {
   mb::u64 lower, upper;
   lower = *reinterpret_cast<mb::u64 *>(id.data);
   upper = *reinterpret_cast<mb::u64 *>(id.data + sizeof(mb::u64));
   return std::make_pair(lower, upper);
}

void encode_uuid(char dst[], boost::uuids::uuid id);
void decode_uuid(boost::uuids::uuid &dst, const char *src);
mb::result<uuid> make_uuid(const std::string &id);
std::string uuid_to_string(uuid id);

}// namespace minecpp::util
