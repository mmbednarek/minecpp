#pragma once
#include "game/items/item.h"
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
   template <typename T> T details() const = delete;
   template <>[[nodiscard]] CraftingShaped details() const;
   template <>[[nodiscard]] CraftingShapeless details() const;
   template <>[[nodiscard]] HeatTreatment details() const;
   template <>[[nodiscard]] StoneCutting details() const;

 private:
   typedef std::variant<CraftingShaped, CraftingShapeless, HeatTreatment,
                        StoneCutting, Special>
       Details;

   ItemStack _outcome_item;
   RecipeType _type;
   Details _details;
   std::string _group;
};

} // namespace Game
