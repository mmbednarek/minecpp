#pragma once

#include "minecpp/nbt/trace/Trace.schema.h"
#include "minecpp/nbt/Writer.h"
#include "minecpp/util/Context.h"

#include <concepts>
#include <cstdint>
#include <fstream>
#include <functional>
#include <mutex>
#include <ostream>
#include <string_view>
#include <utility>

namespace minecpp::debug {

template<typename TObject>
concept NbtObject = requires(TObject object, std::ostream &stream, std::string_view name) {
   {
      object.serialize(stream, name)
   };
   {
      std::decay_t<TObject>::object_name
   } -> std::convertible_to<const char *>;
};

template<typename TAllocator = std::allocator<std::uint8_t>>
class TraceObject
{
 public:
   template<NbtObject TNbtStruct>
   explicit TraceObject(std::string_view source_file, int line, util::ContextId context_id,
                        TNbtStruct &&object, const TAllocator &allocator = TAllocator()) :
       m_allocator{allocator},
       m_object{m_allocator.allocate(sizeof(TNbtStruct))},
       m_size{sizeof(TNbtStruct)},
       m_name(std::decay_t<TNbtStruct>::object_name),
       m_time(std::chrono::system_clock::now()),
       m_source_file{source_file},
       m_line{line},
       m_context_id{context_id},
       m_serialize_func([](const void *object, std::ostream &stream) {
          using Decayed = typename std::decay_t<TNbtStruct>;
          std::invoke(&Decayed::serialize, static_cast<const Decayed *>(object), stream, "data");
       })
   {
      using Decayed = typename std::decay_t<TNbtStruct>;
      m_object      = new (m_object) Decayed(std::forward<TNbtStruct>(object));
   }

   TraceObject(const TraceObject &object)            = delete;
   TraceObject &operator=(const TraceObject &object) = delete;

   TraceObject(TraceObject &&object) noexcept :
       m_allocator(object.m_allocator),
       m_object(std::exchange(object.m_object, nullptr)),
       m_size(std::exchange(object.m_size, 0)),
       m_name(std::exchange(object.m_name, {})),
       m_time(std::exchange(object.m_time, {})),
       m_source_file(std::exchange(object.m_source_file, {})),
       m_line(std::exchange(object.m_line, {})),
       m_context_id{std::exchange(object.m_context_id, 0)},
       m_serialize_func(std::exchange(object.m_serialize_func, {}))
   {
   }

   TraceObject &operator=(TraceObject &&object) noexcept
   {
      m_allocator      = object.m_allocator;
      m_object         = std::exchange(object.m_object, nullptr);
      m_size           = std::exchange(object.m_size, 0);
      m_name           = std::exchange(object.m_name, {});
      m_time           = std::exchange(object.m_time, {});
      m_source_file    = std::exchange(object.m_source_file, {});
      m_line           = std::exchange(object.m_line, {});
      m_context_id     = std::exchange(object.m_context_id, 0);
      m_serialize_func = std::exchange(object.m_serialize_func, {});
   }

   ~TraceObject()
   {
      if (m_object != nullptr) {
         m_allocator.deallocate(static_cast<std::uint8_t *>(m_object), m_size);
      }
   }

   void serialize(std::ostream &stream) const
   {
      nbt::Writer writer(stream);
      writer.begin_compound("");
      writer.write_string("name", m_name);
      writer.write_long("time", m_time.time_since_epoch().count());
      writer.write_string("source_file", m_source_file);
      writer.write_int("line", m_line);
      writer.write_int("context_id", static_cast<int>(m_context_id));
      m_serialize_func(m_object, stream);
      writer.end_compound();
   }

 private:
   TAllocator m_allocator;
   void *m_object;
   std::size_t m_size;
   std::string m_name;
   std::chrono::system_clock::time_point m_time;
   std::string m_source_file;
   int m_line;
   util::ContextId m_context_id;
   std::function<void(const void *, std::ostream &)> m_serialize_func;
};

class TraceManager
{
 public:
   void initialize();
   void write_trace(TraceObject<> &&object);
   void flush();

   static TraceManager &the();

 private:
   std::mutex m_mutex;
   std::vector<TraceObject<>> m_buffer;
   std::ofstream m_file_stream;
};

}// namespace minecpp::debug

#define MCPP_TRACE(Name, ...)                                                      \
   {                                                                               \
      ::minecpp::nbt::trace::Name _{};                                             \
      __VA_ARGS__;                                                                 \
      ::minecpp::debug::TraceManager::the().write_trace(                           \
              ::minecpp::debug::TraceObject(__FILE__, __LINE__, 0, std::move(_))); \
   }

#define MCPP_TRACE_CTX(Name, ctx, ...)                                                    \
   {                                                                                      \
      ::minecpp::nbt::trace::Name _{};                                                    \
      __VA_ARGS__;                                                                        \
      ::minecpp::debug::TraceManager::the().write_trace(                                  \
              ::minecpp::debug::TraceObject(__FILE__, __LINE__, ctx.id(), std::move(_))); \
   }
