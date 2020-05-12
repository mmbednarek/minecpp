#include "gtest/gtest.h"
#include "../common/packet/reader.h"

using namespace Packet;

TEST(PacketReader, VarInt) {
	char buff[] {(char) 0xe2, (char) 0xde, 0x0b};
	auto stream = std::stringstream();
	stream.write(buff, sizeof(buff));

	Reader r(stream);
	int v = r.read_varint();

	ASSERT_EQ(v, 192354);
}

