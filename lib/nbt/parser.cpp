#include <stdexcept>
#include <signal.h>
#include "parser.h"
#include "exception.h"

namespace NBT {

Parser::Parser(std::istream& s) : Utils::Reader(s) {
}

Parser::~Parser() = default;

TagPtr Parser::read_tag() const {
    auto type = read_static<TagID>(TagID::End);
    if(type == TagID::End)
    	return std::unique_ptr<Tag>{};

    auto name = read_string();

    Tag *tag;
    switch(type) {
	case Byte:
		tag = make_tag<TagID::Byte>(name); break;
    case Short:
		tag = make_tag<TagID::Short>(name); break;
    case Int:
		tag = make_tag<TagID::Int>(name); break;
    case Long:
		tag = make_tag<TagID::Long>(name); break;
    case Float:
		tag = make_tag<TagID::Float>(name); break;
    case Double:
		tag = make_tag<TagID::Double>(name); break;
	case ByteArray:
		tag = make_tag<TagID::ByteArray>(name); break;
	case String:
		tag = make_tag<TagID::String>(name); break;
	case List:
		tag = make_tag<TagID::List>(name); break;
    case Compound:
		tag = make_tag<TagID::Compound>(name); break;
    case IntArray:
		tag = make_tag<TagID::IntArray>(name); break;
	case LongArray:
		tag = make_tag<TagID::LongArray>(name); break;
	default:
		throw Exception("invalid tag id");
	}

	return std::unique_ptr<Tag>(tag);
}

TagMap Parser::read_compound() const {
	TagMap result;
	for(auto tag = read_tag(); tag; tag = read_tag()) {
		result[tag->name()] = std::move(tag);
	}
	return result;
}

ListPayload Parser::read_list_payload() const {
	auto tagid = read_static(TagID::End);
	auto size = read_bswap<int>();

	switch(tagid) {
	case End:
		if(size > 0)
			throw Exception("list of type end with size > 0");
		return ListPayload(tagid, nullptr);
	case Byte:
		return ListPayload(tagid, new std::vector<uint8_t>(read_payload_array<Byte>(size)));
	case Short:
		return ListPayload(tagid, new std::vector<short>(read_payload_array<Short>(size)));
	case Int:
		return ListPayload(tagid, new std::vector<int>(read_payload_array<Int>(size)));
	case Long:
		return ListPayload(tagid, new std::vector<long long>(read_payload_array<Long>(size)));
	case Float:
		return ListPayload(tagid, new std::vector<float>(read_payload_array<Float>(size)));
	case Double:
		return ListPayload(tagid, new std::vector<double>(read_payload_array<Double>(size)));
	case ByteArray:
		return ListPayload(tagid, new std::vector<std::vector<uint8_t>>(read_payload_array<ByteArray>(size)));
	case String:
		return ListPayload(tagid, new std::vector<std::string>(read_payload_array<String>(size)));
	case Compound:
		return ListPayload(tagid, new std::vector<TagMap>(read_payload_array<Compound>(size)));
	case IntArray:
		return ListPayload(tagid, new std::vector<std::vector<int>>(read_payload_array<IntArray>(size)));
	case LongArray:
		return ListPayload(tagid, new std::vector<std::vector<long long>>(read_payload_array<LongArray>(size)));
	case List:
		return ListPayload(tagid, new std::vector<ListPayload>(read_payload_array<List>(size)));
	}

	throw Exception("invalid tag");
}

}
