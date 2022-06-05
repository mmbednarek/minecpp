#include <cstring>
#include <mb/result.h>
#include <minecpp/util/uuid.h>

namespace minecpp::util {

void encode_uuid(char dst[], boost::uuids::uuid id)
{
   dst[16] = 0;
   std::memcpy(dst, id.data, sizeof(id.data));
}

void decode_uuid(boost::uuids::uuid &dst, const char *src) { std::memcpy(dst.data, src, 16); }

mb::result<uuid> make_uuid(const std::string &id)
{
   uuid result{};
   if (id.size() != 16)
      return result;

   decode_uuid(result, id.data());
   return result;
}

std::string uuid_to_string(uuid id)
{
   char data[17];
   encode_uuid(data, id);
   return {data};
}

}// namespace minecpp::util
