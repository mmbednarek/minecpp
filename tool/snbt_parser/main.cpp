#include "lexer.h"
#include "parser.h"
#include <array>
#include <fstream>
#include <iostream>
#include <minecpp/nbt/parser.h>
#include <sstream>

std::array<std::string, 9> token_names{
        "Identifier",         "String", "Numeric", "Colon", "Comma", "LeftBrace", "RightBrace", "LeftSquareBracket",
        "RightSquareBracket",
};

extern std::string nbt;

int main()
{
   using namespace minecpp::tool::snbt_parser;

   StringReader reader(nbt);
   Lexer lexer(reader);
   auto tokens = lexer.lex();
   Parser parser(tokens);

   auto result = parser.read_content();
   if (!result.ok()) {
      std::cerr << result.msg();
      return 1;
   }

   auto content = result.unwrap();
   std::ofstream out("/home/ego/foo.bin");
   //   std::stringstream ss;
   content.serialize("", out);
   //
   //   minecpp::nbt::Parser nbt_parser(ss);
   //   auto content2 = nbt_parser.read_compound();

   return 0;
}

std::string nbt{R"(
{
  "minecraft:dimension_type": {
    type: "minecraft:dimension_type",
    value: [
      {
        element: {
          ambient_light: 0.0f,
          bed_works: 1b,
          coordinate_scale: 1.0d,
          effects: "minecraft:overworld",
          has_ceiling: 0b,
          has_raids: 1b,
          has_skylight: 1b,
          height: 384,
          infiniburn: "#minecraft:infiniburn_overworld",
          logical_height: 384,
          min_y: -64,
          natural: 1b,
          piglin_safe: 0b,
          respawn_anchor_works: 0b,
          ultrawarm: 0b
        },
        id: 0,
        name: "minecraft:overworld"
      },
      {
        element: {
          ambient_light: 0.0f,
          bed_works: 1b,
          coordinate_scale: 1.0d,
          effects: "minecraft:overworld",
          has_ceiling: 1b,
          has_raids: 1b,
          has_skylight: 1b,
          height: 384,
          infiniburn: "#minecraft:infiniburn_overworld",
          logical_height: 384,
          min_y: -64,
          natural: 1b,
          piglin_safe: 0b,
          respawn_anchor_works: 0b,
          ultrawarm: 0b
        },
        id: 1,
        name: "minecraft:overworld_caves"
      },
      {
        element: {
          ambient_light: 0.1f,
          bed_works: 0b,
          coordinate_scale: 8.0d,
          effects: "minecraft:the_nether",
          fixed_time: 18000L,
          has_ceiling: 1b,
          has_raids: 0b,
          has_skylight: 0b,
          height: 256,
          infiniburn: "#minecraft:infiniburn_nether",
          logical_height: 128,
          min_y: 0,
          natural: 0b,
          piglin_safe: 1b,
          respawn_anchor_works: 1b,
          ultrawarm: 1b
        },
        id: 2,
        name: "minecraft:the_nether"
      },
      {
        element: {
          ambient_light: 0.0f,
          bed_works: 0b,
          coordinate_scale: 1.0d,
          effects: "minecraft:the_end",
          fixed_time: 6000L,
          has_ceiling: 0b,
          has_raids: 1b,
          has_skylight: 0b,
          height: 256,
          infiniburn: "#minecraft:infiniburn_end",
          logical_height: 256,
          min_y: 0,
          natural: 0b,
          piglin_safe: 0b,
          respawn_anchor_works: 0b,
          ultrawarm: 0b
        },
        id: 3,
        name: "minecraft:the_end"
      }
    ]
  },
  "minecraft:worldgen/biome": {
    type: "minecraft:worldgen/biome",
    value: [
      {
        element: {
          category: "none",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 0.5f
        },
        id: 0,
        name: "minecraft:the_void"
      },
      {
        element: {
          category: "plains",
          downfall: 0.4f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7907327,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.8f
        },
        id: 1,
        name: "minecraft:plains"
      },
      {
        element: {
          category: "plains",
          downfall: 0.4f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7907327,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.8f
        },
        id: 2,
        name: "minecraft:sunflower_plains"
      },
      {
        element: {
          category: "icy",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8364543,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: 0.0f
        },
        id: 3,
        name: "minecraft:snowy_plains"
      },
      {
        element: {
          category: "icy",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8364543,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: 0.0f
        },
        id: 4,
        name: "minecraft:ice_spikes"
      },
      {
        element: {
          category: "desert",
          downfall: 0.0f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 5,
        name: "minecraft:desert"
      },
      {
        element: {
          category: "swamp",
          downfall: 0.9f,
          effects: {
            fog_color: 12638463,
            foliage_color: 6975545,
            grass_color_modifier: "swamp",
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7907327,
            water_color: 6388580,
            water_fog_color: 2302743
          },
          precipitation: "rain",
          temperature: 0.8f
        },
        id: 6,
        name: "minecraft:swamp"
      },
      {
        element: {
          category: "forest",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7972607,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.7f
        },
        id: 7,
        name: "minecraft:forest"
      },
      {
        element: {
          category: "forest",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7972607,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.7f
        },
        id: 8,
        name: "minecraft:flower_forest"
      },
      {
        element: {
          category: "forest",
          downfall: 0.6f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8037887,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.6f
        },
        id: 9,
        name: "minecraft:birch_forest"
      },
      {
        element: {
          category: "forest",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            grass_color_modifier: "dark_forest",
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7972607,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.7f
        },
        id: 10,
        name: "minecraft:dark_forest"
      },
      {
        element: {
          category: "forest",
          downfall: 0.6f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8037887,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.6f
        },
        id: 11,
        name: "minecraft:old_growth_birch_forest"
      },
      {
        element: {
          category: "taiga",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8168447,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.3f
        },
        id: 12,
        name: "minecraft:old_growth_pine_taiga"
      },
      {
        element: {
          category: "taiga",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8233983,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.25f
        },
        id: 13,
        name: "minecraft:old_growth_spruce_taiga"
      },
      {
        element: {
          category: "taiga",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8233983,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.25f
        },
        id: 14,
        name: "minecraft:taiga"
      },
      {
        element: {
          category: "taiga",
          downfall: 0.4f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8625919,
            water_color: 4020182,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: -0.5f
        },
        id: 15,
        name: "minecraft:snowy_taiga"
      },
      {
        element: {
          category: "savanna",
          downfall: 0.0f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 16,
        name: "minecraft:savanna"
      },
      {
        element: {
          category: "savanna",
          downfall: 0.0f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 17,
        name: "minecraft:savanna_plateau"
      },
      {
        element: {
          category: "extreme_hills",
          downfall: 0.3f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8233727,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.2f
        },
        id: 18,
        name: "minecraft:windswept_hills"
      },
      {
        element: {
          category: "extreme_hills",
          downfall: 0.3f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8233727,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.2f
        },
        id: 19,
        name: "minecraft:windswept_gravelly_hills"
      },
      {
        element: {
          category: "extreme_hills",
          downfall: 0.3f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8233727,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.2f
        },
        id: 20,
        name: "minecraft:windswept_forest"
      },
      {
        element: {
          category: "savanna",
          downfall: 0.0f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 21,
        name: "minecraft:windswept_savanna"
      },
      {
        element: {
          category: "jungle",
          downfall: 0.9f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7842047,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.95f
        },
        id: 22,
        name: "minecraft:jungle"
      },
      {
        element: {
          category: "jungle",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7842047,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.95f
        },
        id: 23,
        name: "minecraft:sparse_jungle"
      },
      {
        element: {
          category: "jungle",
          downfall: 0.9f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7842047,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.95f
        },
        id: 24,
        name: "minecraft:bamboo_jungle"
      },
      {
        element: {
          category: "mesa",
          downfall: 0.0f,
          effects: {
            fog_color: 12638463,
            foliage_color: 10387789,
            grass_color: 9470285,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 25,
        name: "minecraft:badlands"
      },
      {
        element: {
          category: "mesa",
          downfall: 0.0f,
          effects: {
            fog_color: 12638463,
            foliage_color: 10387789,
            grass_color: 9470285,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 26,
        name: "minecraft:eroded_badlands"
      },
      {
        element: {
          category: "mesa",
          downfall: 0.0f,
          effects: {
            fog_color: 12638463,
            foliage_color: 10387789,
            grass_color: 9470285,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 27,
        name: "minecraft:wooded_badlands"
      },
      {
        element: {
          category: "mountain",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.overworld.meadow"
            },
            sky_color: 8103167,
            water_color: 937679,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 28,
        name: "minecraft:meadow"
      },
      {
        element: {
          category: "forest",
          downfall: 0.8f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.overworld.grove"
            },
            sky_color: 8495359,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: -0.2f
        },
        id: 29,
        name: "minecraft:grove"
      },
      {
        element: {
          category: "mountain",
          downfall: 0.9f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.overworld.snowy_slopes"
            },
            sky_color: 8560639,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: -0.3f
        },
        id: 30,
        name: "minecraft:snowy_slopes"
      },
      {
        element: {
          category: "mountain",
          downfall: 0.9f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.overworld.frozen_peaks"
            },
            sky_color: 8756735,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: -0.7f
        },
        id: 31,
        name: "minecraft:frozen_peaks"
      },
      {
        element: {
          category: "mountain",
          downfall: 0.9f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.overworld.jagged_peaks"
            },
            sky_color: 8756735,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: -0.7f
        },
        id: 32,
        name: "minecraft:jagged_peaks"
      },
      {
        element: {
          category: "mountain",
          downfall: 0.3f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.overworld.stony_peaks"
            },
            sky_color: 7776511,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 1.0f
        },
        id: 33,
        name: "minecraft:stony_peaks"
      },
      {
        element: {
          category: "river",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 34,
        name: "minecraft:river"
      },
      {
        element: {
          category: "river",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8364543,
            water_color: 3750089,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: 0.0f
        },
        id: 35,
        name: "minecraft:frozen_river"
      },
      {
        element: {
          category: "beach",
          downfall: 0.4f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7907327,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.8f
        },
        id: 36,
        name: "minecraft:beach"
      },
      {
        element: {
          category: "beach",
          downfall: 0.3f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8364543,
            water_color: 4020182,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: 0.05f
        },
        id: 37,
        name: "minecraft:snowy_beach"
      },
      {
        element: {
          category: "beach",
          downfall: 0.3f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8233727,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.2f
        },
        id: 38,
        name: "minecraft:stony_shore"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4445678,
            water_fog_color: 270131
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 39,
        name: "minecraft:warm_ocean"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4566514,
            water_fog_color: 267827
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 40,
        name: "minecraft:lukewarm_ocean"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4566514,
            water_fog_color: 267827
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 41,
        name: "minecraft:deep_lukewarm_ocean"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 42,
        name: "minecraft:ocean"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 43,
        name: "minecraft:deep_ocean"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4020182,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 44,
        name: "minecraft:cold_ocean"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 4020182,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 45,
        name: "minecraft:deep_cold_ocean"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8364543,
            water_color: 3750089,
            water_fog_color: 329011
          },
          precipitation: "snow",
          temperature: 0.0f,
          temperature_modifier: "frozen"
        },
        id: 46,
        name: "minecraft:frozen_ocean"
      },
      {
        element: {
          category: "ocean",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 8103167,
            water_color: 3750089,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.5f,
          temperature_modifier: "frozen"
        },
        id: 47,
        name: "minecraft:deep_frozen_ocean"
      },
      {
        element: {
          category: "mushroom",
          downfall: 1.0f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 7842047,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.9f
        },
        id: 48,
        name: "minecraft:mushroom_fields"
      },
      {
        element: {
          category: "underground",
          downfall: 0.4f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.overworld.dripstone_caves"
            },
            sky_color: 7907327,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.8f
        },
        id: 49,
        name: "minecraft:dripstone_caves"
      },
      {
        element: {
          category: "underground",
          downfall: 0.5f,
          effects: {
            fog_color: 12638463,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.overworld.lush_caves"
            },
            sky_color: 8103167,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "rain",
          temperature: 0.5f
        },
        id: 50,
        name: "minecraft:lush_caves"
      },
      {
        element: {
          category: "nether",
          downfall: 0.0f,
          effects: {
            additions_sound: {
              sound: "minecraft:ambient.nether_wastes.additions",
              tick_chance: 0.0111d
            },
            ambient_sound: "minecraft:ambient.nether_wastes.loop",
            fog_color: 3344392,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.nether_wastes.mood",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.nether.nether_wastes"
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 51,
        name: "minecraft:nether_wastes"
      },
      {
        element: {
          category: "nether",
          downfall: 0.0f,
          effects: {
            additions_sound: {
              sound: "minecraft:ambient.warped_forest.additions",
              tick_chance: 0.0111d
            },
            ambient_sound: "minecraft:ambient.warped_forest.loop",
            fog_color: 1705242,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.warped_forest.mood",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.nether.warped_forest"
            },
            particle: {
              options: {
                type: "minecraft:warped_spore"
              },
              probability: 0.01428f
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 52,
        name: "minecraft:warped_forest"
      },
      {
        element: {
          category: "nether",
          downfall: 0.0f,
          effects: {
            additions_sound: {
              sound: "minecraft:ambient.crimson_forest.additions",
              tick_chance: 0.0111d
            },
            ambient_sound: "minecraft:ambient.crimson_forest.loop",
            fog_color: 3343107,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.crimson_forest.mood",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.nether.crimson_forest"
            },
            particle: {
              options: {
                type: "minecraft:crimson_spore"
              },
              probability: 0.025f
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 53,
        name: "minecraft:crimson_forest"
      },
      {
        element: {
          category: "nether",
          downfall: 0.0f,
          effects: {
            additions_sound: {
              sound: "minecraft:ambient.soul_sand_valley.additions",
              tick_chance: 0.0111d
            },
            ambient_sound: "minecraft:ambient.soul_sand_valley.loop",
            fog_color: 1787717,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.soul_sand_valley.mood",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.nether.soul_sand_valley"
            },
            particle: {
              options: {
                type: "minecraft:ash"
              },
              probability: 0.00625f
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 54,
        name: "minecraft:soul_sand_valley"
      },
      {
        element: {
          category: "nether",
          downfall: 0.0f,
          effects: {
            additions_sound: {
              sound: "minecraft:ambient.basalt_deltas.additions",
              tick_chance: 0.0111d
            },
            ambient_sound: "minecraft:ambient.basalt_deltas.loop",
            fog_color: 6840176,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.basalt_deltas.mood",
              tick_delay: 6000
            },
            music: {
              max_delay: 24000,
              min_delay: 12000,
              replace_current_music: 0b,
              sound: "minecraft:music.nether.basalt_deltas"
            },
            particle: {
              options: {
                type: "minecraft:white_ash"
              },
              probability: 0.118093334f
            },
            sky_color: 7254527,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 2.0f
        },
        id: 55,
        name: "minecraft:basalt_deltas"
      },
      {
        element: {
          category: "the_end",
          downfall: 0.5f,
          effects: {
            fog_color: 10518688,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 0,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 0.5f
        },
        id: 56,
        name: "minecraft:the_end"
      },
      {
        element: {
          category: "the_end",
          downfall: 0.5f,
          effects: {
            fog_color: 10518688,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 0,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 0.5f
        },
        id: 57,
        name: "minecraft:end_highlands"
      },
      {
        element: {
          category: "the_end",
          downfall: 0.5f,
          effects: {
            fog_color: 10518688,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 0,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 0.5f
        },
        id: 58,
        name: "minecraft:end_midlands"
      },
      {
        element: {
          category: "the_end",
          downfall: 0.5f,
          effects: {
            fog_color: 10518688,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 0,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 0.5f
        },
        id: 59,
        name: "minecraft:small_end_islands"
      },
      {
        element: {
          category: "the_end",
          downfall: 0.5f,
          effects: {
            fog_color: 10518688,
            mood_sound: {
              block_search_extent: 8,
              offset: 2.0d,
              sound: "minecraft:ambient.cave",
              tick_delay: 6000
            },
            sky_color: 0,
            water_color: 4159204,
            water_fog_color: 329011
          },
          precipitation: "none",
          temperature: 0.5f
        },
        id: 60,
        name: "minecraft:end_barrens"
      }
    ]
  }
}
)"};