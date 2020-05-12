#include "compound.h"

namespace NBT {

Compound::Compound() = default;

void Compound::load(Reader& r) {
	for(;;) {
		Compound *compound;
		auto header = r.peek_tag();
		switch(header.id) {
		case TagID::End:
			return;
		case TagID::Compound:
			compound = load_compound(header.name);
			if(compound)
				compound->load(r);
			continue;
		case TagID::List:
			// TODO: handle
			return;
		default: break;
		}
		auto result = load_value(header.id, header.name);
		if(result.tagid == header.id && result.ptr) {
			r.read_payload_unsafe(result.tagid, result.ptr);
		}
	}
}

}
