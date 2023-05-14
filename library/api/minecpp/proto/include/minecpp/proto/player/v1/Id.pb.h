// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: minecpp/proto/player/v1/Id.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_minecpp_2fproto_2fplayer_2fv1_2fId_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_minecpp_2fproto_2fplayer_2fv1_2fId_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_minecpp_2fproto_2fplayer_2fv1_2fId_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_minecpp_2fproto_2fplayer_2fv1_2fId_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fId_2eproto;
namespace minecpp {
namespace proto {
namespace player {
namespace v1 {
class PlayerId;
struct PlayerIdDefaultTypeInternal;
extern PlayerIdDefaultTypeInternal _PlayerId_default_instance_;
}  // namespace v1
}  // namespace player
}  // namespace proto
}  // namespace minecpp
PROTOBUF_NAMESPACE_OPEN
template<> ::minecpp::proto::player::v1::PlayerId* Arena::CreateMaybeMessage<::minecpp::proto::player::v1::PlayerId>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace minecpp {
namespace proto {
namespace player {
namespace v1 {

// ===================================================================

class PlayerId final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:minecpp.proto.player.v1.PlayerId) */ {
 public:
  inline PlayerId() : PlayerId(nullptr) {}
  ~PlayerId() override;
  explicit PROTOBUF_CONSTEXPR PlayerId(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PlayerId(const PlayerId& from);
  PlayerId(PlayerId&& from) noexcept
    : PlayerId() {
    *this = ::std::move(from);
  }

  inline PlayerId& operator=(const PlayerId& from) {
    CopyFrom(from);
    return *this;
  }
  inline PlayerId& operator=(PlayerId&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PlayerId& default_instance() {
    return *internal_default_instance();
  }
  static inline const PlayerId* internal_default_instance() {
    return reinterpret_cast<const PlayerId*>(
               &_PlayerId_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PlayerId& a, PlayerId& b) {
    a.Swap(&b);
  }
  inline void Swap(PlayerId* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PlayerId* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PlayerId* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PlayerId>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PlayerId& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const PlayerId& from) {
    PlayerId::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PlayerId* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "minecpp.proto.player.v1.PlayerId";
  }
  protected:
  explicit PlayerId(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLowerFieldNumber = 1,
    kUpperFieldNumber = 2,
  };
  // uint64 lower = 1;
  void clear_lower();
  uint64_t lower() const;
  void set_lower(uint64_t value);
  private:
  uint64_t _internal_lower() const;
  void _internal_set_lower(uint64_t value);
  public:

  // uint64 upper = 2;
  void clear_upper();
  uint64_t upper() const;
  void set_upper(uint64_t value);
  private:
  uint64_t _internal_upper() const;
  void _internal_set_upper(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:minecpp.proto.player.v1.PlayerId)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    uint64_t lower_;
    uint64_t upper_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_minecpp_2fproto_2fplayer_2fv1_2fId_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PlayerId

// uint64 lower = 1;
inline void PlayerId::clear_lower() {
  _impl_.lower_ = uint64_t{0u};
}
inline uint64_t PlayerId::_internal_lower() const {
  return _impl_.lower_;
}
inline uint64_t PlayerId::lower() const {
  // @@protoc_insertion_point(field_get:minecpp.proto.player.v1.PlayerId.lower)
  return _internal_lower();
}
inline void PlayerId::_internal_set_lower(uint64_t value) {
  
  _impl_.lower_ = value;
}
inline void PlayerId::set_lower(uint64_t value) {
  _internal_set_lower(value);
  // @@protoc_insertion_point(field_set:minecpp.proto.player.v1.PlayerId.lower)
}

// uint64 upper = 2;
inline void PlayerId::clear_upper() {
  _impl_.upper_ = uint64_t{0u};
}
inline uint64_t PlayerId::_internal_upper() const {
  return _impl_.upper_;
}
inline uint64_t PlayerId::upper() const {
  // @@protoc_insertion_point(field_get:minecpp.proto.player.v1.PlayerId.upper)
  return _internal_upper();
}
inline void PlayerId::_internal_set_upper(uint64_t value) {
  
  _impl_.upper_ = value;
}
inline void PlayerId::set_upper(uint64_t value) {
  _internal_set_upper(value);
  // @@protoc_insertion_point(field_set:minecpp.proto.player.v1.PlayerId.upper)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace v1
}  // namespace player
}  // namespace proto
}  // namespace minecpp

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_minecpp_2fproto_2fplayer_2fv1_2fId_2eproto
