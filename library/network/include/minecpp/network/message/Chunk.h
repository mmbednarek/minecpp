#pragma once
#include <minecpp/network/message/Writer.h>
#include <minecpp/proto/chunk/Chunk.pb.h>

namespace minecpp::network::message {

void write_chunk(network::message::Writer &w, const minecpp::proto::chunk::Chunk &chunk);
void write_light(Writer &w, const minecpp::proto::chunk::Chunk &chunk);

}// namespace minecpp::network::message
