#pragma once
#include <boost/uuid/uuid.hpp>
#include <cstring>
#include <mb/int.h>
#include <mb/result.h>
#include <string>

namespace minecpp::util {

using Uuid = boost::uuids::uuid;

inline Uuid read_uuid(mb::u64 lower, mb::u64 upper)
{
   Uuid id;
   *reinterpret_cast<mb::u64 *>(id.data)                   = lower;
   *reinterpret_cast<mb::u64 *>(id.data + sizeof(mb::u64)) = upper;
   return id;
}

inline Uuid read_uuid4(mb::i32 a, mb::i32 b, mb::i32 c, mb::i32 d)
{
   Uuid id;
   *reinterpret_cast<mb::i32 *>(id.data)                       = a;
   *reinterpret_cast<mb::i32 *>(id.data + sizeof(mb::i32))     = b;
   *reinterpret_cast<mb::i32 *>(id.data + 2 * sizeof(mb::i32)) = c;
   *reinterpret_cast<mb::i32 *>(id.data + 3 * sizeof(mb::i32)) = d;
   return id;
}

inline std::pair<mb::u64, mb::u64> write_uuid(Uuid id)
{
   mb::u64 lower, upper;
   lower = *reinterpret_cast<mb::u64 *>(id.data);
   upper = *reinterpret_cast<mb::u64 *>(id.data + sizeof(mb::u64));
   return std::make_pair(lower, upper);
}

inline std::tuple<mb::i32, mb::i32, mb::i32, mb::i32> write_uuid4(Uuid id)
{
   mb::i32 a, b, c, d;
   a = *reinterpret_cast<mb::i32 *>(id.data);
   b = *reinterpret_cast<mb::i32 *>(id.data + sizeof(mb::i32));
   c = *reinterpret_cast<mb::i32 *>(id.data + 2 * sizeof(mb::i32));
   d = *reinterpret_cast<mb::i32 *>(id.data + 3 * sizeof(mb::i32));
   return std::make_tuple(a, b, c, d);
}

void encode_uuid(char dst[], boost::uuids::uuid id);
void decode_uuid(boost::uuids::uuid &dst, const char *src);
mb::result<Uuid> make_uuid(const std::string &id);
std::string uuid_to_string(Uuid id);

}// namespace minecpp::util
