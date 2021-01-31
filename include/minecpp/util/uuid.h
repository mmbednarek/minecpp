#pragma once
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <string>

namespace minecpp::util {

using uuid = boost::uuids::uuid;

void encode_uuid(char dst[], boost::uuids::uuid id);
void decode_uuid(boost::uuids::uuid &dst, const char *src);
mb::result<uuid> make_uuid(const std::string &id);
std::string uuid_to_string(uuid id);

}// namespace minecpp::util
