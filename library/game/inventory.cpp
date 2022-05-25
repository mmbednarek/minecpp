#include <minecpp/game/inventory.h>
#include <minecpp/game/item/registry.h>
#include <minecpp/nbt/parser.h>

namespace minecpp::game {

using nbt::TagId;

InventoryItem::InventoryItem(nbt::Reader &r)
{
   r.read_compound([this](nbt::Reader &r, nbt::TagId tagid, const std::string &name) {
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
               auto item_id = item::item_id_from_tag(r.read_str());
               id           = item::item_by_id(item_id).tag();
            } catch (std::runtime_error &e) {
               id = "air";
            }
            return;
         }
         break;
      case TagId::Compound:
         if (name == "tag") {
            nbt::Parser p(r.raw_stream());
            tag = p.read_tag().content.as<nbt::CompoundContent>();
            return;
         }
         break;
      default: break;
      }
      r.skip_payload(tagid);
   });
}

}// namespace minecpp::game
