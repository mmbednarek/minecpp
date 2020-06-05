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
#include <game/direction.h>
#include <string_view>
#include <type_traits>

namespace Game::Block {

class Attribute {
   std::string_view prop_name;

 public:
   explicit Attribute(std::string_view name) : prop_name(name) {}
   [[nodiscard]] std::string_view name() { return prop_name; }

   virtual int num_states() const = 0;

   int id{};
};

class State {
   std::vector<Attribute *> properties{};

 public:
   template <typename... P> explicit State(P... props) : properties{props...} {}
   State() = default;
};

template <int Min, int Max> class IntAttribute : public Attribute {
 public:
   explicit IntAttribute(std::string_view name) : Attribute(name) {}

   int num_states() const override { return Max - Min; }
   int value(int state) const { return Min + state; };
};

class BoolAttribute : public Attribute {
 public:
   explicit BoolAttribute(std::string_view name);

   int num_states() const override;
   bool value(int state) const;
};

template <Enumerable E> class EnumAttribute : public Attribute {
 public:
   explicit EnumAttribute(std::string_view name) : Attribute(name) {}

   int num_states() const override { return E::num(); }

   E value(int state) const { return E(state); };
};

template <Enumerable E, uint32_t... Indexes>
class EnumPartAttribute : public Attribute {
 public:
   explicit EnumPartAttribute(std::string_view name) : Attribute(name) {}

   [[nodiscard]] int num_states() const override { return sizeof...(Indexes); }

   E value(int state) const {
      return E(std::array<uint32_t, sizeof...(Indexes)>{Indexes...}[state]);
   };
};

namespace Attrib {

const BoolAttribute Attached("attached");
const BoolAttribute Bottom("bottom");
const BoolAttribute Conditional("conditional");
const BoolAttribute Disarmed("disarmed");
const BoolAttribute Drag("drag");
const BoolAttribute Enabled("enabled");
const BoolAttribute Extended("extended");
const BoolAttribute Eye("eye");
const BoolAttribute Falling("falling");
const BoolAttribute Hanging("hanging");
const BoolAttribute HasBottle0("has_bottle_0");
const BoolAttribute HasBottle1("has_bottle_1");
const BoolAttribute HasBottle2("has_bottle_2");
const BoolAttribute HasRecord("has_record");
const BoolAttribute HasBook("has_book");
const BoolAttribute Inverted("inverted");
const BoolAttribute InWall("in_wall");
const BoolAttribute Lit("lit");
const BoolAttribute Locked("locked");
const BoolAttribute Occupied("occupied");
const BoolAttribute Open("open");
const BoolAttribute Persistent("persistent");
const BoolAttribute Powered("powered");
const BoolAttribute Short("short");
const BoolAttribute SignalFire("signal_fire");
const BoolAttribute Snowy("snowy");
const BoolAttribute Triggered("triggered");
const BoolAttribute Unstable("unstable");
const BoolAttribute Waterlogged("waterlogged");
const EnumPartAttribute<Axis, Axis::index_of<ENU("X")>(), Axis::index_of<ENU("Y")>()>
    HorizontalAxis("axis");
const BoolAttribute Up("up");
const BoolAttribute Down("down");
const BoolAttribute North("north");
const BoolAttribute East("east");
const BoolAttribute South("south");
const BoolAttribute West("west");

const EnumAttribute<Direction> Facing("facing");

const EnumPartAttribute<
    Direction, Direction::index_of<ENU("down")>(),
    Direction::index_of<ENU("north")>(), Direction::index_of<ENU("south")>(),
    Direction::index_of<ENU("west")>(), Direction::index_of<ENU("east")>()>
    FacingExceptUp("facing");

const EnumPartAttribute<Direction, Direction::index_of<ENU("north")>(),
                 Direction::index_of<ENU("south")>(),
                 Direction::index_of<ENU("west")>(),
                 Direction::index_of<ENU("east")>()>
    HorizontalFacing("facing");

const EnumAttribute<Face> Face("face");
const EnumAttribute<BellAttachment> BellAttachment("attachment");

const EnumAttribute<RedstoneSide> RedstoneEast("east");
const EnumAttribute<RedstoneSide> RedstoneNorth("north");
const EnumAttribute<RedstoneSide> RedstoneSouth("south");
const EnumAttribute<RedstoneSide> RedstoneWest("west");

const EnumAttribute<DoubleBlockHalf> DoubleBlockHalf("half");
const EnumAttribute<Half> Half("half");

const EnumPartAttribute<RailShape, RailShape::index_of<ENU("north_south")>(),
                 RailShape::index_of<ENU("east_west")>(),
                 RailShape::index_of<ENU("ascending_east")>(),
                 RailShape::index_of<ENU("ascending_west")>(),
                 RailShape::index_of<ENU("ascending_north")>(),
                 RailShape::index_of<ENU("ascending_south")>()>
    RailShapeStraith("shape");

const EnumAttribute<RailShape> RailShape("shape");

const IntAttribute<0, 1> Age_0_1("age");
const IntAttribute<0, 2> Age_0_2("age");
const IntAttribute<0, 3> Age_0_3("age");
const IntAttribute<0, 5> Age_0_5("age");
const IntAttribute<0, 7> Age_0_7("age");
const IntAttribute<0, 15> Age_0_15("age");
const IntAttribute<0, 25> Age_0_25("age");
const IntAttribute<0, 6> Bites_0_6("bites");
const IntAttribute<1, 4> Delay_1_4("delay");
const IntAttribute<1, 7> Distance_1_7("distance");
const IntAttribute<1, 4> Eggs_1_4("eggs");
const IntAttribute<0, 2> Hatch_0_2("hatch");
const IntAttribute<1, 8> Layers_1_8("layers");
const IntAttribute<0, 3> Level_0_3("level");
const IntAttribute<0, 8> Level_0_8("level");
const IntAttribute<1, 8> Level_1_8("level");
const IntAttribute<0, 5> HoneyLevel_0_5("honey_level");
const IntAttribute<0, 15> Level_0_15("level");
const IntAttribute<0, 7> Moisture_0_7("moisture");
const IntAttribute<0, 24> Note_0_24("note");
const IntAttribute<1, 4> Pickles_1_4("pickles");
const IntAttribute<0, 15> Power_0_15("power");
const IntAttribute<0, 1> Stage_0_1("stage");
const IntAttribute<0, 7> Distance_0_7("distance");
const IntAttribute<0, 15> Rotation_0_15("rotation");

const EnumAttribute<BedPart> BedPart("part");
const EnumAttribute<ChestType> ChestType("type");
const EnumAttribute<ComparatorMode> ComparatorMode("mode");
const EnumAttribute<DoorHinge> DoorHinge("hinge");
const EnumAttribute<NoteBlockInstrument> NoteBlockInstrument("instrument");
const EnumAttribute<PistonType> PistonType("type");
const EnumAttribute<SlabType> SlabType("type");
const EnumAttribute<StairsShape> StairsShape("shape");
const EnumAttribute<StructureMode> StructureMode("mode");
const EnumAttribute<BambooLeaves> BambooLeaves("leaves");

} // namespace Prop

} // namespace Game::Block