#pragma once
#include <string>
#include <cstdint>
#include <cstring>
#include <functional>
#include <utils/reader.h>
#include <utils/format.h>
#include "tag.h"

namespace NBT {

struct TagHeader {
	TagID id;
	std::string name;
};

class Reader : private Utils::Reader {
public:
	explicit Reader(std::istream& s);

	typedef std::function<void(Reader& r, const TagID type, std::string name)> IterCallback;


	template<TagID t>
	tagid_type(t) must_find_tag(std::string name) {
		must_seek_tag<t>(name);
		return read_payload<t>();
	}

	template<TagID t>
	tagid_type(t) expect_tag(std::string name) {
		auto type = read_static(TagID::End);
		if(type == t) {
			throw Exception(Utils::format("[nbt] incorrect tag type expected {} got {}", tagid_to_str(t), tagid_to_str(type)));
		}

		auto tag_name = read_string();
		if(tag_name != name) {
			throw Exception(Utils::format("[nbt] incorrect tag name expected {} got {}", name, tag_name));
		}

		return read_payload<t>();
	}

	template<TagID t>
	tagid_type(t) find_value(std::string name, tagid_type(t) def) {
		if(!seek_tag<t>(name)) {
			return def;
		}
		return read_payload<t>();
	}

	template<TagID t>
	std::vector<tagid_type(t)> find_list(std::string name) {
		if(!seek_tag<t>(name)) {
			return std::vector<tagid_type(t)>();
		}
		return read_list_payload<t>();
	}

	template<TagID t>
	std::vector<tagid_type(t)> read_list_payload() {
		auto elm_type = read_static(TagID::End);
		if(elm_type != t) {
			throw Exception("invalid list type");
		}

		auto size = read_bswap<int>();
		std::vector<tagid_type(t)> result(size);
		for(int i = 0; i < size; i++) {
			result[i] = read_payload<t>();
		}

		return result;
	}

	bool find_bool_str(std::string name, bool def);
	void find_compound(std::string name);
	void leave_compound();
	void iter_compound(std::string name, const IterCallback& callback);
	void skip_payload(TagID tagid);
	void read_payload_unsafe(TagID tagid, void* ptr);
	TagHeader peek_tag();
	void check_signature();

private:
	template<TagID t>
	inline tagid_type(t) read_payload() const = delete;

#define payload_of(typeid, value) \
	template<> \
	inline tagid_type(typeid) read_payload<typeid>() const { \
		return value; \
	}

	payload_of(TagID::Byte, read_static<uint8_t>(0));
	payload_of(TagID::Short, read_bswap<short>());
	payload_of(TagID::Int, read_bswap<int>());
	payload_of(TagID::Long, read_bswap<long long>());
	payload_of(TagID::Float, read_float());
	payload_of(TagID::Double, read_double());
	payload_of(TagID::ByteArray, read_byte_array());
	payload_of(TagID::String, read_string());
	payload_of(TagID::IntArray, read_int_array<int>());
	payload_of(TagID::LongArray, read_int_array<long long>());

	template<TagID t>
	bool seek_tag(std::string& name) {
		for(;;) {
			auto type = read_static(TagID::End);
			if(type == TagID::End) {
				get_stream().seekg(-sizeof(TagID), std::ios_base::cur);
				return false;
			}

			auto name_size = read_bswap<short>();
			if(type != t || name_size != static_cast<short>(name.size())) {
				get_stream().seekg(name_size, std::ios_base::cur);
				skip_payload(type);
				continue;
			}

			char tag_name[name_size];
			get_stream().read(tag_name, name_size);

			if(memcmp(tag_name, name.data(), name_size) != 0) {
				skip_payload(type);
				continue;
			}

			return true;
		}
	}

	template<TagID t>
	void must_seek_tag(std::string& name) {
		if(!seek_tag<t>(name)) {
			std::string msg("could not find tag ");
			msg.append(name);
			throw Exception(msg);
		}
	}
};

}

