#include <cstdio>
#include <fmt/core.h>
#include <minecpp/service/discovery/Api.h>
#include <string_view>

template<typename... ARGS>
void die(fmt::format_string<ARGS...> fmt, ARGS &&...args)
{
   fmt::print(stderr, fmt, std::forward<ARGS>(args)...);
   std::exit(1);
}

int main()
{
   auto cli = minecpp::service::discovery::Client::create("127.0.0.1:9911");
   if (cli.has_failed()) {
      die("could not initialise client");
   }

   if (auto res = cli->register_service("minecpp.service.engine", "127.0.0.1", 7001); !res.ok()) {
      die("could not register service");
   }

   if (auto res = cli->register_service("minecpp.service.engine", "10.4.4.4", 7001); !res.ok()) {
      die("could not register service");
   }

   auto resolve_res = cli->resolve("minecpp.service.engine");
   if (!resolve_res.ok()) {
      die("could not resolve service");
   }

   auto result = resolve_res.unwrap();

   fmt::print("modified: {}\n", result.modified);
   fmt::print("endpoints\n");
   for (const auto &endpoint : result.endpoints) {
      fmt::print(" - {}\n", endpoint.to_string());
   }
}