#pragma once
#include "bamboo.h"
#include "bed.h"
#include "chest.h"
#include "comparator.h"
#include "door.h"
#include "note_block.h"
#include "piston.h"
#include "slab.h"
#include "stairs.h"
#include "structure.h"
#include <array>
#include <boost/fusion/container/vector.hpp>
#include <minecpp/game/direction.h>
#include <string_view>
#include <type_traits>

namespace minecpp::game::block {

class Attribute {
   std::string_view m_tag;
   std::string_view m_prop_name;

 public:
   explicit Attribute(std::string_view tag, std::string_view name) : m_tag(tag), m_prop_name(name) {}
   [[nodiscard]] constexpr std::string_view name() const { return m_prop_name; }
   [[nodiscard]] constexpr std::string_view tag() const { return m_tag; }

   virtual int num_states() const = 0;

   virtual int index_from_int(int i) const = 0;
   virtual int index_from_str(const std::string &s) const = 0;
   [[nodiscard]] virtual std::string name_of(int i) const = 0;

   int id{};
};

class BoolAttribute;

extern std::vector<BoolAttribute *> g_bool_attribs;
extern std::vector<Attribute *> g_int_attribs;
extern std::vector<Attribute *> g_enum_attribs;

template <int Min, int Max> class IntAttribute : public Attribute {
 public:
   explicit IntAttribute(std::string_view tag, std::string_view name) : Attribute(tag, name) {
      g_int_attribs.push_back(this);
   }

   [[nodiscard]] int num_states() const override { return Max + 1 - Min; }
   [[nodiscard]] int value(int state) const { return Min + state; };
   [[nodiscard]] int index_from_int(int i) const override { return i - Min; }
   [[nodiscard]] int index_from_str(const std::string &s) const override {
      return std::stoi(s) - Min;
   }
   [[nodiscard]] std::string name_of(int i) const override {
      return std::to_string(i + Min);
   }
};

class BoolAttribute : public Attribute {
 public:
   explicit BoolAttribute(std::string_view tag, std::string_view name);

   [[nodiscard]] int num_states() const override;
   [[nodiscard]] bool value(int state) const;
   [[nodiscard]] int index_from_int(int i) const override { return i ? 0 : 1; }
   [[nodiscard]] int index_from_str(const std::string &s) const override {
      return s == "true" ? 0 : 1;
   }
   [[nodiscard]] std::string name_of(int i) const override {
      return i == 1 ? "false" : "true";
   }
};

template <Enumerable E> class EnumAttribute : public Attribute {
 public:
   explicit EnumAttribute(std::string_view tag, std::string_view name) : Attribute(tag, name) {
      g_enum_attribs.push_back(this);
   }

   int num_states() const override { return E::num(); }

   E value(int state) const { return E(state); };
   int index_from_int(int i) const override { return i; }
   [[nodiscard]] int index_from_str(const std::string &s) const override {
      return E(s.c_str()).index();
   }
   [[nodiscard]] std::string name_of(int i) const override {
      return std::string(E(i).str());
   }
};

template <Enumerable E, uint32_t... Indexes>
class EnumPartAttribute : public Attribute {
 public:
   explicit EnumPartAttribute(std::string_view tag, std::string_view name) : Attribute(tag, name) {
      g_enum_attribs.push_back(this);
   }

   [[nodiscard]] int num_states() const override { return sizeof...(Indexes); }

   [[nodiscard]] E value(int state) const {
      return E(std::array<uint32_t, sizeof...(Indexes)>{Indexes...}[state]);
   };

   [[nodiscard]] int index_from_int(int i) const override { return i; }

