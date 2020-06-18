#include "inventory.h"
#include <game/items/registry.h>
#include <nbt/parser.h>

namespace Game {

using NBT::TagID;

InventoryItem::InventoryItem(NBT::Reader &r) {
   r.read_compound([this](NBT::Reader &r, NBT::TagID tagid,
                          const std::string &name) {
     switch (tagid) {
     case TagID::Byte:
        if (name == "Count") {
           count = r.read_payload<NBT::Byte>();
           return;
        }
        if (name == "Slot") {
           slot = r.read_payload<NBT::Byte>();
        }
        break;
     case TagID::String:
        if (name == "id") {
           try {
              auto item_id = item_id_from_tag(r.read_payload<NBT::String>());
              id = item_by_id(item_id).tag();
           } catch (std::runtime_error &e) {
              id = "air";
           }
           return;
        }
        break;
     case TagID::Compound:
        if (name == "tag") {
           NBT::Parser p(r.raw_stream());
           tag = p.read_compound();
           return;
        }
        break;
     default:
        break;
     }
     r.skip_payload(tagid);
   });
}

}
