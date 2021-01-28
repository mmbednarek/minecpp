#pragma once
#include <boost/uuid/uuid.hpp>
#include <string>

namespace Utils {

void encode_uuid(char dst[], boost::uuids::uuid id);
void decode_uuid(boost::uuids::uuid &dst, const char *src);
boost::uuids::uuid make_uuid(const char *src);

}
