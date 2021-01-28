#pragma once
#include <minecpp/network/msg/writer.h>
#include <minepb/chunk.pb.h>

namespace MineNet::Message {

void write_chunk(MineNet::Message::Writer &w, const minecpp::chunk::NetChunk &chunk);
void write_light(Writer &w, const minecpp::chunk::NetChunk &chunk);

}
