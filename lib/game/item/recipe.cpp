#include <minecpp/game/item/recipe.h>
#include <stdexcept>
#include <utility>

namespace minecpp::game::item {

const ItemStack &Recipe::outcome() const { return _outcome_item; }

RecipeType Recipe::type() const { return _type; }

Recipe::Recipe(ItemStack item, std::string group, Recipe::CraftingShaped details) :
    _outcome_item(item),
    _type(RecipeType::CraftingShaped),
    _details(std::move(details)),
    _group(std::move(group))
{
}

Recipe::Recipe(ItemStack item, std::string group, Recipe::CraftingShapeless details) :
    _outcome_item(item),
    _type(RecipeType::CraftingShapeless),
    _details(std::move(details)),
    _group(std::move(group))
{
}

Recipe::Recipe(ItemStack item, RecipeType method) :
    _outcome_item(item),
    _type(method),
    _details(Recipe::Special{}),
    _group("special")
{
}

Recipe::Recipe(ItemStack item, std::string group, RecipeType method, Recipe::HeatTreatment smelted) :
    _outcome_item(item),
    _type(method),
    _details(std::move(smelted)),
    _group(std::move(group))
{
   switch (method) {
   case Smelting:
   case Blasting:
   case Smoking:
   case CampfireCooking: break;
   default: throw std::runtime_error("invalid method for heat treatment");
   }
}

Recipe::Recipe(ItemStack item, std::string group, Recipe::StoneCutting details) :
    _outcome_item(item),
    _type(RecipeType::StoneCutting),
    _details(std::move(details)),
    _group(std::move(group))
{
}

template<>
Recipe::StoneCutting Recipe::details() const
{
   if (_type != RecipeType::StoneCutting)
      throw std::runtime_error("invalid recipe type");

   return std::get<Recipe::StoneCutting>(_details);
}

}// namespace minecpp::game::item
