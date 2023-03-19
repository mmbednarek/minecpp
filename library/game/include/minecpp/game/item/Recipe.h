#pragma once
#include "Item.h"
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace minecpp::game::item {

enum RecipeType
{
   CraftingShaped,
   CraftingShapeless,
   Smelting,
   Blasting,
   Smoking,
   CampfireCooking,
   StoneCutting,
   Special,
};

class Recipe
{
 public:
   struct CraftingShaped
   {
      int width, height;
      std::vector<StackVariants> ingredients;
   };

   struct CraftingShapeless
   {
      std::vector<StackVariants> ingredients;
   };

   struct HeatTreatment
   {
      StackVariants ingredient;
      float experience;
      int cooking_time;
   };

   struct StoneCutting
   {
      StackVariants ingredient;
   };

   struct Special
   {};

   Recipe(ItemStack item, RecipeType method);
   Recipe(ItemStack item, std::string group, CraftingShaped details);
   Recipe(ItemStack item, std::string group, CraftingShapeless details);
   Recipe(ItemStack item, std::string group, RecipeType method, HeatTreatment details);
   Recipe(ItemStack item, std::string group, StoneCutting details);

   [[nodiscard]] const ItemStack &outcome() const;
   [[nodiscard]] RecipeType type() const;

   template<typename T>
   T details() const
   {
      if constexpr (std::is_same<T, CraftingShaped>::value) {
         if (m_type == RecipeType::CraftingShaped) {
            return std::get<CraftingShaped>(m_details);
         }
      }
      if constexpr (std::is_same<T, CraftingShapeless>::value) {
         if (m_type == RecipeType::CraftingShapeless) {
            return std::get<CraftingShapeless>(m_details);
         }
      }
      if constexpr (std::is_same<T, HeatTreatment>::value) {
         switch (m_type) {
         case Smelting:
         case Blasting:
         case Smoking:
         case CampfireCooking: return std::get<HeatTreatment>(m_details);
         default: break;
         }
      }
      if constexpr (std::is_same<T, StoneCutting>::value) {
         if (m_type == RecipeType::StoneCutting) {
            return std::get<StoneCutting>(m_details);
         }
      }
      return T{};
   }

 private:
   typedef std::variant<CraftingShaped, CraftingShapeless, HeatTreatment, StoneCutting, Special> Details;

   ItemStack m_outcome_item;
   RecipeType m_type;
   Details m_details;
   std::string m_group;
};

}// namespace minecpp::game::item
