#include "gtest/gtest.h"
#include <nbt/compound_map.h>
#include <nbt/parser.h>
#include <nbt/reader.h>
#include <nbt/snbt.h>

using namespace NBT;

namespace {

TEST(NBT_Parser, TagByte) {
   char buff[]{0x01, 0x00, 0x04, 'T', 'e', 's', 't', 0x42};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Parser r(stream);
   auto tag = r.read_tag();

   ASSERT_EQ(tag->name(), "Test");
   ASSERT_EQ(tag->value<uint8_t>(), 0x42);
   ASSERT_EQ(as_string(tag), "66b");
}

TEST(NBT_Parser, TagShort) {
   char buff[]{0x02, 0x00, 0x05, 'T', 'e', 's', 't', 's', 0x01, 0x50};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Parser r(stream);
   auto tag = r.read_tag();

   ASSERT_EQ(tag->name(), "Tests");
   ASSERT_EQ(tag->value<short>(), 0x150);
   ASSERT_EQ(as_string(tag), "336s");
}

TEST(NBT_Parser, TagInt) {
   char buff[]{0x03, 0x00, 0x06, 'T',  'e',  's', 't',
               's',  '1',  0x10, 0x21, 0x32, 0x43};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Parser r(stream);
   auto tag = r.read_tag();

   ASSERT_EQ(tag->name(), "Tests1");
   ASSERT_EQ(tag->value<int>(), 0x10213243);
   ASSERT_EQ(as_string(tag), "270611011");
}

TEST(NBT_Parser, TagLong) {
   char buff[]{0x04, 0x00, 0x06, 'T',  'e',  's',  't',  's', '1',
               0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x08};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Parser r(stream);
   auto tag = r.read_tag();

   ASSERT_EQ(tag->name(), "Tests1");
   ASSERT_EQ(tag->value<long long>(), 0x1020304050607008);
   ASSERT_EQ(as_string(tag), "1161981756646125576l");
}

TEST(NBT_Parser, TagFloat) {
   char buff[]{0x05, 0x00, 0x10, 'A',  'b',        's',  'o', 'r',
               'p',  't',  'i',  'o',  'n',        'A',  'm', 'o',
               'u',  'n',  't',  0x40, (char)0xa0, 0x00, 0x00};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Parser r(stream);
   auto tag = r.read_tag();

   ASSERT_EQ(tag->name(), "AbsorptionAmount");
   ASSERT_EQ(tag->value<float>(), 5.0f);
   ASSERT_EQ(as_string(tag), "5f");
}

TEST(NBT_Parser, TagDouble) {
   char buff[]{0x06, 0x00, 0x11, 0x42, 0x6f, 0x72, 0x64, 0x65, 0x72, 0x57,
               0x61, 0x72, 0x6e, 0x69, 0x6e, 0x67, 0x54, 0x69, 0x6d, 0x65,
               0x40, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Parser r(stream);
   auto tag = r.read_tag();

   ASSERT_EQ(tag->name(), "BorderWarningTime");
   ASSERT_EQ(tag->value<double>(), 15.0);
   ASSERT_EQ(as_string(tag), "15d");
}

TEST(NBT_Parser, MultipleTags) {
   char buff[]{0x03, 0x00, 0x06, 'T',  'e',  's', 't', 's', '1',  0x10, 0x21,
               0x32, 0x43, 0x02, 0x00, 0x03, 'a', 'b', 'c', 0x10, 0x20};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Parser r(stream);

   auto tag1 = r.read_tag();
   auto tag2 = r.read_tag();

   ASSERT_EQ(tag1->name(), "Tests1");
   ASSERT_EQ(tag1->value<int>(), 0x10213243);
   ASSERT_EQ(tag2->name(), "abc");
   ASSERT_EQ(tag2->value<short>(), 0x1020);
}

TEST(NBT_Parser, NullTag) {
   char buff[]{0x03, 0x00, 0x06, 'T',  'e',  's', 't',
               's',  '1',  0x10, 0x21, 0x32, 0x43};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Parser r(stream);

   auto tag1 = r.read_tag();
   auto tag2 = r.read_tag();

   ASSERT_EQ(tag1->name(), "Tests1");
   ASSERT_EQ(tag1->value<int>(), 0x10213243);
   ASSERT_FALSE(tag2);
}

TEST(NBT_Parser, ByteArrayTag) {
   char buff[]{0x07, 0x00, 0x04, 'T',  'e',  's',  't',  0x00,
               0x00, 0x00, 0x05, 0x01, 0x02, 0x03, 0x04, 0x05};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));
   Parser r(stream);

   auto tag = r.read_tag();

   std::vector<uint8_t> expected_vec{0x01, 0x02, 0x03, 0x04, 0x05};

   ASSERT_EQ(tag->name(), "Test");
   ASSERT_EQ(tag->value<std::vector<uint8_t>>(), expected_vec);
   ASSERT_EQ(as_string(tag), "[B;\n\t1,\n\t2,\n\t3,\n\t4,\n\t5\n]");
}

TEST(NBT_Parser, StringTag) {
   char buff[]{0x08, 0x00, 0x04, 'T', 'e', 's', 't',
               0x00, 0x05, 'v',  'a', 'l', 'u', 'e'};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));
   Parser r(stream);

   auto tag = r.read_tag();

   ASSERT_EQ(tag->name(), "Test");
   ASSERT_EQ(tag->value<std::string>(), "value");
   ASSERT_EQ(as_string(tag), "\"value\"");
}

