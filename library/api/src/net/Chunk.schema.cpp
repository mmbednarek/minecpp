#include "minecpp/network/NetworkUtil.h"
#include "net/Chunk.schema.h"
#include <algorithm>

namespace minecpp::net {

void SingleValueData::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(this->value);
   writer.write_varint(this->length);
}

SingleValueData SingleValueData::deserialize(::minecpp::network::message::Reader &reader) {
   SingleValueData result;
   result.value = reader.read_varint();
   result.length = reader.read_varint();
   return result;
}

void PalettedData::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(static_cast<std::int32_t>(this->palette.size()));
   for (const auto &palette_value_0 : this->palette) {
      writer.write_varint(palette_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_big_endian(data_value_0);
   }
}

PalettedData PalettedData::deserialize(::minecpp::network::message::Reader &reader) {
   PalettedData result;
   auto palette_size_0 = reader.read_varint();
   result.palette.resize(static_cast<std::size_t>(palette_size_0));
   std::generate(result.palette.begin(), result.palette.end(), [&reader]() {
      return reader.read_varint();
   });
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   return result;
}

void DirectData::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_big_endian(data_value_0);
   }
}

DirectData DirectData::deserialize(::minecpp::network::message::Reader &reader) {
   DirectData result;
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   return result;
}

void PalettedContainer::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(this->bits_per_entry);
   if (this->single_value_data.has_value()) {
      this->single_value_data->serialize(writer);
   }
   if (this->indirect_data.has_value()) {
      this->indirect_data->serialize(writer);
   }
   if (this->direct_data.has_value()) {
      this->direct_data->serialize(writer);
   }
}

PalettedContainer PalettedContainer::deserialize(::minecpp::network::message::Reader &reader, std::uint8_t indirect_limit) {
   PalettedContainer result;
   result.bits_per_entry = reader.read_byte();
   const auto single_value_data_has_value_0 = result.bits_per_entry == 0u;
   if (single_value_data_has_value_0) {
      result.single_value_data = SingleValueData::deserialize(reader);
   }
   const auto indirect_data_has_value_0 = result.bits_per_entry > 0u && result.bits_per_entry <= indirect_limit;
   if (indirect_data_has_value_0) {
      result.indirect_data = PalettedData::deserialize(reader);
   }
   const auto direct_data_has_value_0 = result.bits_per_entry > indirect_limit;
   if (direct_data_has_value_0) {
      result.direct_data = DirectData::deserialize(reader);
   }
   return result;
}

void Section::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_big_endian(this->block_count);
   this->block_states.serialize(writer);
   this->biomes.serialize(writer);
}

Section Section::deserialize(::minecpp::network::message::Reader &reader) {
   Section result;
   result.block_count = reader.read_big_endian<std::uint16_t>();
   result.block_states = PalettedContainer::deserialize(reader, 8u);
   result.biomes = PalettedContainer::deserialize(reader, 3u);
   return result;
}

void ChunkData::serialize(::minecpp::network::message::Writer &writer) const {
   for (const auto &sections_value_0 : this->sections) {
      sections_value_0.serialize(writer);
   }
}

ChunkData ChunkData::deserialize(::minecpp::network::message::Reader &reader, std::int32_t section_count) {
   ChunkData result;
   result.sections.resize(static_cast<std::size_t>(section_count));
   std::generate(result.sections.begin(), result.sections.end(), [&reader]() {
      return Section::deserialize(reader);
   });
   return result;
}

void BlockEntity::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_byte(this->position_xz);
   writer.write_big_endian(this->y);
   writer.write_varint(this->type);
   this->data.serialize(writer.raw_stream(), "");
}

BlockEntity BlockEntity::deserialize(::minecpp::network::message::Reader &reader) {
   BlockEntity result;
   result.position_xz = reader.read_byte();
   result.y = reader.read_big_endian<std::int16_t>();
   result.type = reader.read_varint();
   result.data = nbt::block::BlockEntityData::deserialize(reader.raw_stream());
   return result;
}

