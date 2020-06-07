#pragma once
#include "color.h"

namespace Game::Block {

enum class PushReaction { Normal, Destroy, Block, Ignore, PushOnly };

struct Material {
   ColorId color = ColorId::Dirt;
   PushReaction push_reaction = PushReaction::Normal;
   bool blocks_movement = true;
   bool flammable = false;
   bool requires_no_tool = true;
   bool is_liquid = false;
   bool is_opaque = true;
   bool replaceable = false;
   bool is_solid = true;

   static const Material Air;
   static const Material StructureVoid;
   static const Material Portal;
   static const Material Carpet;
   static const Material Plants;
   static const Material OceanPlant;
   static const Material TallPlants;
   static const Material SeaGrass;
   static const Material Water;
   static const Material BubbleColumn;
   static const Material Lava;
   static const Material Snow;
   static const Material Fire;
   static const Material Miscellaneous;
   static const Material Web;
   static const Material RedstoneLight;
   static const Material Clay;
   static const Material Earth;
   static const Material Organic;
   static const Material PackedIce;
   static const Material Sand;
   static const Material Sponge;
   static const Material Shulker;
   static const Material Wood;
   static const Material BambooSapling;
   static const Material Bamboo;
   static const Material Wool;
   static const Material Tnt;
   static const Material Leaves;
   static const Material Glass;
   static const Material Ice;
   static const Material Cactus;
   static const Material Rock;
   static const Material Iron;
   static const Material SnowBlock;
   static const Material Anvil;
   static const Material Barrier;
   static const Material Piston;
   static const Material Coral;
   static const Material Gourd;
   static const Material DragonEgg;
   static const Material Cake;
};

} // namespace Game::Block
