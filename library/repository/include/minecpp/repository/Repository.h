#ifndef MINECPP_REPOSITORY_H
#define MINECPP_REPOSITORY_H
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/game/Game.h>
#include <minecpp/nbt/repository/v1/Codec.nbt.h>
#include <string>
#include <unordered_map>
#include <vector>

#define BLOCK_ID(name) (::minecpp::repository::BlockIds::the().name)

namespace minecpp::repository {

template<typename TResource, typename TId>
struct Description
{
   TResource resource;
   std::string tag;
   TId id;
};

template<typename TResource, typename TId = int>
class Repository
{
   std::vector<Description<TResource, TId>> m_description;
   std::unordered_map<std::string, TId> m_tags;

 public:
   using index_type = TId;

   [[nodiscard]] mb::result<index_type> find_id_by_tag(const std::string &tag)
   {
      if (m_tags.contains(std::string(tag))) {
         return static_cast<index_type>(m_tags.at(tag));
      }
      return mb::error("not found");
   }

   [[nodiscard]] mb::result<const TResource &> find_by_tag(std::string_view tag)
   {
      auto id = MB_TRY(find_id_by_tag(std::string(tag)));
      return m_description[id].resource;
   }

   [[nodiscard]] mb::result<const TResource &> get_by_id(index_type id) const
   {
      using size_type = typename decltype(m_description)::size_type;

      auto size_index = static_cast<size_type>(id);

      if (size_index >= m_description.size())
         return mb::error("invalid id");

      return m_description.at(size_index).resource;
   }

   void register_resource(const std::string &tag, const TResource &res)
   {
      auto index = static_cast<index_type>(m_description.size());
      m_description.push_back(Description<TResource, TId>{res, tag.data(), index});
      m_tags[tag] = index;
   }
};

struct BlockIds
{
   game::BlockId Air;
   game::BlockId Water;
   game::BlockId Torch;
   game::BlockId WallTorch;
   game::BlockId OakDoor;

   void init();
   [[nodiscard]] static BlockIds &the();

 private:
   bool m_initialised = false;
};

mb::result<nbt::repository::v1::Registry> load_network_registry_from_file(std::string_view filename);
mb::emptyres load_repository_from_file(std::string_view filename);

}// namespace minecpp::repository

#endif//MINECPP_REPOSITORY_H
