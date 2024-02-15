#include <gtest/gtest.h>
#include <sstream>

#include "minecpp/debug/TraceManager.h"
#include "minecpp/nbt/Parser.h"
#include "minecpp/nbt/trace/Trace.schema.h"

TEST(TraceTest, Trace_OK)
{
   minecpp::nbt::trace::ChunkDispatchRequested chunk_dispatch_requested;
   chunk_dispatch_requested.chunk_x = 13;
   chunk_dispatch_requested.chunk_z = 12;

   minecpp::debug::TraceObject<> obj("source.cpp", 20, 0, chunk_dispatch_requested);

   std::stringstream ss;
   obj.serialize(ss);

   ss.seekg(0, std::ios::beg);

   minecpp::nbt::Parser parser(ss);
   auto root  = parser.read_compound();
   auto trace = root[""].as<minecpp::nbt::CompoundContent>();

   EXPECT_EQ(trace["name"].as<std::string>(), "ChunkDispatchRequested");

   auto trace_data = trace["data"].as<minecpp::nbt::CompoundContent>();
   EXPECT_EQ(trace_data["chunk_x"].as<int>(), 13);
   EXPECT_EQ(trace_data["chunk_z"].as<int>(), 12);
}