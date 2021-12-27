#include <minecpp/service/discovery/api.h>
#include <fmt/core.h>
#include <cstdio>
#include <string_view>

void die(std::string_view value) {
   fmt::print(stderr, value);
   std::exit(1);
}

int main() {
   auto cli_result = minecpp::service::discovery::Client::create("127.0.0.1:9911");
   if (!cli_result.ok()) {
      die("could not initialise client");
   }

   auto cli = cli_result.unwrap();
   if (auto res = cli.register_service("minecpp.service.engine", "127.0.0.1", 7001); !res.ok()) {
      die("could not register service");
   }

   if (auto res = cli.register_service("minecpp.service.engine", "10.4.4.4", 7001); !res.ok()) {
      die("could not register service");
   }

   auto resolve_res = cli.resolve("minecpp.service.engine");
   if (!resolve_res.ok()) {
      die("could not resolve service");
   }

   auto result = resolve_res.unwrap();

   fmt::print("modified: {}\n", result.modified);
   fmt::print("endpoints\n");
   for (const auto &endpoint: result.endpoints) {
      fmt::print(" - {}\n", endpoint.to_string());
   }
}