#pragma once
#include <istream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <optional>
#include "tag.h"
#include <mineutils/reader.h>

namespace NBT {

class Parser : private Utils::Reader {
public:
    explicit Parser(std::istream& s);
    ~Parser();

    [[nodiscard]]
    TagPtr read_tag() const;

private:
	[[nodiscard]] TagMap read_compound() const;

	ListPayload read_list_payload() const;

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
	payload_of(TagID::ByteArray, read_byte_list());
	payload_of(TagID::String, read_string());
	payload_of(TagID::List, read_list_payload());
	payload_of(TagID::Compound, read_compound());
	payload_of(TagID::IntArray, read_int_list<int>());
	payload_of(TagID::LongArray, read_int_list<long long>());

	template<TagID t>
	PayloadTag<tagid_type(t)> *make_tag(std::string& name) const {
		return new PayloadTag<tagid_type(t)>(name, read_payload<t>());
	}

	template<TagID t>
	std::vector<tagid_type(t)> read_payload_array(int size) const {
		std::vector<tagid_type(t)> result(size);
		for(int i = 0; i < size; i++) {
			result[i] = read_payload<t>();
		}
		return std::move(result);
	}
};

}
