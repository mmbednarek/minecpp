#include "service.h"
#include "protocol/protocol.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <grpcpp/client_context.h>
#include <grpcpp/grpcpp.h>

namespace Front {

Service::Service(Config &conf) : player_services(conf.engine_hosts.size()) {
   int i = 0;
   for (const auto &host : conf.engine_hosts) {
      auto channel =
          grpc::CreateChannel(host, grpc::InsecureChannelCredentials());
      player_services[i] = minecpp::engine::PlayerService::NewStub(channel);
      i++;
   }

   std::ifstream recipe_st;
   recipe_st.open(conf.recipe_path);
   if (!recipe_st.is_open()) {
      throw std::runtime_error("could not open recipe file");
   }
   recipe_st.seekg(0, std::ios::end);
   cached_recipes_size = recipe_st.tellg();
   recipe_st.seekg(0, std::ios::beg);
   cached_recipes = new char[cached_recipes_size];
   recipe_st.read(cached_recipes, cached_recipes_size);

   std::ifstream tags_st;
   tags_st.open(conf.tags_path);
   if (!tags_st.is_open()) {
      throw std::runtime_error("could not open recipe file");
   }
   tags_st.seekg(0, std::ios::end);
   cached_tags_size = tags_st.tellg();
   tags_st.seekg(0, std::ios::beg);
   cached_tags = new char[cached_tags_size];
   tags_st.read(cached_tags, cached_tags_size);
}

Service::~Service() { delete[] cached_recipes; }

Service::LoginResponse Service::login_player(std::string &user_name) {
   auto player = new Player(user_name);

   try {
      players.add_player(player);
   } catch (PlayerException &e) {
      return Service::LoginResponse{
          .accepted = false,
          .refusal_reason = "invalid player data",
      };
   }

   // TODO: Encryption authentication etc.

   return Service::LoginResponse{.accepted = true,
                                 .user_name = player->name(),
                                 .uuid = player->user_id()};
}

MineNet::Message::Raw get_command_list();

void Service::init_player(Front::Connection &conn, boost::uuids::uuid id) {
   using namespace MineNet::Message;

   conn.set_state(Protocol::State::Play);
   auto player = players.get_player(id);

   grpc::ClientContext ctx;

   minecpp::engine::AcceptPlayerResponse res;
   minecpp::engine::AcceptPlayerRequest req;
   req.set_name(player.name());
   req.set_uuid(player.user_id_str());
   get_player_service()->AcceptPlayer(&ctx, req, &res);

   conn.send(JoinGame{
       .player_id = res.player_id(),
       .game_mode = static_cast<uint8_t>(res.game_info().mode()),
       .dimension = static_cast<uint32_t>(res.game_info().dimension()),
       .seed = res.game_info().seed(),
       .max_players = static_cast<uint8_t>(res.game_info().max_players()),
       .world_type = ({
          auto wld_type =
              minecpp::engine::WorldType_Name(res.game_info().world());
          boost::algorithm::to_lower(wld_type);
          wld_type;
       }),
       .view_distance = static_cast<uint32_t>(res.game_info().view_distance()),
       .reduced_debug_info = res.game_info().reduced_debug_info(),
       .immediate_respawn = res.game_info().do_immediate_respawn(),
   });

   conn.send(ServerBrand{"minecraft:brand.minecpp"});

   conn.send(Difficulty{.difficulty =
                            static_cast<uint8_t>(res.game_info().difficulty()),
                        .locked = false});

   conn.send(PlayerAbilities{
       .flags = 0,
       .fly_speed = 0.5f,
       .walk_speed = 0.1f,
   });

   conn.send(Raw{
       .size = cached_recipes_size,
       .data = cached_recipes,
   });

   conn.send(Raw{
       .size = cached_tags_size,
       .data = cached_tags,
   });
   conn.send(EntityStatus{
       .entity_id = res.player_id(),
       .opcode = 0x18,
   });

   conn.send(get_command_list());

   conn.send(RecipeBook{
       .state = Init,
       .gui_open = false,
       .filtering_craftable = false,
       .furnace_gui_open = false,
       .furnace_filtering_craftable = false,
   });

   conn.send(PlayerPositionLook{
       .x = 198.0,
       .y = 70.0,
       .z = -178.0,
       .yaw = 0.0f,
       .pitch = 0.0f,
       .flags = 0,
       .tp_id = 0,
   });

   conn.send(AddPlayer{
       .id = player.user_id(),
       .name = player.name(),
       .game_mode = 0x00,
       .ping = 0x00,
   });

   conn.send(UpdateChunkPosition{
       .x = 198 / 16,
       .z = -178 / 16,
   });
}

EnginePlayerService &Service::get_player_service() {
   boost::random::uniform_int_distribution<> dist(0,
                                                  player_services.size() - 1);
   return player_services[dist(rand)];
}

const char command_list[]{
    0x12, 0x14, 0x00, 0x09, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x05, 0x01, 0x0a, 0x04, 0x68, 0x65, 0x6c, 0x70, 0x05, 0x01, 0x0b,
    0x04, 0x6c, 0x69, 0x73, 0x74, 0x01, 0x01, 0x0c, 0x02, 0x6d, 0x65, 0x01,
    0x01, 0x0d, 0x03, 0x6d, 0x73, 0x67, 0x01, 0x01, 0x0e, 0x07, 0x74, 0x65,
    0x61, 0x6d, 0x6d, 0x73, 0x67, 0x09, 0x00, 0x04, 0x04, 0x74, 0x65, 0x6c,
    0x6c, 0x09, 0x00, 0x05, 0x02, 0x74, 0x6d, 0x01, 0x01, 0x0f, 0x07, 0x74,
    0x72, 0x69, 0x67, 0x67, 0x65, 0x72, 0x09, 0x00, 0x04, 0x01, 0x77, 0x06,
    0x00, 0x07, 0x63, 0x6f, 0x6d, 0x6d, 0x61, 0x6e, 0x64, 0x10, 0x62, 0x72,
    0x69, 0x67, 0x61, 0x64, 0x69, 0x65, 0x72, 0x3a, 0x73, 0x74, 0x72, 0x69,
    0x6e, 0x67, 0x02, 0x05, 0x00, 0x05, 0x75, 0x75, 0x69, 0x64, 0x73, 0x06,
    0x00, 0x06, 0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x10, 0x62, 0x72, 0x69,
    0x67, 0x61, 0x64, 0x69, 0x65, 0x72, 0x3a, 0x73, 0x74, 0x72, 0x69, 0x6e,
    0x67, 0x02, 0x02, 0x01, 0x10, 0x07, 0x74, 0x61, 0x72, 0x67, 0x65, 0x74,
    0x73, 0x10, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a,
    0x65, 0x6e, 0x74, 0x69, 0x74, 0x79, 0x02, 0x06, 0x00, 0x07, 0x6d, 0x65,
    0x73, 0x73, 0x61, 0x67, 0x65, 0x11, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72,
    0x61, 0x66, 0x74, 0x3a, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x16,
    0x02, 0x11, 0x12, 0x09, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x69, 0x76,
    0x65, 0x13, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a,
    0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x14, 0x6d, 0x69,
    0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x61, 0x73, 0x6b, 0x5f,
    0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x06, 0x00, 0x07, 0x6d, 0x65, 0x73,
    0x73, 0x61, 0x67, 0x65, 0x11, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61,
    0x66, 0x74, 0x3a, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x01, 0x01,
    0x13, 0x03, 0x61, 0x64, 0x64, 0x01, 0x01, 0x13, 0x03, 0x73, 0x65, 0x74,
    0x06, 0x00, 0x05, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x11, 0x62, 0x72, 0x69,
    0x67, 0x61, 0x64, 0x69, 0x65, 0x72, 0x3a, 0x69, 0x6e, 0x74, 0x65, 0x67,
    0x65, 0x72, 0x00, 0x00};

MineNet::Message::Raw get_command_list() {
   return MineNet::Message::Raw{
       .size = sizeof(command_list),
       .data = command_list,
   };
}

} // namespace Front
