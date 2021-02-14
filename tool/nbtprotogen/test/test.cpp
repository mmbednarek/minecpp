#include <gtest/gtest.h>
#include <sstream>
#include "test.nbt.h"

TEST(nbtproto, full) {
   proto::nbt::test::Foo f;
   f.value = "hello";
   f.stuff["foo"] = 4;
   f.stuff["bar"] = 5;

   proto::nbt::test::Foo f2;
   f2.value = "world";
   f2.stuff["oof"] = 2;
   f2.stuff["rab"] = 3;

   proto::nbt::test::Bar b;
   b.foo_map["foo1"] = f;
   b.foo_map["foo2"] = f2;
   b.foo.emplace_back(f);

   minecpp::nbt::CompoundContent meta;
   meta["stuff"] = minecpp::nbt::make_string("foo");
   b.meta = meta;

   std::stringstream ss;
   b.serialize(ss, "");
   ss.seekg(0, std::ios::beg);

   auto bdes = proto::nbt::test::Bar::deserialize(ss);
   ASSERT_EQ(bdes.meta["stuff"].as<std::string>(), "foo");
   ASSERT_EQ(bdes.foo[0].value, "hello");
   ASSERT_EQ(bdes.foo[0].stuff["foo"], 4);
   ASSERT_EQ(bdes.foo[0].stuff["bar"], 5);
   ASSERT_EQ(bdes.foo_map["foo1"].value, "hello");
   ASSERT_EQ(bdes.foo_map["foo1"].stuff["foo"], 4);
   ASSERT_EQ(bdes.foo_map["foo1"].stuff["bar"], 5);
   ASSERT_EQ(bdes.foo_map["foo2"].value, "world");
   ASSERT_EQ(bdes.foo_map["foo2"].stuff["oof"], 2);
   ASSERT_EQ(bdes.foo_map["foo2"].stuff["rab"], 3);
}