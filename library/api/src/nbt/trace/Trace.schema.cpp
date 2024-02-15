#include "nbt/trace/Trace.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::trace {

void ChunkDispatchRequested::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "chunk_x");
   w.write_int_content(chunk_x);
   w.write_header(minecpp::nbt::TagId::Int, "chunk_z");
   w.write_int_content(chunk_z);
   w.end_compound();
}

void ChunkDispatchRequested::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChunkDispatchRequested ChunkDispatchRequested::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChunkDispatchRequested result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chunk_x") {
         ::minecpp::nbt::verify_tag("ChunkDispatchRequested", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_x = r.read_int();
         continue;
      }
      if (in_field_name == "chunk_z") {
         ::minecpp::nbt::verify_tag("ChunkDispatchRequested", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_z = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChunkDispatchRequested ChunkDispatchRequested::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChunkDispatchRequested::deserialize_no_header(r);
}

void ChunkSentToPlayer::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "chunk_x");
   w.write_int_content(chunk_x);
   w.write_header(minecpp::nbt::TagId::Int, "chunk_z");
   w.write_int_content(chunk_z);
   w.write_header(minecpp::nbt::TagId::String, "player_id");
   w.write_string_content(player_id);
   w.end_compound();
}

void ChunkSentToPlayer::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChunkSentToPlayer ChunkSentToPlayer::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChunkSentToPlayer result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chunk_x") {
         ::minecpp::nbt::verify_tag("ChunkSentToPlayer", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_x = r.read_int();
         continue;
      }
      if (in_field_name == "chunk_z") {
         ::minecpp::nbt::verify_tag("ChunkSentToPlayer", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_z = r.read_int();
         continue;
      }
      if (in_field_name == "player_id") {
         ::minecpp::nbt::verify_tag("ChunkSentToPlayer", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.player_id = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChunkSentToPlayer ChunkSentToPlayer::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChunkSentToPlayer::deserialize_no_header(r);
}

void GeneratingChunk::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "chunk_x");
   w.write_int_content(chunk_x);
   w.write_header(minecpp::nbt::TagId::Int, "chunk_z");
   w.write_int_content(chunk_z);
   w.end_compound();
}

void GeneratingChunk::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

GeneratingChunk GeneratingChunk::deserialize_no_header(minecpp::nbt::Reader &r) {
   GeneratingChunk result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chunk_x") {
         ::minecpp::nbt::verify_tag("GeneratingChunk", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_x = r.read_int();
         continue;
      }
      if (in_field_name == "chunk_z") {
         ::minecpp::nbt::verify_tag("GeneratingChunk", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_z = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

GeneratingChunk GeneratingChunk::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return GeneratingChunk::deserialize_no_header(r);
}

void HandlingChunkData::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "chunk_x");
   w.write_int_content(chunk_x);
   w.write_header(minecpp::nbt::TagId::Int, "chunk_z");
   w.write_int_content(chunk_z);
   w.end_compound();
}

void HandlingChunkData::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

HandlingChunkData HandlingChunkData::deserialize_no_header(minecpp::nbt::Reader &r) {
   HandlingChunkData result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chunk_x") {
         ::minecpp::nbt::verify_tag("HandlingChunkData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_x = r.read_int();
         continue;
      }
      if (in_field_name == "chunk_z") {
         ::minecpp::nbt::verify_tag("HandlingChunkData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_z = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

HandlingChunkData HandlingChunkData::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return HandlingChunkData::deserialize_no_header(r);
}

void PreHandlingChunkDataJob::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "chunk_x");
   w.write_int_content(chunk_x);
   w.write_header(minecpp::nbt::TagId::Int, "chunk_z");
   w.write_int_content(chunk_z);
   w.end_compound();
}

void PreHandlingChunkDataJob::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

PreHandlingChunkDataJob PreHandlingChunkDataJob::deserialize_no_header(minecpp::nbt::Reader &r) {
   PreHandlingChunkDataJob result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chunk_x") {
         ::minecpp::nbt::verify_tag("PreHandlingChunkDataJob", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_x = r.read_int();
         continue;
      }
      if (in_field_name == "chunk_z") {
         ::minecpp::nbt::verify_tag("PreHandlingChunkDataJob", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_z = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

PreHandlingChunkDataJob PreHandlingChunkDataJob::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return PreHandlingChunkDataJob::deserialize_no_header(r);
}

void PostHandlingChunkDataJob::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "chunk_x");
   w.write_int_content(chunk_x);
   w.write_header(minecpp::nbt::TagId::Int, "chunk_z");
   w.write_int_content(chunk_z);
   w.end_compound();
}

void PostHandlingChunkDataJob::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

PostHandlingChunkDataJob PostHandlingChunkDataJob::deserialize_no_header(minecpp::nbt::Reader &r) {
   PostHandlingChunkDataJob result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chunk_x") {
         ::minecpp::nbt::verify_tag("PostHandlingChunkDataJob", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_x = r.read_int();
         continue;
      }
      if (in_field_name == "chunk_z") {
         ::minecpp::nbt::verify_tag("PostHandlingChunkDataJob", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_z = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

PostHandlingChunkDataJob PostHandlingChunkDataJob::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return PostHandlingChunkDataJob::deserialize_no_header(r);
}

void HandlingEmptyChunk::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "chunk_x");
   w.write_int_content(chunk_x);
   w.write_header(minecpp::nbt::TagId::Int, "chunk_z");
   w.write_int_content(chunk_z);
   w.end_compound();
}

void HandlingEmptyChunk::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

HandlingEmptyChunk HandlingEmptyChunk::deserialize_no_header(minecpp::nbt::Reader &r) {
   HandlingEmptyChunk result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chunk_x") {
         ::minecpp::nbt::verify_tag("HandlingEmptyChunk", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_x = r.read_int();
         continue;
      }
      if (in_field_name == "chunk_z") {
         ::minecpp::nbt::verify_tag("HandlingEmptyChunk", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.chunk_z = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

HandlingEmptyChunk HandlingEmptyChunk::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return HandlingEmptyChunk::deserialize_no_header(r);
}

}