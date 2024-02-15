#pragma once
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::trace {

class ChunkDispatchRequested {
 public:
   static constexpr auto object_name = "ChunkDispatchRequested";
   std::int32_t chunk_x{};
   std::int32_t chunk_z{};
   ChunkDispatchRequested() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ChunkDispatchRequested deserialize_no_header(minecpp::nbt::Reader &r);
   static ChunkDispatchRequested deserialize(std::istream &in);
};

class ChunkSentToPlayer {
 public:
   static constexpr auto object_name = "ChunkSentToPlayer";
   std::int32_t chunk_x{};
   std::int32_t chunk_z{};
   std::string player_id{};
   ChunkSentToPlayer() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ChunkSentToPlayer deserialize_no_header(minecpp::nbt::Reader &r);
   static ChunkSentToPlayer deserialize(std::istream &in);
};

class GeneratingChunk {
 public:
   static constexpr auto object_name = "GeneratingChunk";
   std::int32_t chunk_x{};
   std::int32_t chunk_z{};
   GeneratingChunk() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static GeneratingChunk deserialize_no_header(minecpp::nbt::Reader &r);
   static GeneratingChunk deserialize(std::istream &in);
};

class HandlingChunkData {
 public:
   static constexpr auto object_name = "HandlingChunkData";
   std::int32_t chunk_x{};
   std::int32_t chunk_z{};
   HandlingChunkData() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static HandlingChunkData deserialize_no_header(minecpp::nbt::Reader &r);
   static HandlingChunkData deserialize(std::istream &in);
};

class PreHandlingChunkDataJob {
 public:
   static constexpr auto object_name = "PreHandlingChunkDataJob";
   std::int32_t chunk_x{};
   std::int32_t chunk_z{};
   PreHandlingChunkDataJob() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static PreHandlingChunkDataJob deserialize_no_header(minecpp::nbt::Reader &r);
   static PreHandlingChunkDataJob deserialize(std::istream &in);
};

class PostHandlingChunkDataJob {
 public:
   static constexpr auto object_name = "PostHandlingChunkDataJob";
   std::int32_t chunk_x{};
   std::int32_t chunk_z{};
   PostHandlingChunkDataJob() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static PostHandlingChunkDataJob deserialize_no_header(minecpp::nbt::Reader &r);
   static PostHandlingChunkDataJob deserialize(std::istream &in);
};

class HandlingEmptyChunk {
 public:
   static constexpr auto object_name = "HandlingEmptyChunk";
   std::int32_t chunk_x{};
   std::int32_t chunk_z{};
   HandlingEmptyChunk() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static HandlingEmptyChunk deserialize_no_header(minecpp::nbt::Reader &r);
   static HandlingEmptyChunk deserialize(std::istream &in);
};

}
