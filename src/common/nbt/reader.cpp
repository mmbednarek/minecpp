#include "reader.h"
#include <cassert>

namespace NBT {

Reader::Reader(std::istream &s) : Utils::Reader(s) {
}

void Reader::find_compound(std::string name) {
	if(!seek_tag<TagID::Compound>(name)) {
		throw Exception("could not find tag");
	}
}


void Reader::leave_compound() {
	for(;;) {
		auto type = read_static(TagID::End);
		if(type == TagID::End)
			return;
		auto name_size = read_bswap<short>();
		get_stream().ignore(name_size);
		skip_payload(type);
	}
}

void Reader::skip_payload(TagID tagid) {
	int size;
	TagID elm_tagid;

	switch(tagid) {
	case Byte:
		get_stream().ignore(sizeof(uint8_t));
		return;
	case Short:
		get_stream().ignore(sizeof(short));
		return;
	case Int:
		get_stream().ignore(sizeof(int));
		return;
	case Long:
		get_stream().ignore(sizeof(long long));
		return;
	case Float:
		get_stream().ignore(sizeof(float));
		return;
	case Double:
		get_stream().ignore(sizeof(double));
		return;
	case List:
		elm_tagid = read_static(TagID::End);
		size = read_bswap<int>();
		for(int i = 0; i < size; i++) {
			skip_payload(elm_tagid);
		}
		return;
	case Compound:
		for(;;) {
			elm_tagid = read_static(TagID::End);
			if(elm_tagid == TagID::End) {
				return;
			}
			size = read_bswap<short>();
			get_stream().ignore(size);
			skip_payload(elm_tagid);
		}
	case String:
		size = read_bswap<short>();
		get_stream().ignore(size);
		return;
	case ByteArray:
		size = read_bswap<int>();
		get_stream().ignore(size * sizeof(uint8_t));
		return;
	case IntArray:
		size = read_bswap<int>();
		get_stream().ignore(size * sizeof(int));
		return;
	case LongArray:
		size = read_bswap<int>();
		get_stream().ignore(size * sizeof(long long));
		return;
	case End:
		return;
	}
}


void Reader::iter_compound(std::string name, const IterCallback& callback) {
	must_seek_tag<TagID::Compound>(name);
	for(;;) {
		auto type = read_static(TagID::End);
		if(type == TagID::End)
			return;
		auto tag_name = read_string();
		callback(*this, type, tag_name);
	}
}


bool Reader::find_bool_str(std::string name, bool def) {
	if(!seek_tag<NBT::String>(name)) {
		return def;
	}
	return read_payload<NBT::String>() == "true";
}

TagHeader Reader::peek_tag() {
	auto tagid = read_static(TagID::End);
	if(tagid == TagID::End) {
		return TagHeader{.id = tagid};
	}
	return TagHeader{
		.id   = tagid,
		.name = read_string()
	};
}

void Reader::check_signature() {
	auto type = read_static(TagID::End);
	auto name_size = read_bswap<short>();
	if(type != TagID::Compound || name_size != 0) {
		throw Exception("stream does not contain correct nbt data");
	}
}

void Reader::read_payload_unsafe(TagID tagid, void *ptr) {
	switch(tagid) {
	case Byte:
		*reinterpret_cast<uint8_t*>(ptr) = read_payload<Byte>();
		break;
	case Short:
		*reinterpret_cast<short*>(ptr) = read_payload<Short>();
		break;
	case Int:
		*reinterpret_cast<int*>(ptr) = read_payload<Int>();
		break;
	case Long:
		*reinterpret_cast<long long*>(ptr) = read_payload<Long>();
		break;
	case Float:
		*reinterpret_cast<float*>(ptr) = read_payload<Float>();
		break;
	case Double:
		*reinterpret_cast<double*>(ptr) = read_payload<Double>();
		break;
	case ByteArray:
		*reinterpret_cast<std::vector<uint8_t>*>(ptr) = read_payload<ByteArray>();
		break;
	case String:
		*reinterpret_cast<std::string*>(ptr) = read_payload<String>();
		break;
	case IntArray:
		*reinterpret_cast<std::vector<int>*>(ptr) = read_payload<IntArray>();
		break;
	case LongArray:
		*reinterpret_cast<std::vector<long long>*>(ptr) = read_payload<LongArray>();
		break;
	default:
		break;
	}
}

}
