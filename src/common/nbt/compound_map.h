#pragma once
#include <map>
#include <string>
#include "tag.h"
#include "compound.h"

namespace NBT {

template<TagID t>
class CompoundMap : public std::map<std::string, tagid_type(t)>, public Compound {
public:
	TaggedPtr load_value(TagID tagid, const std::string &name) override {
		return TaggedPtr{
			.tagid = t,
			.ptr = &this->operator[](name),
		};
	}

	Compound *load_compound(const std::string &name) override {
		return nullptr;
	}
};

}