TEST(NBT_Parser, StringListTag) {
   char buff[]{0x09, 0x00, 0x0c, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x42,
               0x72, 0x61, 0x6e, 0x64, 0x73, 0x08, 0x00, 0x00, 0x00, 0x02,
               0x00, 0x07, 0x76, 0x61, 0x6e, 0x69, 0x6c, 0x6c, 0x61, 0x00,
               0x07, 'm',  'i',  'n',  'e',  'c',  'p',  'p'};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));
   Parser r(stream);

   auto tag = r.read_tag();
   auto list_tag = tag->value<ListPayload>();

   std::vector<std::string> expected_vec{"vanilla", "minecpp"};

   ASSERT_EQ(tag->name(), "ServerBrands");
   ASSERT_EQ(list_tag.type(), TagID::String);
   ASSERT_EQ(list_tag.value<std::string>(), expected_vec);
   ASSERT_EQ(as_string(tag), "[\n\t\"vanilla\",\n\t\"minecpp\"\n]");
}

TEST(NBT_Parser, CompoundTag) {
   char buff[]{0x0a, 0x00, 0x04, 'D',  'a',  't',  'a',  0x02, 0x00, 0x03,
               'N',  'u',  'm',  0x01, 0x23, 0x03, 0x00, 0x05, 'S',  't',
               'u',  'f',  'f',  0x10, 0x20, 0x30, 0x40, 0x00};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));
   Parser r(stream);

   auto tag = r.read_tag();
   auto &tag_map = tag->value<NBT::TagMap>();
   auto &num_tag = tag_map["Num"];
   auto &stuff_tag = tag_map["Stuff"];

   ASSERT_EQ(num_tag->name(), "Num");
   ASSERT_EQ(num_tag->value<short>(), 0x0123);
   ASSERT_EQ(stuff_tag->name(), "Stuff");
   ASSERT_EQ(stuff_tag->value<int>(), 0x10203040);
   ASSERT_EQ(as_string(tag), "{\n\tNum: 291s,\n\tStuff: 270544960\n}");
}

TEST(NBT_Parser, IntArrayTag) {
   char buff[]{0x0b, 0x00, 0x06, 'i',  'n',  't',  'a',  'r',  'r',  0x00, 0x00,
               0x00, 0x02, 0x01, 0x02, 0x03, 0x04, 0x10, 0x20, 0x30, 0x40};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));
   Parser r(stream);

   auto tag = r.read_tag();

   std::vector<int> expect_vec{0x01020304, 0x10203040};

   ASSERT_EQ(tag->name(), "intarr");
   ASSERT_EQ(tag->value<std::vector<int>>(), expect_vec);
   ASSERT_EQ(as_string(tag), "[I;\n\t16909060,\n\t270544960\n]");
}

TEST(NBT_Parser, LongArrayTag) {
   char buff[]{0x0c, 0x00, 0x07, 'l',  'o',  'n',       'g',  'a',
               'r',  'r',  0x00, 0x00, 0x00, 0x02,      0x01, 0x02,
               0x03, 0x04, 0x05, 0x06, 0x07, 0x08,      0x10, 0x20,
               0x30, 0x40, 0x50, 0x60, 0x70, (char)0x80};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));
   Parser r(stream);

   auto tag = r.read_tag();

   std::vector<long long> expect_vec{0x0102030405060708, 0x1020304050607080};

   ASSERT_EQ(tag->name(), "longarr");
   ASSERT_EQ(tag->value<std::vector<long long>>(), expect_vec);
   ASSERT_EQ(as_string(tag),
             "[L;\n\t72623859790382856,\n\t1161981756646125696\n]");
}

TEST(NBT_Compound, Map) {
   char buff[]{0x02, 0x00, 0x05, 's', 't', 'u', 'f',  'f',  0x12, 0x34, 0x02,
               0x00, 0x04, 't',  'e', 's', 't', 0x43, 0x21, 0x02, 0x00, 0x06,
               'a',  'b',  'c',  '1', '2', '3', 0x11, 0x22, 0x00};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));
   Reader r(stream);

   CompoundMap<Short> m;
   m.load(r);

   ASSERT_EQ(m["stuff"], 0x1234);
   ASSERT_EQ(m["test"], 0x4321);
   ASSERT_EQ(m["abc123"], 0x1122);
}

TEST(NBT_Reader, Int) {
   char buff[]{0x0a, 0x00, 0x00, 0x03, 0x00, 0x06, 'T',  'e', 's',
               't',  's',  '1',  0x10, 0x21, 0x32, 0x43, 0x00};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Reader r(stream);
   r.check_signature();
   auto tag = r.must_find_tag<Int>("Tests1");

   ASSERT_EQ(tag, 0x10213243);
}

TEST(NBT_Reader, Compound) {
   char buff[]{0x0a, 0x00, 0x00, 0x03, 0x00, 0x06, 'T',  'e',  's',
               't',  's',  '1',  0x12, 0x34, 0x56, 0x78, 0x0a, 0x00,
               0x06, 'V',  'a',  'l',  'u',  'e',  's',  0x02, 0x00,
               0x03, 'F',  'o',  'o',  0x12, 0x35, 0x00, 0x00};
   auto stream = std::stringstream();
   stream.write(buff, sizeof(buff));

   Reader r(stream);
   r.check_signature();

   auto tag2 = r.must_find_tag<TagID::Int>("Tests1");
   r.find_compound("Values");
   auto tag1 = r.must_find_tag<TagID::Short>("Foo");
   r.leave_compound();

   ASSERT_EQ(tag1, 0x1235);
   ASSERT_EQ(tag2, 0x12345678);
}

} // namespace
