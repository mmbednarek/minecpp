#pragma once

#include <mb/int.h>
#include <minecpp/util/Uuid.h>

namespace minecpp::game {

using ChunkHash    = mb::u64;
using SlotId       = mb::u32;
using PlayerId     = util::Uuid;
using BlockId      = mb::i32;
using EntityId     = mb::u32;
using BlockStateId = mb::u32;
using StateOffset  = mb::i32;
using ItemId       = mb::i32;
using LightValue   = mb::u8;

}// namespace minecpp::game
