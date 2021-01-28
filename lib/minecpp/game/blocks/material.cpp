#include <minecpp/game/blocks/material.h>

namespace Game::Block {

const Material Material::Air{
    .color = ColorId::Air,
    .blocks_movement = false,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::StructureVoid{
    .color = ColorId::Air,
    .blocks_movement = false,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::Portal{
    .color = ColorId::Air,
    .push_reaction = PushReaction::Block,
    .blocks_movement = false,
    .is_opaque = false,
    .is_solid = false,
};

const Material Material::Carpet{
    .color = ColorId::Wool,
    .blocks_movement = false,
    .flammable = true,
    .is_opaque = false,
    .is_solid = false,
};

const Material Material::Plants{
    .color = ColorId::Foliage,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .is_opaque = false,
    .is_solid = false,
};

const Material Material::OceanPlant{
    .color = ColorId::Water,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .is_opaque = false,
    .is_solid = false,
};

const Material Material::TallPlants{
    .color = ColorId::Foliage,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .flammable = true,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::SeaGrass{
    .color = ColorId::Water,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::Water{
    .color = ColorId::Water,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .is_liquid = true,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::BubbleColumn{
    .color = ColorId::Water,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .is_liquid = true,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::Lava{
    .color = ColorId::Tnt,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .is_liquid = true,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::Snow{
    .color = ColorId::Snow,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .requires_no_tool = false,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::Fire{
    .color = ColorId::Air,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .is_opaque = false,
    .replaceable = true,
    .is_solid = false,
};

const Material Material::Miscellaneous{
    .color = ColorId::Air,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .is_opaque = false,
    .is_solid = false,
};

const Material Material::Web{
    .color = ColorId::Wool,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .requires_no_tool = false,
    .is_opaque = false,
};

const Material Material::RedstoneLight{
    .color = ColorId::Air,
};

const Material Material::Clay{
    .color = ColorId::Clay,
};

const Material Material::Earth{
    .color = ColorId::Dirt,
};

const Material Material::Organic{
    .color = ColorId::Grass,
};

const Material Material::PackedIce{
    .color = ColorId::Ice,
};

const Material Material::Sand{
    .color = ColorId::Sand,
};

const Material Material::Sponge{
    .color = ColorId::Yellow,
};

const Material Material::Shulker{
    .color = ColorId::Purple,
};

const Material Material::Wood{
    .color = ColorId::Wood,
    .flammable = true,
};

const Material Material::BambooSapling{
    .color = ColorId::Wood,
    .push_reaction = PushReaction::Destroy,
    .blocks_movement = false,
    .flammable = true,
};

const Material Material::Bamboo{
    .color = ColorId::Wood,
    .push_reaction = PushReaction::Destroy,
    .flammable = true,
};

const Material Material::Wool{
    .color = ColorId::Wool,
    .flammable = true,
};

const Material Material::Tnt{
    .color = ColorId::Tnt,
    .flammable = true,
    .is_opaque = false,
};

const Material Material::Leaves{
    .color = ColorId::Foliage,
    .push_reaction = PushReaction::Destroy,
    .flammable = true,
    .is_opaque = false,
};

const Material Material::Glass{
    .color = ColorId::Air,
    .is_opaque = false,
};

const Material Material::Ice{
    .color = ColorId::Ice,
    .is_opaque = false,
};

const Material Material::Cactus{
    .color = ColorId::Foliage,
    .push_reaction = PushReaction::Destroy,
    .is_opaque = false,
};

const Material Material::Rock{
    .color = ColorId::Stone,
    .requires_no_tool = false,
};

const Material Material::Iron{
    .color = ColorId::Iron,
    .requires_no_tool = false,
};

const Material Material::SnowBlock{
    .color = ColorId::Snow,
    .requires_no_tool = false,
};

const Material Material::Anvil{
    .color = ColorId::Iron,
    .push_reaction = PushReaction::Block,
    .requires_no_tool = false,
};

const Material Material::Barrier{
    .color = ColorId::Air,
    .push_reaction = PushReaction::Block,
    .requires_no_tool = false,
};

const Material Material::Piston{
    .color = ColorId::Stone,
    .push_reaction = PushReaction::Block,
};

const Material Material::Coral{
    .color = ColorId::Foliage,
    .push_reaction = PushReaction::Destroy,
};

const Material Material::Gourd{
    .color = ColorId::Foliage,
    .push_reaction = PushReaction::Destroy,
};

const Material Material::DragonEgg{
    .color = ColorId::Foliage,
    .push_reaction = PushReaction::Destroy,
};

const Material Material::Cake{
    .color = ColorId::Air,
    .push_reaction = PushReaction::Destroy,
};

const Material Material::NetherWood{
    .color = ColorId::Wood,
};

} // namespace Game::Block
