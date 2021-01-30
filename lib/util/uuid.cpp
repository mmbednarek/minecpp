#include <minecpp/util/uuid.h>
#include <cstring>

namespace minecpp::util {

void encode_uuid(char dst[], boost::uuids::uuid id) {
   dst[16] = 0;
   std::memcpy(dst, id.data, sizeof(id.data));
}

void decode_uuid(boost::uuids::uuid &dst, const char *src) {
   std::memcpy(dst.data, src, 16);
}

boost::uuids::uuid make_uuid(const char *src) {
   boost::uuids::uuid result;
   decode_uuid(result, src);
   return result;
}

}
