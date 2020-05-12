#include "snbt.h"
#include <sstream>

namespace NBT {

static void pad(std::ostream &s, int n) {
	for(int i = 0; i < n; i++) {
		s << '\t';
	}
}

static void _encode_snbt(std::ostream& s, TagPtr& p, int level);

template<typename T, typename C, char p>
static void encode_int_array(std::ostream &s, std::vector<T> &vec, int level) {
	auto it = vec.begin();
	if(it == vec.end()) {
		s << "[]";
		return;
	}
	char prefix[]{'[', p , ';', '\n', 0x00};
	s << prefix;
	pad(s, level+1);
	s << (C)*it;
	for(++it; it != vec.end(); ++it) {
		s << ",\n";
		pad(s, level+1);
		s << (C)*it;
	}
	s << '\n';
	pad(s, level);
	s << ']';
}

static void encode_compound(std::ostream &s, TagMap &m, int level) {
	auto it = m.begin();
	if(it == m.end()) {
		s << "{}";
		return;
	}
	auto& f = *it;
	s << "{\n";
	pad(s, level+1);
	s << f.first << ": ";
	_encode_snbt(s, f.second, level+1);
	for(++it; it != m.end(); ++it) {
		s << ",\n";
		pad(s, level+1);
		auto& e = *it;
		s << e.first << ": ";
		_encode_snbt(s, e.second, level+1);
	}
	s << '\n';
	pad(s, level);
	s << '}';
}

static void encode_list(std::ostream& s, ListPayload& p, int level);

template<TagID t>
inline void encode_element(std::ostream &s, tagid_type(t) &e, [[maybe_unused]] int level) = delete;
template<>
inline void encode_element<TagID::Byte>(std::ostream &s, uint8_t &e, [[maybe_unused]] int level) { s << (int)e << 'b'; }
template<>
inline void encode_element<TagID::Short>(std::ostream &s, short &e, [[maybe_unused]] int level) { s << e << 's'; }
template<>
inline void encode_element<TagID::Int>(std::ostream &s, int &e, [[maybe_unused]] int level) { s << e; }
template<>
inline void encode_element<TagID::Long>(std::ostream &s, long long &e, [[maybe_unused]] int level) { s << e << 'l'; }
template<>
inline void encode_element<TagID::Float>(std::ostream &s, float &e, [[maybe_unused]] int level) { s << e << 'f'; }
template<>
inline void encode_element<TagID::Double>(std::ostream &s, double &e, [[maybe_unused]] int level) { s << e << 'd'; }
template<>
inline void
encode_element<TagID::ByteArray>(std::ostream &s, std::vector<uint8_t> &e, int level) {
	encode_int_array<uint8_t, int, 'B'>(s, e, level);
}
template<>
inline void encode_element<TagID::String>(std::ostream &s, std::string &e, [[maybe_unused]] int level) { s << '"' << e << '"'; }
template<>
inline void encode_element<TagID::List>(std::ostream &s, ListPayload &e, int level) {
	encode_list(s, e, level);
}
template<>
inline void encode_element<TagID::Compound>(std::ostream &s, TagMap &e, [[maybe_unused]] int level) {
	encode_compound(s, e, level);
}
template<>
inline void
encode_element<TagID::IntArray>(std::ostream &s, std::vector<int> &e, int level) {
	encode_int_array<int, int, 'I'>(s, e, level);
}
template<>
inline void encode_element<TagID::LongArray>(std::ostream &s, std::vector<long long> &e, int level) {
	encode_int_array<long long, long long, 'L'>( s, e, level);
}

template<TagID t>
static void encode_vector(std::ostream& s, std::vector<tagid_type(t)>& vec, int level) {
	auto it = vec.begin();
	if(it == vec.end()) {
		s << "[]";
		return;
	}
	s << "[\n";
	pad(s, level+1);
	encode_element<t>(s, *it, level+1);
	for(++it; it != vec.end(); ++it) {
		s << ",\n";
		pad(s, level+1);
		encode_element<t>(s, *it, level+1);
	}
	s << '\n';
	pad(s, level);
	s << ']';
}

static void encode_list(std::ostream& s, ListPayload& p, int level) {
	switch(p.type()) {
	case End:
		s << "[]";
		break;
	case Byte:
		encode_vector<Byte>(s, p.value<uint8_t>(), level); break;
	case Short:
		encode_vector<Short>(s, p.value<short>(), level); break;
	case Int:
		encode_vector<Int>(s, p.value<int>(), level); break;
	case Long:
		encode_vector<Long>(s, p.value<long long>(), level); break;
	case Float:
		encode_vector<Float>(s, p.value<float>(), level); break;
	case Double:
		encode_vector<Double>(s, p.value<double>(), level); break;
	case ByteArray:
		encode_vector<ByteArray>(s, p.value<std::vector<uint8_t>>(), level); break;
	case String:
		encode_vector<String>(s, p.value<std::string>(), level); break;
	case List:
		encode_vector<List>(s, p.value<ListPayload>(), level); break;
	case Compound:
		encode_vector<Compound>(s, p.value<TagMap>(), level); break;
	case IntArray:
		encode_vector<IntArray>(s, p.value<std::vector<int>>(), level); break;
	case LongArray:
		encode_vector<LongArray>(s, p.value<std::vector<long long>>(), level); break;
	default:
		s << "[##invalid##]";
	}
}

static void _encode_snbt(std::ostream& s, TagPtr& p, int level) {
	switch(p->type()) {
	case Byte:
		encode_element<Byte>(s, p->value<uint8_t>(), level); break;
	case Short:
		encode_element<Short>(s, p->value<short>(), level); break;
	case Int:
		encode_element<Int>(s, p->value<int>(), level); break;
	case Long:
		encode_element<Long>(s, p->value<long long>(), level); break;
	case Float:
		encode_element<Float>(s, p->value<float>(), level); break;
	case Double:
		encode_element<Double>(s, p->value<double>(), level); break;
	case ByteArray:
		encode_element<ByteArray>(s, p->value<std::vector<uint8_t>>(), level); break;
	case String:
		encode_element<String>(s, p->value<std::string>(), level); break;
	case List:
		encode_element<List>(s, p->value<ListPayload>(), level); break;
	case Compound:
		encode_element<Compound>(s, p->value<TagMap>(), level); break;
	case IntArray:
		encode_element<IntArray>(s, p->value<std::vector<int>>(), level); break;
	case LongArray:
		encode_element<LongArray>(s, p->value<std::vector<long long>>(), level); break;
	default:
		s << "##invalid##";
	}
}


void encode_snbt(std::ostream& s, TagPtr& p) {
	_encode_snbt(s, p, 0);
}

std::string as_string(TagPtr& p) {
	std::stringstream ss;
	encode_snbt(ss, p);
	return ss.str();
}

}
