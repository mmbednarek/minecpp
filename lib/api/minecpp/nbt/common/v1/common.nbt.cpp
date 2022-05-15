#include <minecpp/nbt/common/v1/common.nbt.h>

namespace minecpp::nbt::common::v1 {

void ChunkPosition::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::Int, "x");
   w.write_int_content(x);
   w.write_header(minecpp::nbt::TagId::Int, "y");
   w.write_int_content(y);
   w.end_compound();
}

void ChunkPosition::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ChunkPosition ChunkPosition::deserialize_no_header(minecpp::nbt::Reader &r)
{
   ChunkPosition res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int: res.__xx_put(name, r.read_int()); return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

ChunkPosition ChunkPosition::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return ChunkPosition();
   }
   return ChunkPosition::deserialize_no_header(r);
}

void BlockPosition::serialize_no_header(minecpp::nbt::Writer &w) const
{
   w.write_header(minecpp::nbt::TagId::Int, "x");
   w.write_int_content(x);
   w.write_header(minecpp::nbt::TagId::Int, "y");
   w.write_int_content(y);
   w.write_header(minecpp::nbt::TagId::Int, "z");
   w.write_int_content(z);
   w.end_compound();
}

void BlockPosition::serialize(std::ostream &out, std::string_view name) const
{
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BlockPosition BlockPosition::deserialize_no_header(minecpp::nbt::Reader &r)
{
   BlockPosition res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int: res.__xx_put(name, r.read_int()); return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

BlockPosition BlockPosition::deserialize(std::istream &in)
{
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return BlockPosition();
   }
   return BlockPosition::deserialize_no_header(r);
}

}// namespace minecpp::nbt::common::v1