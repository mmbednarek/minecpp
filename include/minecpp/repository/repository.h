#ifndef MINECPP_REPOSITORY_H
#define MINECPP_REPOSITORY_H
#include <mb/int.h>
#include <mb/result.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace minecpp::repository {

using Id = mb::size;

template<typename TResource>
struct Description
{
   TResource resource;
   std::string tag;
   Id id;
};

template<typename TResource>
class Repository
{
   std::vector<Description<TResource>> m_description;
   std::unordered_map<std::string, Id> m_tags;

 public:
   [[nodiscard]] mb::result<Id> find_id_by_tag(const std::string &tag)
   {
      if (m_tags.contains(std::string(tag))) {
         return static_cast<Id>(m_tags.at(tag));
      }
      return mb::error("not found");
   }

   [[nodiscard]] mb::result<const TResource &> find_block_by_tag(std::string_view tag)
   {
      auto id = MB_TRY(find_id_by_tag(std::string(tag)));
      return m_description[id].resource;
   }

   [[nodiscard]] mb::result<const TResource &> get_by_id(Id id)
   {
      if (id >= m_description.size())
         return mb::error("invalid id");
      return m_description[id].resource;
   }

   void register_resource(const std::string &tag, const TResource &res)
   {
      auto index = m_description.size();
      m_description.push_back(Description<TResource>{res, tag.data(), index});
      m_tags[tag] = index;
   }
};

mb::emptyres load_repository_from_file(std::string_view filename);

}// namespace minecpp::repository

#endif//MINECPP_REPOSITORY_H
