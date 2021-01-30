#pragma once
#include <minecpp/network/message/writer.h>
#include <minepb/chunk.pb.h>

namespace minecpp::network::message {

void write_chunk(network::message::Writer &w, const minecpp::chunk::NetChunk &chunk);
void write_light(Writer &w, const minecpp::chunk::NetChunk &chunk);

}
