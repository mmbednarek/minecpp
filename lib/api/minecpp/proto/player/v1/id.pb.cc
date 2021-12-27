// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: minecpp/proto/player/v1/id.proto

#include <minecpp/proto/player/v1/id.pb.h>

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace minecpp {
namespace proto {
namespace player {
namespace v1 {
constexpr PlayerId::PlayerId(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : lower_(uint64_t{0u})
  , upper_(uint64_t{0u}){}
struct PlayerIdDefaultTypeInternal {
  constexpr PlayerIdDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PlayerIdDefaultTypeInternal() {}
  union {
    PlayerId _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PlayerIdDefaultTypeInternal _PlayerId_default_instance_;
}  // namespace v1
}  // namespace player
}  // namespace proto
}  // namespace minecpp
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::minecpp::proto::player::v1::PlayerId, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::minecpp::proto::player::v1::PlayerId, lower_),
  PROTOBUF_FIELD_OFFSET(::minecpp::proto::player::v1::PlayerId, upper_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::minecpp::proto::player::v1::PlayerId)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::minecpp::proto::player::v1::_PlayerId_default_instance_),
};

const char descriptor_table_protodef_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n minecpp/proto/player/v1/id.proto\022\027mine"
  "cpp.proto.player.v1\"(\n\010PlayerId\022\r\n\005lower"
  "\030\001 \001(\004\022\r\n\005upper\030\002 \001(\004b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto = {
  false, false, 109, descriptor_table_protodef_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto, "minecpp/proto/player/v1/id.proto", 
  &descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto::offsets,
  file_level_metadata_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto, file_level_enum_descriptors_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto, file_level_service_descriptors_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto_getter() {
  return &descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto(&descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto);
namespace minecpp {
namespace proto {
namespace player {
namespace v1 {

// ===================================================================

class PlayerId::_Internal {
 public:
};

PlayerId::PlayerId(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:minecpp.proto.player.v1.PlayerId)
}
PlayerId::PlayerId(const PlayerId& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&lower_, &from.lower_,
    static_cast<size_t>(reinterpret_cast<char*>(&upper_) -
    reinterpret_cast<char*>(&lower_)) + sizeof(upper_));
  // @@protoc_insertion_point(copy_constructor:minecpp.proto.player.v1.PlayerId)
}

inline void PlayerId::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&lower_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&upper_) -
    reinterpret_cast<char*>(&lower_)) + sizeof(upper_));
}

PlayerId::~PlayerId() {
  // @@protoc_insertion_point(destructor:minecpp.proto.player.v1.PlayerId)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void PlayerId::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void PlayerId::ArenaDtor(void* object) {
  PlayerId* _this = reinterpret_cast< PlayerId* >(object);
  (void)_this;
}
void PlayerId::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void PlayerId::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void PlayerId::Clear() {
// @@protoc_insertion_point(message_clear_start:minecpp.proto.player.v1.PlayerId)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&lower_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&upper_) -
      reinterpret_cast<char*>(&lower_)) + sizeof(upper_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PlayerId::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 lower = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          lower_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint64 upper = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          upper_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* PlayerId::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:minecpp.proto.player.v1.PlayerId)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 lower = 1;
  if (this->_internal_lower() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_lower(), target);
  }

  // uint64 upper = 2;
  if (this->_internal_upper() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_upper(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:minecpp.proto.player.v1.PlayerId)
  return target;
}

size_t PlayerId::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:minecpp.proto.player.v1.PlayerId)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint64 lower = 1;
  if (this->_internal_lower() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_lower());
  }

  // uint64 upper = 2;
  if (this->_internal_upper() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_upper());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PlayerId::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    PlayerId::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PlayerId::GetClassData() const { return &_class_data_; }

void PlayerId::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<PlayerId *>(to)->MergeFrom(
      static_cast<const PlayerId &>(from));
}


void PlayerId::MergeFrom(const PlayerId& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:minecpp.proto.player.v1.PlayerId)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_lower() != 0) {
    _internal_set_lower(from._internal_lower());
  }
  if (from._internal_upper() != 0) {
    _internal_set_upper(from._internal_upper());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PlayerId::CopyFrom(const PlayerId& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:minecpp.proto.player.v1.PlayerId)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PlayerId::IsInitialized() const {
  return true;
}

void PlayerId::InternalSwap(PlayerId* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(PlayerId, upper_)
      + sizeof(PlayerId::upper_)
      - PROTOBUF_FIELD_OFFSET(PlayerId, lower_)>(
          reinterpret_cast<char*>(&lower_),
          reinterpret_cast<char*>(&other->lower_));
}

::PROTOBUF_NAMESPACE_ID::Metadata PlayerId::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto_getter, &descriptor_table_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto_once,
      file_level_metadata_minecpp_2fproto_2fplayer_2fv1_2fid_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace v1
}  // namespace player
}  // namespace proto
}  // namespace minecpp
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::minecpp::proto::player::v1::PlayerId* Arena::CreateMaybeMessage< ::minecpp::proto::player::v1::PlayerId >(Arena* arena) {
  return Arena::CreateMessageInternal< ::minecpp::proto::player::v1::PlayerId >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
