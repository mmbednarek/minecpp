#include <benchmark/benchmark.h>
#include <minecpp/nbt/repository/v1/repository.nbt.h>
#include <minecpp/nbt/parser.h>
#include <sstream>
#include <fstream>

void copy_stream(std::istream &in, std::ostream &out) {
   char buff[1024];
   std::streamsize count;
   do {
      count = in.readsome(buff, 1024);
      out.write(buff, count);
   } while (count == 1024);
}

static void bm_repository_struct(benchmark::State &state) {
   std::ifstream fs("repository.bin");
   std::stringstream data;
   copy_stream(fs, data);
   data.seekg(0, std::ios::beg);

   for (auto _ : state) {
      auto res = minecpp::nbt::repository::v1::Repository::deserialize(data);

      std::stringstream ss;
      res.serialize(ss, "");
   }
}
BENCHMARK(bm_repository_struct);

static void bm_repository_dynamic(benchmark::State &state) {
   std::ifstream fs("repository.bin");
   std::stringstream data;
   copy_stream(fs, data);
   data.seekg(0, std::ios::beg);

   for (auto _ : state) {
      minecpp::nbt::Parser parser(data);
      auto comp = parser.read_compound();

      std::stringstream ss;
      minecpp::nbt::Content{
              .tag_id =  minecpp::nbt::TagId::Compound,
              .content = comp,
      }.serialize("",ss);
   }
}
BENCHMARK(bm_repository_dynamic);

BENCHMARK_MAIN();
