// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: chunk_storage.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_chunk_5fstorage_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_chunk_5fstorage_2eproto

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
#include "chunk.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_chunk_5fstorage_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_chunk_5fstorage_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_chunk_5fstorage_2eproto;
namespace minecpp {
namespace chunk_storage {
class EmptyResponse;
class EmptyResponseDefaultTypeInternal;
extern EmptyResponseDefaultTypeInternal _EmptyResponse_default_instance_;
class LoadChunkRequest;
class LoadChunkRequestDefaultTypeInternal;
extern LoadChunkRequestDefaultTypeInternal _LoadChunkRequest_default_instance_;
class SetBlockRequest;
class SetBlockRequestDefaultTypeInternal;
extern SetBlockRequestDefaultTypeInternal _SetBlockRequest_default_instance_;
}  // namespace chunk_storage
}  // namespace minecpp
PROTOBUF_NAMESPACE_OPEN
template<> ::minecpp::chunk_storage::EmptyResponse* Arena::CreateMaybeMessage<::minecpp::chunk_storage::EmptyResponse>(Arena*);
template<> ::minecpp::chunk_storage::LoadChunkRequest* Arena::CreateMaybeMessage<::minecpp::chunk_storage::LoadChunkRequest>(Arena*);
template<> ::minecpp::chunk_storage::SetBlockRequest* Arena::CreateMaybeMessage<::minecpp::chunk_storage::SetBlockRequest>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace minecpp {
namespace chunk_storage {

// ===================================================================

class LoadChunkRequest :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:minecpp.chunk_storage.LoadChunkRequest) */ {
 public:
  LoadChunkRequest();
  virtual ~LoadChunkRequest();

  LoadChunkRequest(const LoadChunkRequest& from);
  LoadChunkRequest(LoadChunkRequest&& from) noexcept
    : LoadChunkRequest() {
    *this = ::std::move(from);
  }

  inline LoadChunkRequest& operator=(const LoadChunkRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline LoadChunkRequest& operator=(LoadChunkRequest&& from) noexcept {
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
  static const LoadChunkRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const LoadChunkRequest* internal_default_instance() {
    return reinterpret_cast<const LoadChunkRequest*>(
               &_LoadChunkRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(LoadChunkRequest* other);
  friend void swap(LoadChunkRequest& a, LoadChunkRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline LoadChunkRequest* New() const final {
    return CreateMaybeMessage<LoadChunkRequest>(nullptr);
  }

  LoadChunkRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<LoadChunkRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const LoadChunkRequest& from);
  void MergeFrom(const LoadChunkRequest& from);
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
  void InternalSwap(LoadChunkRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "minecpp.chunk_storage.LoadChunkRequest";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_chunk_5fstorage_2eproto);
    return ::descriptor_table_chunk_5fstorage_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 x = 1;
  void clear_x();
  static const int kXFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int32 x() const;
  void set_x(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 z = 2;
  void clear_z();
  static const int kZFieldNumber = 2;
  ::PROTOBUF_NAMESPACE_ID::int32 z() const;
  void set_z(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:minecpp.chunk_storage.LoadChunkRequest)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::int32 x_;
  ::PROTOBUF_NAMESPACE_ID::int32 z_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_chunk_5fstorage_2eproto;
};
// -------------------------------------------------------------------

class SetBlockRequest :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:minecpp.chunk_storage.SetBlockRequest) */ {
 public:
  SetBlockRequest();
  virtual ~SetBlockRequest();

  SetBlockRequest(const SetBlockRequest& from);
  SetBlockRequest(SetBlockRequest&& from) noexcept
    : SetBlockRequest() {
    *this = ::std::move(from);
  }

  inline SetBlockRequest& operator=(const SetBlockRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline SetBlockRequest& operator=(SetBlockRequest&& from) noexcept {
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
  static const SetBlockRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SetBlockRequest* internal_default_instance() {
    return reinterpret_cast<const SetBlockRequest*>(
               &_SetBlockRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(SetBlockRequest* other);
  friend void swap(SetBlockRequest& a, SetBlockRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SetBlockRequest* New() const final {
    return CreateMaybeMessage<SetBlockRequest>(nullptr);
  }

  SetBlockRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SetBlockRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SetBlockRequest& from);
  void MergeFrom(const SetBlockRequest& from);
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
  void InternalSwap(SetBlockRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "minecpp.chunk_storage.SetBlockRequest";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_chunk_5fstorage_2eproto);
    return ::descriptor_table_chunk_5fstorage_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 x = 1;
  void clear_x();
  static const int kXFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int32 x() const;
  void set_x(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 y = 2;
  void clear_y();
  static const int kYFieldNumber = 2;
  ::PROTOBUF_NAMESPACE_ID::int32 y() const;
  void set_y(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 z = 3;
  void clear_z();
  static const int kZFieldNumber = 3;
  ::PROTOBUF_NAMESPACE_ID::int32 z() const;
  void set_z(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 state = 4;
  void clear_state();
  static const int kStateFieldNumber = 4;
  ::PROTOBUF_NAMESPACE_ID::int32 state() const;
  void set_state(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:minecpp.chunk_storage.SetBlockRequest)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::int32 x_;
  ::PROTOBUF_NAMESPACE_ID::int32 y_;
  ::PROTOBUF_NAMESPACE_ID::int32 z_;
  ::PROTOBUF_NAMESPACE_ID::int32 state_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_chunk_5fstorage_2eproto;
};
// -------------------------------------------------------------------

class EmptyResponse :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:minecpp.chunk_storage.EmptyResponse) */ {
 public:
  EmptyResponse();
  virtual ~EmptyResponse();

  EmptyResponse(const EmptyResponse& from);
  EmptyResponse(EmptyResponse&& from) noexcept
    : EmptyResponse() {
    *this = ::std::move(from);
  }

  inline EmptyResponse& operator=(const EmptyResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline EmptyResponse& operator=(EmptyResponse&& from) noexcept {
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
  static const EmptyResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const EmptyResponse* internal_default_instance() {
    return reinterpret_cast<const EmptyResponse*>(
               &_EmptyResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(EmptyResponse* other);
  friend void swap(EmptyResponse& a, EmptyResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline EmptyResponse* New() const final {
    return CreateMaybeMessage<EmptyResponse>(nullptr);
  }

  EmptyResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<EmptyResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const EmptyResponse& from);
  void MergeFrom(const EmptyResponse& from);
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
  void InternalSwap(EmptyResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "minecpp.chunk_storage.EmptyResponse";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_chunk_5fstorage_2eproto);
    return ::descriptor_table_chunk_5fstorage_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:minecpp.chunk_storage.EmptyResponse)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_chunk_5fstorage_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LoadChunkRequest

// int32 x = 1;
inline void LoadChunkRequest::clear_x() {
  x_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LoadChunkRequest::x() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk_storage.LoadChunkRequest.x)
  return x_;
}
inline void LoadChunkRequest::set_x(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  x_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk_storage.LoadChunkRequest.x)
}

// int32 z = 2;
inline void LoadChunkRequest::clear_z() {
  z_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 LoadChunkRequest::z() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk_storage.LoadChunkRequest.z)
  return z_;
}
inline void LoadChunkRequest::set_z(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  z_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk_storage.LoadChunkRequest.z)
}

// -------------------------------------------------------------------

// SetBlockRequest

// int32 x = 1;
inline void SetBlockRequest::clear_x() {
  x_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 SetBlockRequest::x() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk_storage.SetBlockRequest.x)
  return x_;
}
inline void SetBlockRequest::set_x(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  x_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk_storage.SetBlockRequest.x)
}

// int32 y = 2;
inline void SetBlockRequest::clear_y() {
  y_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 SetBlockRequest::y() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk_storage.SetBlockRequest.y)
  return y_;
}
inline void SetBlockRequest::set_y(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  y_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk_storage.SetBlockRequest.y)
}

// int32 z = 3;
inline void SetBlockRequest::clear_z() {
  z_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 SetBlockRequest::z() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk_storage.SetBlockRequest.z)
  return z_;
}
inline void SetBlockRequest::set_z(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  z_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk_storage.SetBlockRequest.z)
}

// int32 state = 4;
inline void SetBlockRequest::clear_state() {
  state_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 SetBlockRequest::state() const {
  // @@protoc_insertion_point(field_get:minecpp.chunk_storage.SetBlockRequest.state)
  return state_;
}
inline void SetBlockRequest::set_state(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  state_ = value;
  // @@protoc_insertion_point(field_set:minecpp.chunk_storage.SetBlockRequest.state)
}

// -------------------------------------------------------------------

// EmptyResponse

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace chunk_storage
}  // namespace minecpp

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_chunk_5fstorage_2eproto
