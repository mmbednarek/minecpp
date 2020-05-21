#include "recipe.h"

#include <stdexcept>
#include <utility>

namespace Game {

const ItemStack &Game::Recipe::outcome() const { return _outcome_item; }
RecipeType Recipe::type() const { return _type; }

Recipe::Recipe(ItemStack item, std::string group,
               Recipe::CraftingShaped details)
    : _outcome_item(item), _type(RecipeType::CraftingShaped),
      _details(std::move(details)), _group(std::move(group)) {}

template <> Recipe::CraftingShaped Recipe::details() const {
   if (_type != RecipeType::CraftingShaped)
      throw std::runtime_error("invalid recipe type");

   return std::get<Recipe::CraftingShaped>(_details);
}

Recipe::Recipe(ItemStack item, std::string group,
               Recipe::CraftingShapeless details)
    : _outcome_item(item), _type(RecipeType::CraftingShapeless),
      _details(std::move(details)), _group(std::move(group)) {}

template <> Recipe::CraftingShapeless Recipe::details() const {
   if (_type != RecipeType::CraftingShapeless)
      throw std::runtime_error("invalid recipe type");

   return std::get<Recipe::CraftingShapeless>(_details);
}

Recipe::Recipe(ItemStack item, RecipeType method)
    : _outcome_item(item), _type(method), _details(Recipe::Special{}),
      _group("special") {}

Recipe::Recipe(ItemStack item, std::string group, RecipeType method,
               Recipe::HeatTreatment smelted)
    : _outcome_item(item), _type(method), _details(std::move(smelted)),
      _group(std::move(group)) {
   switch (method) {
   case Smelting:
   case Blasting:
   case Smoking:
   case CampfireCooking:
      break;
   default:
      throw std::runtime_error("invalid method for heat treatment");
   }
}

template <> Recipe::HeatTreatment Recipe::details() const {
   if (_type != RecipeType::Smelting)
      throw std::runtime_error("invalid recipe type");

   return std::get<Recipe::HeatTreatment>(_details);
}

Recipe::Recipe(ItemStack item, std::string group, Recipe::StoneCutting details)
    : _outcome_item(item), _type(RecipeType::StoneCutting),
      _details(std::move(details)), _group(std::move(group)) {}

template <> Recipe::StoneCutting Recipe::details() const {
   if (_type != RecipeType::StoneCutting)
      throw std::runtime_error("invalid recipe type");

   return std::get<Recipe::StoneCutting>(_details);
}

} // namespace Game