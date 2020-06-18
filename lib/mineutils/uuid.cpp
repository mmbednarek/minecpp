#include "uuid.h"
#include <cstring>

namespace Utils {

void encode_uuid(char dst[], boost::uuids::uuid id) {
   dst[16] = 0;
   std::memcpy(dst, id.data, sizeof(id.data));
}

void decode_uuid(boost::uuids::uuid &dst, const char *src) {
   std::memcpy(dst.data, src, 16);
}

}