   [[nodiscard]] int index_from_str(const std::string &s) const override {
      auto index = E(s.c_str()).index();
      auto arr = std::array<uint32_t, sizeof...(Indexes)>{Indexes...};
      int result = 0;
      for (const auto &i : arr) {
         if (index == i) {
            return result;
         }
         ++result;
      }
      return result;
   }
   [[nodiscard]] std::string name_of(int i) const override {
      auto arr = std::array<uint32_t, sizeof...(Indexes)>{Indexes...};
      return std::string(E(arr[i]).str());
   }
};

namespace Attrib {

const BoolAttribute Attached("attached", "attached");
const BoolAttribute Bottom("bottom", "bottom");
const BoolAttribute Conditional("conditional", "conditional");
const BoolAttribute Disarmed("disarmed", "disarmed");
const BoolAttribute Drag("drag", "drag");
const BoolAttribute Enabled("enabled", "enabled");
const BoolAttribute Extended("extended", "extended");
const BoolAttribute Eye("eye", "eye");
const BoolAttribute Falling("falling", "falling");
const BoolAttribute Hanging("hanging", "hanging");
const BoolAttribute HasBottle0("has_bottle_0", "has_bottle_0");
const BoolAttribute HasBottle1("has_bottle_1", "has_bottle_1");
const BoolAttribute HasBottle2("has_bottle_2", "has_bottle_2");
const BoolAttribute HasRecord("has_record", "has_record");
const BoolAttribute HasBook("has_book", "has_book");
const BoolAttribute Inverted("inverted", "inverted");
const BoolAttribute InWall("in_wall", "in_wall");
const BoolAttribute Lit("lit", "lit");
const BoolAttribute Locked("locked", "locked");
const BoolAttribute Occupied("occupied", "occupied");
const BoolAttribute Open("open", "open");
const BoolAttribute Persistent("persistent", "persistent");
const BoolAttribute Powered("powered", "powered");
const BoolAttribute Short("short", "short");
const BoolAttribute SignalFire("signal_fire", "signal_fire");
const BoolAttribute Snowy("snowy", "snowy");
const BoolAttribute Triggered("triggered", "triggered");
const BoolAttribute Unstable("unstable", "unstable");
const BoolAttribute Waterlogged("waterlogged", "waterlogged");
const EnumPartAttribute<Axis, Axis::index_of<ENU("x")>(),
                        Axis::index_of<ENU("z")>()>
    HorizontalAxis("axis0", "axis");
const EnumAttribute<Axis> Axis("axis1", "axis");
const BoolAttribute Up("up", "up");
const BoolAttribute Down("down", "down");
const BoolAttribute North("north", "north");
const BoolAttribute East("east", "east");
const BoolAttribute South("south", "south");
const BoolAttribute West("west", "west");

const EnumAttribute<WallHeight> WallNorth("wall_north", "north");
const EnumAttribute<WallHeight> WallEast("wall_east", "east");
const EnumAttribute<WallHeight> WallSouth("wall_south", "south");
const EnumAttribute<WallHeight> WallWest("wall_west", "west");

const EnumAttribute<Direction> Facing("facing0", "facing");

const EnumPartAttribute<
    Direction, Direction::index_of<ENU("down")>(),
    Direction::index_of<ENU("north")>(), Direction::index_of<ENU("south")>(),
    Direction::index_of<ENU("west")>(), Direction::index_of<ENU("east")>()>
    FacingExceptUp("facing1", "facing");

const EnumPartAttribute<Direction, Direction::index_of<ENU("north")>(),
                        Direction::index_of<ENU("south")>(),
                        Direction::index_of<ENU("west")>(),
                        Direction::index_of<ENU("east")>()>
    HorizontalFacing("facing2", "facing");

const EnumAttribute<Face> Face("face", "face");
const EnumAttribute<BellAttachment> BellAttachment("attachment", "attachment");

const EnumAttribute<RedstoneSide> RedstoneEast("redstone_east", "east");
const EnumAttribute<RedstoneSide> RedstoneNorth("redstone_north", "north");
const EnumAttribute<RedstoneSide> RedstoneSouth("redstone_south", "south");
const EnumAttribute<RedstoneSide> RedstoneWest("redstone_west", "west");

const EnumAttribute<DoubleBlockHalf> DoubleBlockHalf("half0", "half");
const EnumAttribute<Half> Half("half1", "half");

const EnumPartAttribute<RailShape, RailShape::index_of<ENU("north_south")>(),
                        RailShape::index_of<ENU("east_west")>(),
                        RailShape::index_of<ENU("ascending_east")>(),
                        RailShape::index_of<ENU("ascending_west")>(),
                        RailShape::index_of<ENU("ascending_north")>(),
                        RailShape::index_of<ENU("ascending_south")>()>
    RailShapeStraith("shape0", "shape");

const EnumAttribute<RailShape> RailShape("shape1", "shape");

const IntAttribute<0, 1> Age_0_1("age0_1", "age");
const IntAttribute<0, 2> Age_0_2("age0_2", "age");
const IntAttribute<0, 3> Age_0_3("age0_3", "age");
const IntAttribute<0, 5> Age_0_5("age0_5", "age");
const IntAttribute<0, 7> Age_0_7("age0_7", "age");
const IntAttribute<0, 15> Age_0_15("age0_15", "age");
const IntAttribute<0, 25> Age_0_25("age0_25", "age");
const IntAttribute<0, 6> Bites_0_6("bites", "bites");
const IntAttribute<1, 4> Delay_1_4("delay", "delay");
const IntAttribute<0, 7> Distance_0_7("distance0_7", "distance");
const IntAttribute<1, 7> Distance_1_7("distance1_7", "distance");
const IntAttribute<1, 4> Eggs_1_4("eggs", "eggs");
const IntAttribute<0, 2> Hatch_0_2("hatch", "hatch");
const IntAttribute<1, 8> Layers_1_8("layers", "layers");
const IntAttribute<0, 3> Level_0_3("level0_3", "level");
const IntAttribute<0, 8> Level_0_8("level0_8", "level");
const IntAttribute<1, 8> Level_1_8("level1_8", "level");
const IntAttribute<0, 5> HoneyLevel_0_5("honey_level", "honey_level");
const IntAttribute<0, 15> Level_0_15("level0_15", "level");
const IntAttribute<0, 7> Moisture_0_7("moisture", "moisture");
const IntAttribute<0, 24> Note_0_24("note", "note");
const IntAttribute<1, 4> Pickles_1_4("pickles", "pickles");
const IntAttribute<0, 15> Power_0_15("power", "power");
const IntAttribute<0, 1> Stage_0_1("stage", "stage");
const IntAttribute<0, 15> Rotation_0_15("rotation", "rotation");
const IntAttribute<0, 4> Charges("charges", "charges");

const EnumAttribute<BedPart> BedPart("part", "part");
const EnumAttribute<ChestType> ChestType("chest_type", "type");
const EnumAttribute<ComparatorMode> ComparatorMode("mode0", "mode");
const EnumAttribute<DoorHinge> DoorHinge("hinge", "hinge");
const EnumAttribute<NoteBlockInstrument> NoteBlockInstrument("instrument", "instrument");
const EnumAttribute<PistonType> PistonType("piston_type", "type");
const EnumAttribute<SlabType> SlabType("slab_type", "type");
const EnumAttribute<StairsShape> StairsShape("shape2", "shape");
const EnumAttribute<StructureMode> StructureMode("mode1", "mode");
const EnumAttribute<BambooLeaves> BambooLeaves("leaves", "leaves");
const EnumAttribute<JigsawOrientation> JigsawOrientation("orientation", "orientation");

} // namespace Attrib

} // namespace minecpp::game::block