#pragma once
#include <string>
#include "tag.h"
#include "reader.h"

namespace NBT {

class Compound {
public:
	struct TaggedPtr {
		TagID tagid;
		void  *ptr;
	};

	Compound();

	void load(Reader& r);
	virtual TaggedPtr load_value(TagID tagid, const std::string& name) = 0;
	virtual Compound *load_compound(const std::string& name) = 0;
};

}
