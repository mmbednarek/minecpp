#pragma once
#include <minepb/chunk.pb.h>
#include <minenet/msg/writer.h>

namespace MineNet::Message {

void write_chunk(MineNet::Message::Writer &w, const minecpp::chunk::NetChunk &chunk);

}
