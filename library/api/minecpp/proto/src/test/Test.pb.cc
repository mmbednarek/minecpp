// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: minecpp/proto/test/Test.proto

#include <minecpp/proto/test/Test.pb.h>

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace minecpp {
namespace proto {
namespace test {
        template <typename>
PROTOBUF_CONSTEXPR TestMessage::TestMessage(::_pbi::ConstantInitialized)
    : _impl_{
      /*decltype(_impl_.value_)*/ {
          &::_pbi::fixed_address_empty_string,
          ::_pbi::ConstantInitialized{},
      },
      /*decltype(_impl_._cached_size_)*/ {},
    } {}
struct TestMessageDefaultTypeInternal {
  PROTOBUF_CONSTEXPR TestMessageDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~TestMessageDefaultTypeInternal() {}
  union {
    TestMessage _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 TestMessageDefaultTypeInternal _TestMessage_default_instance_;
}  // namespace test
}  // namespace proto
}  // namespace minecpp
static ::_pb::Metadata file_level_metadata_minecpp_2fproto_2ftest_2fTest_2eproto[1];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_minecpp_2fproto_2ftest_2fTest_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_minecpp_2fproto_2ftest_2fTest_2eproto = nullptr;
const ::uint32_t TableStruct_minecpp_2fproto_2ftest_2fTest_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::minecpp::proto::test::TestMessage, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::minecpp::proto::test::TestMessage, _impl_.value_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::minecpp::proto::test::TestMessage)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::minecpp::proto::test::_TestMessage_default_instance_._instance,
};
const char descriptor_table_protodef_minecpp_2fproto_2ftest_2fTest_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\035minecpp/proto/test/Test.proto\022\022minecpp"
    ".proto.test\"\034\n\013TestMessage\022\r\n\005value\030\001 \001("
    "\tb\006proto3"
};
static ::absl::once_flag descriptor_table_minecpp_2fproto_2ftest_2fTest_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_minecpp_2fproto_2ftest_2fTest_2eproto = {
    false,
    false,
    89,
    descriptor_table_protodef_minecpp_2fproto_2ftest_2fTest_2eproto,
    "minecpp/proto/test/Test.proto",
    &descriptor_table_minecpp_2fproto_2ftest_2fTest_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_minecpp_2fproto_2ftest_2fTest_2eproto::offsets,
    file_level_metadata_minecpp_2fproto_2ftest_2fTest_2eproto,
    file_level_enum_descriptors_minecpp_2fproto_2ftest_2fTest_2eproto,
    file_level_service_descriptors_minecpp_2fproto_2ftest_2fTest_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_minecpp_2fproto_2ftest_2fTest_2eproto_getter() {
  return &descriptor_table_minecpp_2fproto_2ftest_2fTest_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_minecpp_2fproto_2ftest_2fTest_2eproto(&descriptor_table_minecpp_2fproto_2ftest_2fTest_2eproto);
namespace minecpp {
namespace proto {
namespace test {
// ===================================================================

class TestMessage::_Internal {
 public:
};

TestMessage::TestMessage(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:minecpp.proto.test.TestMessage)
}
TestMessage::TestMessage(const TestMessage& from) : ::google::protobuf::Message() {
  TestMessage* const _this = this;
  (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.value_){},
      /*decltype(_impl_._cached_size_)*/ {},
  };
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  _impl_.value_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.value_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_value().empty()) {
    _this->_impl_.value_.Set(from._internal_value(), _this->GetArenaForAllocation());
  }

  // @@protoc_insertion_point(copy_constructor:minecpp.proto.test.TestMessage)
}
inline void TestMessage::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.value_){},
      /*decltype(_impl_._cached_size_)*/ {},
  };
  _impl_.value_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.value_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}
TestMessage::~TestMessage() {
  // @@protoc_insertion_point(destructor:minecpp.proto.test.TestMessage)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void TestMessage::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.value_.Destroy();
}
void TestMessage::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

PROTOBUF_NOINLINE void TestMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:minecpp.proto.test.TestMessage)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.value_.ClearToEmpty();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* TestMessage::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 44, 2> TestMessage::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_TestMessage_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    // string value = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(TestMessage, _impl_.value_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string value = 1;
    {PROTOBUF_FIELD_OFFSET(TestMessage, _impl_.value_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\36\5\0\0\0\0\0\0"
    "minecpp.proto.test.TestMessage"
    "value"
  }},
};

::uint8_t* TestMessage::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:minecpp.proto.test.TestMessage)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // string value = 1;
  if (!this->_internal_value().empty()) {
    const std::string& _s = this->_internal_value();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "minecpp.proto.test.TestMessage.value");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:minecpp.proto.test.TestMessage)
  return target;
}

::size_t TestMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:minecpp.proto.test.TestMessage)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string value = 1;
  if (!this->_internal_value().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_value());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData TestMessage::_class_data_ = {
    ::google::protobuf::Message::CopyWithSourceCheck,
    TestMessage::MergeImpl
};
const ::google::protobuf::Message::ClassData*TestMessage::GetClassData() const { return &_class_data_; }


void TestMessage::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<TestMessage*>(&to_msg);
  auto& from = static_cast<const TestMessage&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:minecpp.proto.test.TestMessage)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_value().empty()) {
    _this->_internal_set_value(from._internal_value());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void TestMessage::CopyFrom(const TestMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:minecpp.proto.test.TestMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool TestMessage::IsInitialized() const {
  return true;
}

void TestMessage::InternalSwap(TestMessage* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.value_, lhs_arena,
                                       &other->_impl_.value_, rhs_arena);
}

::google::protobuf::Metadata TestMessage::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_minecpp_2fproto_2ftest_2fTest_2eproto_getter, &descriptor_table_minecpp_2fproto_2ftest_2fTest_2eproto_once,
      file_level_metadata_minecpp_2fproto_2ftest_2fTest_2eproto[0]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace test
}  // namespace proto
}  // namespace minecpp
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
