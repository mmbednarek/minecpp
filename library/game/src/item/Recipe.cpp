#include <minecpp/game/item/Recipe.h>
#include <stdexcept>
#include <utility>

namespace minecpp::game::item {

const ItemStack &Recipe::outcome() const
{
   return m_outcome_item;
}

RecipeType Recipe::type() const
{
   return m_type;
}

Recipe::Recipe(ItemStack item, std::string group, Recipe::CraftingShaped details) :
    m_outcome_item(item),
    m_type(RecipeType::CraftingShaped),
    m_details(std::move(details)),
    m_group(std::move(group))
{
}

Recipe::Recipe(ItemStack item, std::string group, Recipe::CraftingShapeless details) :
    m_outcome_item(item),
    m_type(RecipeType::CraftingShapeless),
    m_details(std::move(details)),
    m_group(std::move(group))
{
}

Recipe::Recipe(ItemStack item, RecipeType method) :
    m_outcome_item(item),
    m_type(method),
    m_details(Recipe::Special{}),
    m_group("special")
{
}

Recipe::Recipe(ItemStack item, std::string group, RecipeType method, Recipe::HeatTreatment smelted) :
    m_outcome_item(item),
    m_type(method),
    m_details(std::move(smelted)),
    m_group(std::move(group))
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
    m_outcome_item(item),
    m_type(RecipeType::StoneCutting),
    m_details(std::move(details)),
    m_group(std::move(group))
{
}

template<>
Recipe::StoneCutting Recipe::details() const
{
   if (m_type != RecipeType::StoneCutting)
      throw std::runtime_error("invalid recipe type");

   return std::get<Recipe::StoneCutting>(m_details);
}

}// namespace minecpp::game::item