void LightData::serialize(::minecpp::network::message::Writer &writer) const {
   writer.write_varint(static_cast<std::int32_t>(this->sky_light_mask.size()));
   for (const auto &sky_light_mask_value_0 : this->sky_light_mask) {
      writer.write_big_endian(sky_light_mask_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->block_light_mask.size()));
   for (const auto &block_light_mask_value_0 : this->block_light_mask) {
      writer.write_big_endian(block_light_mask_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->empty_sky_light_mask.size()));
   for (const auto &empty_sky_light_mask_value_0 : this->empty_sky_light_mask) {
      writer.write_big_endian(empty_sky_light_mask_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->empty_block_light_mask.size()));
   for (const auto &empty_block_light_mask_value_0 : this->empty_block_light_mask) {
      writer.write_big_endian(empty_block_light_mask_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->sky_light.size()));
   for (const auto &sky_light_value_0 : this->sky_light) {
      writer.write_varint(static_cast<std::int32_t>(sky_light_value_0.size()));
      for (const auto &sky_light_value_0_value_1 : sky_light_value_0) {
         writer.write_byte(sky_light_value_0_value_1);
      }
   }
   writer.write_varint(static_cast<std::int32_t>(this->block_light.size()));
   for (const auto &block_light_value_0 : this->block_light) {
      writer.write_varint(static_cast<std::int32_t>(block_light_value_0.size()));
      for (const auto &block_light_value_0_value_1 : block_light_value_0) {
         writer.write_byte(block_light_value_0_value_1);
      }
   }
}

LightData LightData::deserialize(::minecpp::network::message::Reader &reader) {
   LightData result;
   auto sky_light_mask_size_0 = reader.read_varint();
   result.sky_light_mask.resize(static_cast<std::size_t>(sky_light_mask_size_0));
   std::generate(result.sky_light_mask.begin(), result.sky_light_mask.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   auto block_light_mask_size_0 = reader.read_varint();
   result.block_light_mask.resize(static_cast<std::size_t>(block_light_mask_size_0));
   std::generate(result.block_light_mask.begin(), result.block_light_mask.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   auto empty_sky_light_mask_size_0 = reader.read_varint();
   result.empty_sky_light_mask.resize(static_cast<std::size_t>(empty_sky_light_mask_size_0));
   std::generate(result.empty_sky_light_mask.begin(), result.empty_sky_light_mask.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   auto empty_block_light_mask_size_0 = reader.read_varint();
   result.empty_block_light_mask.resize(static_cast<std::size_t>(empty_block_light_mask_size_0));
   std::generate(result.empty_block_light_mask.begin(), result.empty_block_light_mask.end(), [&reader]() {
      return reader.read_big_endian<std::uint64_t>();
   });
   auto sky_light_size_0 = reader.read_varint();
   result.sky_light.resize(static_cast<std::size_t>(sky_light_size_0));
   std::generate(result.sky_light.begin(), result.sky_light.end(), [&reader]() {
      std::vector<std::uint8_t> sky_light_result_0;
      auto sky_light_result_0_size_1 = reader.read_varint();
      sky_light_result_0.resize(static_cast<std::size_t>(sky_light_result_0_size_1));
      std::generate(sky_light_result_0.begin(), sky_light_result_0.end(), [&reader]() {
         return reader.read_byte();
      });
      return sky_light_result_0;
   });
   auto block_light_size_0 = reader.read_varint();
   result.block_light.resize(static_cast<std::size_t>(block_light_size_0));
   std::generate(result.block_light.begin(), result.block_light.end(), [&reader]() {
      std::vector<std::uint8_t> block_light_result_0;
      auto block_light_result_0_size_1 = reader.read_varint();
      block_light_result_0.resize(static_cast<std::size_t>(block_light_result_0_size_1));
      std::generate(block_light_result_0.begin(), block_light_result_0.end(), [&reader]() {
         return reader.read_byte();
      });
      return block_light_result_0;
   });
   return result;
}

void Chunk::serialize(::minecpp::network::message::Writer &writer) const {
   network::write_vector2i(writer, this->position);
   this->heightmaps.serialize(writer.raw_stream(), "");
   writer.write_varint(static_cast<std::int32_t>(this->data.size()));
   for (const auto &data_value_0 : this->data) {
      writer.write_byte(data_value_0);
   }
   writer.write_varint(static_cast<std::int32_t>(this->block_entities.size()));
   for (const auto &block_entities_value_0 : this->block_entities) {
      block_entities_value_0.serialize(writer);
   }
   this->light_data.serialize(writer);
}

Chunk Chunk::deserialize(::minecpp::network::message::Reader &reader) {
   Chunk result;
   result.position = network::read_vector2i(reader);
   result.heightmaps = nbt::chunk::HeightmapsNet::deserialize(reader.raw_stream());
   auto data_size_0 = reader.read_varint();
   result.data.resize(static_cast<std::size_t>(data_size_0));
   std::generate(result.data.begin(), result.data.end(), [&reader]() {
      return reader.read_byte();
   });
   auto block_entities_size_0 = reader.read_varint();
   result.block_entities.resize(static_cast<std::size_t>(block_entities_size_0));
   std::generate(result.block_entities.begin(), result.block_entities.end(), [&reader]() {
      return BlockEntity::deserialize(reader);
   });
   result.light_data = LightData::deserialize(reader);
   return result;
}

}