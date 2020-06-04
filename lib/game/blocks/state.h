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

class Property {
   std::string_view prop_name;

 public:
   explicit Property(std::string_view name) : prop_name(name) {}
   [[nodiscard]] std::string_view name() { return prop_name; }

   virtual int num_states() const = 0;

   int id{};
};

class State {
   std::vector<Property *> properties{};

 public:
   template <typename... P> explicit State(P... props) : properties{props...} {}
   State() = default;
};

template <int Min, int Max> class IntProperty : public Property {
 public:
   explicit IntProperty(std::string_view name) : Property(name) {}

   int num_states() const override { return Max - Min; }
   int value(int state) const { return Min + state; };
};

class BoolProperty : public Property {
 public:
   explicit BoolProperty(std::string_view name);

   int num_states() const override;
   bool value(int state) const;
};

template <Enumerable E> class EnumProperty : public Property {
 public:
   explicit EnumProperty(std::string_view name) : Property(name) {}

   int num_states() const override { return E::num(); }

   E value(int state) const { return E(state); };
};

template <Enumerable E, uint32_t... Indexes>
class EnumPartProperty : public Property {
 public:
   explicit EnumPartProperty(std::string_view name) : Property(name) {}

   [[nodiscard]] int num_states() const override { return sizeof...(Indexes); }

   E value(int state) const {
      return E(std::array<uint32_t, sizeof...(Indexes)>{Indexes...}[state]);
   };
};

namespace Prop {

const BoolProperty Attached("attached");
const BoolProperty Bottom("bottom");
const BoolProperty Conditional("conditional");
const BoolProperty Disarmed("disarmed");
const BoolProperty Drag("drag");
const BoolProperty Enabled("enabled");
const BoolProperty Extended("extended");
const BoolProperty Eye("eye");
const BoolProperty Falling("falling");
const BoolProperty Hanging("hanging");
const BoolProperty HasBottle0("has_bottle_0");
const BoolProperty HasBottle1("has_bottle_1");
const BoolProperty HasBottle2("has_bottle_2");
const BoolProperty HasRecord("has_record");
const BoolProperty HasBook("has_book");
const BoolProperty Inverted("inverted");
const BoolProperty InWall("in_wall");
const BoolProperty Lit("lit");
const BoolProperty Locked("locked");
const BoolProperty Occupied("occupied");
const BoolProperty Open("open");
const BoolProperty Persistent("persistent");
const BoolProperty Powered("powered");
const BoolProperty Short("short");
const BoolProperty SignalFire("signal_fire");
const BoolProperty Snowy("snowy");
const BoolProperty Triggered("triggered");
const BoolProperty Unstable("unstable");
const BoolProperty Waterlogged("waterlogged");
const EnumPartProperty<Axis, Axis::index_of<ENU("X")>(), Axis::index_of<ENU("Y")>()>
    HorizontalAxis("axis");
const BoolProperty Up("up");
const BoolProperty Down("down");
const BoolProperty North("north");
const BoolProperty East("east");
const BoolProperty South("south");
const BoolProperty West("west");

const EnumProperty<Direction> Facing("facing");

const EnumPartProperty<
    Direction, Direction::index_of<ENU("down")>(),
    Direction::index_of<ENU("north")>(), Direction::index_of<ENU("south")>(),
    Direction::index_of<ENU("west")>(), Direction::index_of<ENU("east")>()>
    FacingExceptUp("facing");

const EnumPartProperty<Direction, Direction::index_of<ENU("north")>(),
                 Direction::index_of<ENU("south")>(),
                 Direction::index_of<ENU("west")>(),
                 Direction::index_of<ENU("east")>()>
    HorizontalFacing("facing");

const EnumProperty<Face> Face("face");
const EnumProperty<BellAttachment> BellAttachment("attachment");

const EnumProperty<RedstoneSide> RedstoneEast("east");
const EnumProperty<RedstoneSide> RedstoneNorth("north");
const EnumProperty<RedstoneSide> RedstoneSouth("south");
const EnumProperty<RedstoneSide> RedstoneWest("west");

const EnumProperty<DoubleBlockHalf> DoubleBlockHalf("half");
const EnumProperty<Half> Half("half");

const EnumPartProperty<RailShape, RailShape::index_of<ENU("north_south")>(),
                 RailShape::index_of<ENU("east_west")>(),
                 RailShape::index_of<ENU("ascending_east")>(),
                 RailShape::index_of<ENU("ascending_west")>(),
                 RailShape::index_of<ENU("ascending_north")>(),
                 RailShape::index_of<ENU("ascending_south")>()>
    RailShapeStraith("shape");

const EnumProperty<RailShape> RailShape("shape");

const IntProperty<0, 1> Age_0_1("age");
const IntProperty<0, 2> Age_0_2("age");
const IntProperty<0, 3> Age_0_3("age");
const IntProperty<0, 5> Age_0_5("age");
const IntProperty<0, 7> Age_0_7("age");
const IntProperty<0, 15> Age_0_15("age");
const IntProperty<0, 25> Age_0_25("age");
const IntProperty<0, 6> Bites_0_6("bites");
const IntProperty<1, 4> Delay_1_4("delay");
const IntProperty<1, 7> Distance_1_7("distance");
const IntProperty<1, 4> Eggs_1_4("eggs");
const IntProperty<0, 2> Hatch_0_2("hatch");
const IntProperty<1, 8> Layers_1_8("layers");
const IntProperty<0, 3> Level_0_3("level");
const IntProperty<0, 8> Level_0_8("level");
const IntProperty<1, 8> Level_1_8("level");
const IntProperty<0, 5> HoneyLevel_0_5("honey_level");
const IntProperty<0, 15> Level_0_15("level");
const IntProperty<0, 7> Moisture_0_7("moisture");
const IntProperty<0, 24> Note_0_24("note");
const IntProperty<1, 4> Pickles_1_4("pickles");
const IntProperty<0, 15> Power_0_15("power");
const IntProperty<0, 1> Stage_0_1("stage");
const IntProperty<0, 7> Distance_0_7("distance");
const IntProperty<0, 15> Rotation_0_15("rotation");

const EnumProperty<BedPart> BedPart("part");
const EnumProperty<ChestType> ChestType("type");
const EnumProperty<ComparatorMode> ComparatorMode("mode");
const EnumProperty<DoorHinge> DoorHinge("hinge");
const EnumProperty<NoteBlockInstrument> NoteBlockInstrument("instrument");
const EnumProperty<PistonType> PistonType("type");
const EnumProperty<SlabType> SlabType("type");
const EnumProperty<StairsShape> StairsShape("shape");
const EnumProperty<StructureMode> StructureMode("mode");
const EnumProperty<BambooLeaves> BambooLeaves("leaves");

} // namespace Prop

} // namespace Game::Block