#pragma once
#include "item.h"
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace Game {

enum RecipeType {
   CraftingShaped,
   CraftingShapeless,
   Smelting,
   Blasting,
   Smoking,
   CampfireCooking,
   StoneCutting,
   Special,
};

class Recipe {
 public:
   struct CraftingShaped {
      int width, height;
      std::vector<StackVariants> ingredients;
   };

   struct CraftingShapeless {
      std::vector<StackVariants> ingredients;
   };

   struct HeatTreatment {
      StackVariants ingredient;
      float experience;
      int cooking_time;
   };

   struct StoneCutting {
      StackVariants ingredient;
   };

   struct Special {};

   Recipe(ItemStack item, RecipeType method);
   Recipe(ItemStack item, std::string group, CraftingShaped details);
   Recipe(ItemStack item, std::string group, CraftingShapeless details);
   Recipe(ItemStack item, std::string group, RecipeType method,
          HeatTreatment details);
   Recipe(ItemStack item, std::string group, StoneCutting details);

   [[nodiscard]] const ItemStack &outcome() const;
   [[nodiscard]] RecipeType type() const;

   template<typename T>
   T details() const {
      if constexpr (std::is_same<T, CraftingShaped>::value) {
         if (_type == RecipeType::CraftingShaped) {
            return std::get<CraftingShaped>(_details);
         }
      }
      if constexpr (std::is_same<T, CraftingShapeless>::value) {
         if (_type == RecipeType::CraftingShapeless) {
            return std::get<CraftingShapeless>(_details);
         }
      }
      if constexpr (std::is_same<T, HeatTreatment>::value) {
          switch(_type) {
          case Smelting:
          case Blasting:
          case Smoking:
          case CampfireCooking:
             return std::get<HeatTreatment>(_details);
          default: break;
          }
      }
      if constexpr (std::is_same<T, StoneCutting>::value) {
         if (_type == RecipeType::StoneCutting) {
            return std::get<StoneCutting>(_details);
         }
      }
   }
 private:
   typedef std::variant<CraftingShaped, CraftingShapeless, HeatTreatment,
                        StoneCutting, Special>
           Details;

   ItemStack _outcome_item;
   RecipeType _type;
   Details _details;
   std::string _group;
};

}// namespace Game
