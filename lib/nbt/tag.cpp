#include "tag.h"

namespace NBT {

Tag::Tag(TagID t, std::string& s) :
        _type(t),
        _name(std::move(s))
{
}

TagID Tag::type() {
    return _type;
}

const std::string &Tag::name() const {
    return _name;
}

std::string tagid_to_str(TagID tagid) {
	switch(tagid) {
	case End:
		return "End";
	case Byte:
		return "Byte";
	case Short:
		return "Short";
	case Int:
		return "Int";
	case Long:
		return "Long";
	case Float:
		return "Float";
	case Double:
		return "Double";
	case ByteArray:
		return "ByteArray";
	case String:
		return "String";
	case List:
		return "List";
	case Compound:
		return "Compound";
	case IntArray:
		return "IntArray";
	case LongArray:
		return "LongArray";
	}
	return "Unknown";
}

ListPayload::ListPayload(TagID type, void *ptr) : _type(type), ptr(ptr) {
}

ListPayload::ListPayload() : _type(End), ptr(nullptr) {
}

TagID ListPayload::type() {
	return _type;
}

}
