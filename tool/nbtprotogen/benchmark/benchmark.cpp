#include <benchmark/benchmark.h>
#include <minecpp/nbt/chunk/v1/chunk.nbt.h>
#include <minecpp/nbt/parser.h>
#include <sstream>

static void bm_chunk_both(benchmark::State &state) {
   for (auto _ : state) {
      minecpp::nbt::chunk::v1::Chunk chunk{};
      chunk.level.x_pos = 234;
      chunk.level.z_pos = -213;
      chunk.level.biomes = {4, 3, 1};

      std::stringstream ss;
      chunk.serialize(ss, "");
      ss.seekg(0, std::ios::beg);

      auto check = minecpp::nbt::chunk::v1::Chunk::deserialize(ss);
   }
}
BENCHMARK(bm_chunk_both);

static void bm_chunk_deserialize(benchmark::State &state) {
   minecpp::nbt::chunk::v1::Chunk chunk{};
   chunk.level.x_pos = 234;
   chunk.level.z_pos = -213;
   chunk.level.biomes = {4, 3, 1};

   std::stringstream ss;
   chunk.serialize(ss, "");

   std::vector<int> response;

   for (auto _ : state) {
      ss.seekg(0, std::ios::beg);
      auto check = minecpp::nbt::chunk::v1::Chunk::deserialize(ss);
      response.push_back(check.level.x_pos);
   }
}
BENCHMARK(bm_chunk_deserialize);

static void bm_chunk_deserialize_dynamic(benchmark::State &state) {
   minecpp::nbt::chunk::v1::Chunk chunk{};
   chunk.level.x_pos = 234;
   chunk.level.z_pos = -213;
   chunk.level.biomes = {4, 3, 1};

   std::stringstream ss;
   chunk.serialize(ss, "");

   std::vector<int> response;

   for (auto _ : state) {
      ss.seekg(0, std::ios::beg);
      minecpp::nbt::Parser parser(ss);
      auto result = parser.read_compound();
      result.size();
      response.push_back(result[""].as<minecpp::nbt::CompoundContent>()["Level"].as<minecpp::nbt::CompoundContent>()["xPos"].as<int32_t>());
   }
}
BENCHMARK(bm_chunk_deserialize_dynamic);

struct foo {
   int a;
   std::string b;
   float c, d;
};

struct field {
   std::size_t offset;
};

template<typename TDst, typename TSrc>
TDst my_bit_cast(TSrc &&t) {
   TDst result{};
   std::memcpy(&result, &t, std::min(sizeof(TDst), sizeof(TSrc)));
   return result;
}

template<typename TElem, std::size_t CSize>
class ce_map {
 public:
   std::array<std::pair<std::string_view, TElem>, CSize> m_values;
//   template<typename ...TArgs>
//   constexpr ce_map(TArgs ...args) : m_values(args...) {}

   constexpr auto find(std::string_view key) {
      return std::find_if(m_values.begin(), m_values.end(), [rhs = key](std::pair<std::string_view, TElem> &lhs) {return lhs.first == rhs; });
   }

   constexpr auto end() {
      return m_values.end();
   }
};

ce_map<field, 4> field_map {
        std::pair<std::string_view, field>{"a", {my_bit_cast<std::size_t>(&foo::a)}},
        {"b", {my_bit_cast<std::size_t>(&foo::b)}},
        {"c", {my_bit_cast<std::size_t>(&foo::c)}},
        {"d", {my_bit_cast<std::size_t>(&foo::d)}}
};

template<typename T>
void ptr_put(foo *f, std::string_view name, T &&value) {
   auto it = field_map.find(name);
   if (it == field_map.end())
      return;

   using TClass = typename std::remove_reference<T>::type;
   auto field = my_bit_cast<TClass foo::*>(it->second.offset);
   f->*field = std::forward<TClass>(value);

//   auto *ptr = reinterpret_cast<typename std::remove_reference<T>::type *>(reinterpret_cast<char *>(f) + it->second.offset);
//   *ptr = std::forward<T>(value);
}

void bm_ptr_put(benchmark::State &state) {
   for(auto _ : state)  {
      foo f{};
      ptr_put(&f, "a", 15);
      ptr_put(&f, "b", std::string("hello"));
      ptr_put(&f, "c", 2.3f);
      ptr_put(&f, "d", 1.7f);
   }
}
BENCHMARK(bm_ptr_put);

template<typename T>
void simple_put(foo &f, std::string_view name, T &&value) {
   using TClass = typename std::remove_reference<T>::type;
   if constexpr (std::is_same_v<TClass, int>) {
      if(name == "a") {
         f.a = value;
         return;
      }
   }
   if constexpr (std::is_same_v<TClass, std::string>) {
      if(name == "b") {
         f.b = std::forward<T>(value);
         return;
      }
   }
   if constexpr (std::is_same_v<TClass, float>) {
      if(name == "c") {
         f.c = value;
         return;
      }
      if(name == "d") {
         f.d = value;
         return;
      }
   }
}

void bm_simple_put(benchmark::State &state) {
   for(auto _ : state)  {
      foo f{};
      simple_put(f, "a", 15);
      simple_put(f, "b", std::string("hello"));
      simple_put(f, "c", 2.3f);
      simple_put(f, "d", 1.7f);
   }
}
BENCHMARK(bm_simple_put);

BENCHMARK_MAIN();
