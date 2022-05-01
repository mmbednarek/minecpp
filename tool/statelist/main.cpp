#include <fmt/core.h>
#include <minecpp/nbt/repository/v1/repository.nbt.h>
#include <minecpp/nbt/parser.h>
#include <minecpp/nbt/writer.h>
#include <set>
#include <fstream>

auto main() -> int {
   namespace repo = minecpp::nbt::repository::v1;
   repo::Repository repository;
   std::set<std::string> tag_names;

   repository.enum_states.reserve(minecpp::game::block::g_enum_attribs.size());
   for (auto *att : minecpp::game::block::g_enum_attribs) {
      repo::EnumStateEntry entry;
      if (tag_names.contains(std::string(att->tag()))) {
         std::cerr << att->tag() << "appears more than one time";
         return EXIT_FAILURE;
      }
      tag_names.insert(std::string(att->tag()));
      entry.tag = att->tag();
      entry.state.name = att->name();
      for (int i = 0; i < att->num_states(); ++i) {
         entry.state.values.push_back(att->name_of(i));
      }
      repository.enum_states.push_back(entry);
   }

   repository.int_states.reserve(minecpp::game::block::g_int_attribs.size());
   for (auto *att : minecpp::game::block::g_int_attribs) {
      repo::IntStateEntry entry;
      if (tag_names.contains(std::string(att->tag()))) {
         std::cerr << att->tag() << "appears more than one time";
         return EXIT_FAILURE;
      }
      tag_names.insert(std::string(att->tag()));
      entry.tag = att->tag();
      entry.state.name = att->name();
      auto count = att->num_states();
      auto min = -att->index_from_int(0);
      entry.state.min_value = min;
      entry.state.max_value = min + count - 1;
      repository.int_states.push_back(entry);
   }

   repository.bool_states.reserve(minecpp::game::block::g_bool_attribs.size());
   for (auto *att : minecpp::game::block::g_bool_attribs) {
      repo::BoolStateEntry entry;
      if (tag_names.contains(std::string(att->tag()))) {
         std::cerr << att->tag() << "appears more than one time";
         return EXIT_FAILURE;
      }
      tag_names.insert(std::string(att->tag()));
      entry.tag = att->tag();
      entry.state.name = att->name();
      repository.bool_states.push_back(entry);
   }

   repository.blocks.reserve(minecpp::game::block::blocks.size());
   for (auto &block : minecpp::game::block::blocks) {
      repo::BlockEntry entry;
      entry.block.state_tags.reserve(block.attributes.size());

      entry.tag = fmt::format("minecraft:{}", block.tag());
      for (const auto &attrib : block.attributes) {
         entry.block.state_tags.emplace_back(attrib->tag());
      }
      repository.blocks.push_back(entry);
   }

   std::stringstream ss;
   repository.serialize(ss, "");
   ss.seekg(0, std::ios::beg);

   std::ofstream output("repository.bin");
   repository.serialize(output, "");
   output.close();

   minecpp::nbt::Parser parser(ss);
   auto tag = parser.read_tag();
   std::cout << tag.content.to_string() << '\n';
}
