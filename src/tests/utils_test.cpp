#include "gtest/gtest.h"
#include "../common/utils/format.h"
#include "../common/utils/random.h"

TEST(Utils, Format) {
	auto empty_format = Utils::format("Hello!");
	ASSERT_EQ(empty_format, "Hello!");
	auto format_one = Utils::format("Hello {}!", "World");
	ASSERT_EQ(format_one, "Hello World!");
	auto format_many = Utils::format("Many values {}, {}, {}.", "something", 14, 23.567);
	ASSERT_EQ(format_many, "Many values something, 14, 23.567.");
}

TEST(Utils, Random) {
	Utils::Random r(1234);
	int v;
	v = r.next_int(12);
	ASSERT_EQ(v, 8);
	v = r.next_int(34);
	ASSERT_EQ(v, 23);
	v = r.next_int(67);
	ASSERT_EQ(v, 29);
}
