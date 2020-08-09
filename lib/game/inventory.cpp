#include "inventory.h"
#include <game/items/registry.h>
#include <nbt/parser.h>

namespace Game {

using NBT::TagId;

InventoryItem::InventoryItem(NBT::Reader &r) {
   r.read_compound([this](NBT::Reader &r, NBT::TagId tagid,
                          const std::string &name) {
     switch (tagid) {
     case TagId::Byte:
        if (name == "Count") {
           count = r.read_byte();
           return;
        }
        if (name == "Slot") {
           slot = r.read_byte();
        }
        break;
     case TagId::String:
        if (name == "id") {
           try {
              auto item_id = item_id_from_tag(r.read_str());
              id = item_by_id(item_id).tag();
           } catch (std::runtime_error &e) {
              id = "air";
           }
           return;
        }
        break;
     case TagId::Compound:
        if (name == "tag") {
           NBT::Parser p(r.raw_stream());
           tag = p.read_tag().content.as<NBT::CompoundContent>();
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
