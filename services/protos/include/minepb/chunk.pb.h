// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: chunk.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_chunk_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_chunk_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3008000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3008000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_chunk_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_chunk_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_chunk_2eproto;
namespace minecpp {
namespace chunk {
class NetChunk;
class NetChunkDefaultTypeInternal;
extern NetChunkDefaultTypeInternal _NetChunk_default_instance_;
class NetChunk_Section;
class NetChunk_SectionDefaultTypeInternal;
extern NetChunk_SectionDefaultTypeInternal _NetChunk_Section_default_instance_;
}  // namespace chunk
}  // namespace minecpp
PROTOBUF_NAMESPACE_OPEN
template<> ::minecpp::chunk::NetChunk* Arena::CreateMaybeMessage<::minecpp::chunk::NetChunk>(Arena*);
template<> ::minecpp::chunk::NetChunk_Section* Arena::CreateMaybeMessage<::minecpp::chunk::NetChunk_Section>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace minecpp {
namespace chunk {

// ===================================================================

class NetChunk_Section :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:minecpp.chunk.NetChunk.Section) */ {
 public:
  NetChunk_Section();
  virtual ~NetChunk_Section();

  NetChunk_Section(const NetChunk_Section& from);
  NetChunk_Section(NetChunk_Section&& from) noexcept
    : NetChunk_Section() {
    *this = ::std::move(from);
  }

  inline NetChunk_Section& operator=(const NetChunk_Section& from) {
    CopyFrom(from);
    return *this;
  }
  inline NetChunk_Section& operator=(NetChunk_Section&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const NetChunk_Section& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NetChunk_Section* internal_default_instance() {
    return reinterpret_cast<const NetChunk_Section*>(
               &_NetChunk_Section_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(NetChunk_Section* other);
  friend void swap(NetChunk_Section& a, NetChunk_Section& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NetChunk_Section* New() const final {
    return CreateMaybeMessage<NetChunk_Section>(nullptr);
  }

  NetChunk_Section* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<NetChunk_Section>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const NetChunk_Section& from);
  void MergeFrom(const NetChunk_Section& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NetChunk_Section* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "minecpp.chunk.NetChunk.Section";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_chunk_2eproto);
    return ::descriptor_table_chunk_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated int32 palette = 4;
  int palette_size() const;
  void clear_palette();
  static const int kPaletteFieldNumber = 4;
  ::PROTOBUF_NAMESPACE_ID::int32 palette(int index) const;
  void set_palette(int index, ::PROTOBUF_NAMESPACE_ID::int32 value);
  void add_palette(::PROTOBUF_NAMESPACE_ID::int32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      palette() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      mutable_palette();

  // repeated int64 data = 5;
  int data_size() const;
  void clear_data();
  static const int kDataFieldNumber = 5;
  ::PROTOBUF_NAMESPACE_ID::int64 data(int index) const;
  void set_data(int index, ::PROTOBUF_NAMESPACE_ID::int64 value);
  void add_data(::PROTOBUF_NAMESPACE_ID::int64 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >&
      data() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >*
      mutable_data();

  // int32 y = 1;
  void clear_y();
  static const int kYFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int32 y() const;
  void set_y(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 bits = 2;
  void clear_bits();
  static const int kBitsFieldNumber = 2;
  ::PROTOBUF_NAMESPACE_ID::int32 bits() const;
  void set_bits(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 ref_count = 3;
  void clear_ref_count();
  static const int kRefCountFieldNumber = 3;
  ::PROTOBUF_NAMESPACE_ID::int32 ref_count() const;
  void set_ref_count(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:minecpp.chunk.NetChunk.Section)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 > palette_;
  mutable std::atomic<int> _palette_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 > data_;
  mutable std::atomic<int> _data_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 y_;
  ::PROTOBUF_NAMESPACE_ID::int32 bits_;
  ::PROTOBUF_NAMESPACE_ID::int32 ref_count_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_chunk_2eproto;
};
// -------------------------------------------------------------------

class NetChunk :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:minecpp.chunk.NetChunk) */ {
 public:
  NetChunk();
  virtual ~NetChunk();

  NetChunk(const NetChunk& from);
  NetChunk(NetChunk&& from) noexcept
    : NetChunk() {
    *this = ::std::move(from);
  }

  inline NetChunk& operator=(const NetChunk& from) {
    CopyFrom(from);
    return *this;
  }
  inline NetChunk& operator=(NetChunk&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const NetChunk& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const NetChunk* internal_default_instance() {
    return reinterpret_cast<const NetChunk*>(
               &_NetChunk_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(NetChunk* other);
  friend void swap(NetChunk& a, NetChunk& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline NetChunk* New() const final {
    return CreateMaybeMessage<NetChunk>(nullptr);
  }

  NetChunk* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<NetChunk>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const NetChunk& from);
  void MergeFrom(const NetChunk& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(NetChunk* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "minecpp.chunk.NetChunk";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_chunk_2eproto);
    return ::descriptor_table_chunk_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef NetChunk_Section Section;

  // accessors -------------------------------------------------------

  // repeated int32 biomes = 4 [packed = true];
  int biomes_size() const;
  void clear_biomes();
  static const int kBiomesFieldNumber = 4;
  ::PROTOBUF_NAMESPACE_ID::int32 biomes(int index) const;
  void set_biomes(int index, ::PROTOBUF_NAMESPACE_ID::int32 value);
  void add_biomes(::PROTOBUF_NAMESPACE_ID::int32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
      biomes() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
      mutable_biomes();

  // repeated int64 hm_world_surface = 5;
  int hm_world_surface_size() const;
  void clear_hm_world_surface();
  static const int kHmWorldSurfaceFieldNumber = 5;
  ::PROTOBUF_NAMESPACE_ID::int64 hm_world_surface(int index) const;
  void set_hm_world_surface(int index, ::PROTOBUF_NAMESPACE_ID::int64 value);
  void add_hm_world_surface(::PROTOBUF_NAMESPACE_ID::int64 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >&
      hm_world_surface() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >*
      mutable_hm_world_surface();

  // repeated int64 hm_motion_blocking = 6;
  int hm_motion_blocking_size() const;
  void clear_hm_motion_blocking();
  static const int kHmMotionBlockingFieldNumber = 6;
  ::PROTOBUF_NAMESPACE_ID::int64 hm_motion_blocking(int index) const;
  void set_hm_motion_blocking(int index, ::PROTOBUF_NAMESPACE_ID::int64 value);
  void add_hm_motion_blocking(::PROTOBUF_NAMESPACE_ID::int64 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >&
      hm_motion_blocking() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >*
      mutable_hm_motion_blocking();

  // repeated .minecpp.chunk.NetChunk.Section sections = 7;
  int sections_size() const;
  void clear_sections();
  static const int kSectionsFieldNumber = 7;
  ::minecpp::chunk::NetChunk_Section* mutable_sections(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::minecpp::chunk::NetChunk_Section >*
      mutable_sections();
  const ::minecpp::chunk::NetChunk_Section& sections(int index) const;
  ::minecpp::chunk::NetChunk_Section* add_sections();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::minecpp::chunk::NetChunk_Section >&
      sections() const;

  // int32 pos_x = 1;
  void clear_pos_x();
  static const int kPosXFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int32 pos_x() const;
  void set_pos_x(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 pos_z = 2;
  void clear_pos_z();
  static const int kPosZFieldNumber = 2;
  ::PROTOBUF_NAMESPACE_ID::int32 pos_z() const;
  void set_pos_z(::PROTOBUF_NAMESPACE_ID::int32 value);

  // bool full = 3;
  void clear_full();
  static const int kFullFieldNumber = 3;
  bool full() const;
  void set_full(bool value);

  // @@protoc_insertion_point(class_scope:minecpp.chunk.NetChunk)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 > biomes_;
  mutable std::atomic<int> _biomes_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 > hm_world_surface_;
  mutable std::atomic<int> _hm_world_surface_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 > hm_motion_blocking_;
  mutable std::atomic<int> _hm_motion_blocking_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::minecpp::chunk::NetChunk_Section > sections_;
  ::PROTOBUF_NAMESPACE_ID::int32 pos_x_;
  ::PROTOBUF_NAMESPACE_ID::int32 pos_z_;
  bool full_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_chunk_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// NetChunk_Section

// int32 y = 1;
inline void NetChunk_Section::clear_y() {
  y_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NetChunk_Section::y() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.Section.y)
  return y_;
}
inline void NetChunk_Section::set_y(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  y_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.Section.y)
}

// int32 bits = 2;
inline void NetChunk_Section::clear_bits() {
  bits_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NetChunk_Section::bits() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.Section.bits)
  return bits_;
}
inline void NetChunk_Section::set_bits(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  bits_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.Section.bits)
}

// int32 ref_count = 3;
inline void NetChunk_Section::clear_ref_count() {
  ref_count_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NetChunk_Section::ref_count() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.Section.ref_count)
  return ref_count_;
}
inline void NetChunk_Section::set_ref_count(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  ref_count_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.Section.ref_count)
}

// repeated int32 palette = 4;
inline int NetChunk_Section::palette_size() const {
  return palette_.size();
}
inline void NetChunk_Section::clear_palette() {
  palette_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NetChunk_Section::palette(int index) const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.Section.palette)
  return palette_.Get(index);
}
inline void NetChunk_Section::set_palette(int index, ::PROTOBUF_NAMESPACE_ID::int32 value) {
  palette_.Set(index, value);
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.Section.palette)
}
inline void NetChunk_Section::add_palette(::PROTOBUF_NAMESPACE_ID::int32 value) {
  palette_.Add(value);
  // @@protoc_insertion_point(field_add:minecpp.chunk.NetChunk.Section.palette)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
NetChunk_Section::palette() const {
  // @@protoc_insertion_point(field_list:minecpp.chunk.NetChunk.Section.palette)
  return palette_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
NetChunk_Section::mutable_palette() {
  // @@protoc_insertion_point(field_mutable_list:minecpp.chunk.NetChunk.Section.palette)
  return &palette_;
}

// repeated int64 data = 5;
inline int NetChunk_Section::data_size() const {
  return data_.size();
}
inline void NetChunk_Section::clear_data() {
  data_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int64 NetChunk_Section::data(int index) const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.Section.data)
  return data_.Get(index);
}
inline void NetChunk_Section::set_data(int index, ::PROTOBUF_NAMESPACE_ID::int64 value) {
  data_.Set(index, value);
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.Section.data)
}
inline void NetChunk_Section::add_data(::PROTOBUF_NAMESPACE_ID::int64 value) {
  data_.Add(value);
  // @@protoc_insertion_point(field_add:minecpp.chunk.NetChunk.Section.data)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >&
NetChunk_Section::data() const {
  // @@protoc_insertion_point(field_list:minecpp.chunk.NetChunk.Section.data)
  return data_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >*
NetChunk_Section::mutable_data() {
  // @@protoc_insertion_point(field_mutable_list:minecpp.chunk.NetChunk.Section.data)
  return &data_;
}

// -------------------------------------------------------------------

// NetChunk

// int32 pos_x = 1;
inline void NetChunk::clear_pos_x() {
  pos_x_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NetChunk::pos_x() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.pos_x)
  return pos_x_;
}
inline void NetChunk::set_pos_x(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  pos_x_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.pos_x)
}

// int32 pos_z = 2;
inline void NetChunk::clear_pos_z() {
  pos_z_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NetChunk::pos_z() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.pos_z)
  return pos_z_;
}
inline void NetChunk::set_pos_z(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  pos_z_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.pos_z)
}

// bool full = 3;
inline void NetChunk::clear_full() {
  full_ = false;
}
inline bool NetChunk::full() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.full)
  return full_;
}
inline void NetChunk::set_full(bool value) {
  
  full_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.full)
}

// repeated int32 biomes = 4 [packed = true];
inline int NetChunk::biomes_size() const {
  return biomes_.size();
}
inline void NetChunk::clear_biomes() {
  biomes_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int32 NetChunk::biomes(int index) const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.biomes)
  return biomes_.Get(index);
}
inline void NetChunk::set_biomes(int index, ::PROTOBUF_NAMESPACE_ID::int32 value) {
  biomes_.Set(index, value);
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.biomes)
}
inline void NetChunk::add_biomes(::PROTOBUF_NAMESPACE_ID::int32 value) {
  biomes_.Add(value);
  // @@protoc_insertion_point(field_add:minecpp.chunk.NetChunk.biomes)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >&
NetChunk::biomes() const {
  // @@protoc_insertion_point(field_list:minecpp.chunk.NetChunk.biomes)
  return biomes_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int32 >*
NetChunk::mutable_biomes() {
  // @@protoc_insertion_point(field_mutable_list:minecpp.chunk.NetChunk.biomes)
  return &biomes_;
}

// repeated int64 hm_world_surface = 5;
inline int NetChunk::hm_world_surface_size() const {
  return hm_world_surface_.size();
}
inline void NetChunk::clear_hm_world_surface() {
  hm_world_surface_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int64 NetChunk::hm_world_surface(int index) const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.hm_world_surface)
  return hm_world_surface_.Get(index);
}
inline void NetChunk::set_hm_world_surface(int index, ::PROTOBUF_NAMESPACE_ID::int64 value) {
  hm_world_surface_.Set(index, value);
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.hm_world_surface)
}
inline void NetChunk::add_hm_world_surface(::PROTOBUF_NAMESPACE_ID::int64 value) {
  hm_world_surface_.Add(value);
  // @@protoc_insertion_point(field_add:minecpp.chunk.NetChunk.hm_world_surface)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >&
NetChunk::hm_world_surface() const {
  // @@protoc_insertion_point(field_list:minecpp.chunk.NetChunk.hm_world_surface)
  return hm_world_surface_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >*
NetChunk::mutable_hm_world_surface() {
  // @@protoc_insertion_point(field_mutable_list:minecpp.chunk.NetChunk.hm_world_surface)
  return &hm_world_surface_;
}

// repeated int64 hm_motion_blocking = 6;
inline int NetChunk::hm_motion_blocking_size() const {
  return hm_motion_blocking_.size();
}
inline void NetChunk::clear_hm_motion_blocking() {
  hm_motion_blocking_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::int64 NetChunk::hm_motion_blocking(int index) const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.hm_motion_blocking)
  return hm_motion_blocking_.Get(index);
}
inline void NetChunk::set_hm_motion_blocking(int index, ::PROTOBUF_NAMESPACE_ID::int64 value) {
  hm_motion_blocking_.Set(index, value);
  // @@protoc_insertion_point(field_set:minecpp.chunk.NetChunk.hm_motion_blocking)
}
inline void NetChunk::add_hm_motion_blocking(::PROTOBUF_NAMESPACE_ID::int64 value) {
  hm_motion_blocking_.Add(value);
  // @@protoc_insertion_point(field_add:minecpp.chunk.NetChunk.hm_motion_blocking)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >&
NetChunk::hm_motion_blocking() const {
  // @@protoc_insertion_point(field_list:minecpp.chunk.NetChunk.hm_motion_blocking)
  return hm_motion_blocking_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::int64 >*
NetChunk::mutable_hm_motion_blocking() {
  // @@protoc_insertion_point(field_mutable_list:minecpp.chunk.NetChunk.hm_motion_blocking)
  return &hm_motion_blocking_;
}

// repeated .minecpp.chunk.NetChunk.Section sections = 7;
inline int NetChunk::sections_size() const {
  return sections_.size();
}
inline void NetChunk::clear_sections() {
  sections_.Clear();
}
inline ::minecpp::chunk::NetChunk_Section* NetChunk::mutable_sections(int index) {
  // @@protoc_insertion_point(field_mutable:minecpp.chunk.NetChunk.sections)
  return sections_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::minecpp::chunk::NetChunk_Section >*
NetChunk::mutable_sections() {
  // @@protoc_insertion_point(field_mutable_list:minecpp.chunk.NetChunk.sections)
  return &sections_;
}
inline const ::minecpp::chunk::NetChunk_Section& NetChunk::sections(int index) const {
  // @@protoc_insertion_point(field_get:minecpp.chunk.NetChunk.sections)
  return sections_.Get(index);
}
inline ::minecpp::chunk::NetChunk_Section* NetChunk::add_sections() {
  // @@protoc_insertion_point(field_add:minecpp.chunk.NetChunk.sections)
  return sections_.Add();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::minecpp::chunk::NetChunk_Section >&
NetChunk::sections() const {
  // @@protoc_insertion_point(field_list:minecpp.chunk.NetChunk.sections)
  return sections_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace chunk
}  // namespace minecpp

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_chunk_2eproto
