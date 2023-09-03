// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: minecpp/proto/player/Id.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_minecpp_2fproto_2fplayer_2fId_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_minecpp_2fproto_2fplayer_2fId_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4024000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4024002 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_minecpp_2fproto_2fplayer_2fId_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_minecpp_2fproto_2fplayer_2fId_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_minecpp_2fproto_2fplayer_2fId_2eproto;
namespace minecpp {
namespace proto {
namespace player {
class PlayerId;
struct PlayerIdDefaultTypeInternal;
extern PlayerIdDefaultTypeInternal _PlayerId_default_instance_;
}  // namespace player
}  // namespace proto
}  // namespace minecpp
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace minecpp {
namespace proto {
namespace player {

// ===================================================================


// -------------------------------------------------------------------

class PlayerId final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:minecpp.proto.player.PlayerId) */ {
 public:
  inline PlayerId() : PlayerId(nullptr) {}
  ~PlayerId() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR PlayerId(::google::protobuf::internal::ConstantInitialized);

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

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
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
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PlayerId* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PlayerId* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PlayerId>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const PlayerId& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const PlayerId& from) {
    PlayerId::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PlayerId* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "minecpp.proto.player.PlayerId";
  }
  protected:
  explicit PlayerId(::google::protobuf::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLowerFieldNumber = 1,
    kUpperFieldNumber = 2,
  };
  // uint64 lower = 1;
  void clear_lower() ;
  ::uint64_t lower() const;
  void set_lower(::uint64_t value);

  private:
  ::uint64_t _internal_lower() const;
  void _internal_set_lower(::uint64_t value);

  public:
  // uint64 upper = 2;
  void clear_upper() ;
  ::uint64_t upper() const;
  void set_upper(::uint64_t value);

  private:
  ::uint64_t _internal_upper() const;
  void _internal_set_upper(::uint64_t value);

  public:
  // @@protoc_insertion_point(class_scope:minecpp.proto.player.PlayerId)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<1, 2, 0, 0, 2> _table_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::uint64_t lower_;
    ::uint64_t upper_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_minecpp_2fproto_2fplayer_2fId_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// PlayerId

// uint64 lower = 1;
inline void PlayerId::clear_lower() {
  _impl_.lower_ = ::uint64_t{0u};
}
inline ::uint64_t PlayerId::lower() const {
  // @@protoc_insertion_point(field_get:minecpp.proto.player.PlayerId.lower)
  return _internal_lower();
}
inline void PlayerId::set_lower(::uint64_t value) {
  _internal_set_lower(value);
  // @@protoc_insertion_point(field_set:minecpp.proto.player.PlayerId.lower)
}
inline ::uint64_t PlayerId::_internal_lower() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.lower_;
}
inline void PlayerId::_internal_set_lower(::uint64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.lower_ = value;
}

// uint64 upper = 2;
inline void PlayerId::clear_upper() {
  _impl_.upper_ = ::uint64_t{0u};
}
inline ::uint64_t PlayerId::upper() const {
  // @@protoc_insertion_point(field_get:minecpp.proto.player.PlayerId.upper)
  return _internal_upper();
}
inline void PlayerId::set_upper(::uint64_t value) {
  _internal_set_upper(value);
  // @@protoc_insertion_point(field_set:minecpp.proto.player.PlayerId.upper)
}
inline ::uint64_t PlayerId::_internal_upper() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.upper_;
}
inline void PlayerId::_internal_set_upper(::uint64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.upper_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace player
}  // namespace proto
}  // namespace minecpp


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_minecpp_2fproto_2fplayer_2fId_2eproto_2epb_2eh
