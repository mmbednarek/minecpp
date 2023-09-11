#pragma once
#include "minecpp/nbt/block/Block.schema.h"
#include "minecpp/nbt/chunk/Chunk.schema.h"
#include "minecpp/net/Common.schema.h"
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::net {

class SingleValueData {
 public:
   std::int32_t value{};
   std::int32_t length{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static SingleValueData deserialize(::minecpp::network::message::Reader &reader);
};

class PalettedData {
 public:
   std::vector<std::int32_t> palette{};
   std::vector<std::uint64_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PalettedData deserialize(::minecpp::network::message::Reader &reader);
};

class DirectData {
 public:
   std::vector<std::uint64_t> data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static DirectData deserialize(::minecpp::network::message::Reader &reader);
};

class PalettedContainer {
 public:
   std::uint8_t bits_per_entry{};
   std::optional<SingleValueData> single_value_data{};
   std::optional<PalettedData> indirect_data{};
   std::optional<DirectData> direct_data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static PalettedContainer deserialize(::minecpp::network::message::Reader &reader, std::uint8_t indirect_limit);
};

class Section {
 public:
   std::uint16_t block_count{};
   PalettedContainer block_states{};
   PalettedContainer biomes{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Section deserialize(::minecpp::network::message::Reader &reader);
};

class ChunkData {
 public:
   std::vector<Section> sections{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static ChunkData deserialize(::minecpp::network::message::Reader &reader, std::int32_t section_count);
};

class BlockEntity {
 public:
   std::uint8_t position_xz{};
   std::int16_t y{};
   std::int32_t type{};
   nbt::block::BlockEntityData data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static BlockEntity deserialize(::minecpp::network::message::Reader &reader);
};

class LightData {
 public:
   std::vector<std::uint64_t> sky_light_mask{};
   std::vector<std::uint64_t> block_light_mask{};
   std::vector<std::uint64_t> empty_sky_light_mask{};
   std::vector<std::uint64_t> empty_block_light_mask{};
   std::vector<std::vector<std::uint8_t>> sky_light{};
   std::vector<std::vector<std::uint8_t>> block_light{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static LightData deserialize(::minecpp::network::message::Reader &reader);
};

class Chunk {
 public:
   ::minecpp::math::Vector2i position{};
   nbt::chunk::HeightmapsNet heightmaps{};
   std::vector<std::uint8_t> data{};
   std::vector<BlockEntity> block_entities{};
   LightData light_data{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Chunk deserialize(::minecpp::network::message::Reader &reader);
};

}
