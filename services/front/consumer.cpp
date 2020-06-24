#include "consumer.h"
#include <boost/uuid/uuid.hpp>
#include <minenet/msg/clientbound.h>
#include <mineutils/format.h>
#include <mineutils/hex.h>
#include <mineutils/uuid.h>
#include <spdlog/spdlog.h>
#include <stdexcept>

namespace Front {

Consumer::Consumer(KafkaSettings settings, Server &server) : server(server) {
   cppkafka::Configuration config = {{"metadata.broker.list", settings.hosts},
                                     {"enable.auto.commit", false},
                                     {"queue.buffering.max.ms", 50},
                                     {"group.id", "front"}};

   cppkafka::TopicConfiguration topic_config = {
       {"auto.offset.reset", "latest"}};

   config.set_default_topic_configuration(topic_config);

   consumer = new cppkafka::Consumer(config);
   consumer->subscribe(settings.topics);
}

void Consumer::consume(KafkaHandler handler) {
   auto message = consumer->poll();

   if (message) {
      if (message.get_payload().get_size() == 0) {
         return;
      }

      std::string key = message.get_key();
      std::string payload = message.get_payload();

      if (key == "EntityMove") {
         EntityMove pos;
         pos.ParseFromString(payload);
         on_event(pos);
      } else if (key == "EntityLook") {
         EntityLook msg;
         msg.ParseFromString(payload);
         on_event(msg);
      } else if (key == "RemovePlayer") {
         RemovePlayer msg;
         msg.ParseFromString(payload);
         on_event(msg);
      } else if (key == "UpdateBlock") {
         UpdateBlock msg;
         msg.ParseFromString(payload);
         on_event(msg);
      } else if (key == "Chat") {
         Chat msg;
         msg.ParseFromString(payload);
         on_event(msg);
      }

      consumer->commit();
   }
}

void Consumer::on_event(EntityMove &pos) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, pos.uuid().data());
   server.for_each_connection([&pos, id](Connection *conn) {
      if (!conn)
         return;
      if (conn->get_uuid() == id) {
         return;
      }
      conn->send(MineNet::Message::EntityMove{
          .entity_id = pos.id(),
          .x = static_cast<short>(pos.x()),
          .y = static_cast<short>(pos.y()),
          .z = static_cast<short>(pos.z()),
          .yaw = pos.yaw(),
          .pitch = pos.pitch(),
          .on_ground = true,
      });
   });
}

void Consumer::on_event(EntityLook &pos) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, pos.uuid().data());
   server.for_each_connection([&pos, id](Connection *conn) {
      if (!conn)
         return;
      if (conn->get_uuid() == id) {
         return;
      }
      spdlog::info("rot yaw: {}, pitch: {}", pos.yaw(), pos.pitch());
      conn->send(MineNet::Message::EntityLook{
          .entity_id = pos.id(),
          .yaw = pos.yaw(),
          .pitch = pos.pitch(),
          .on_ground = true,
      });
      conn->send(MineNet::Message::EntityHeadLook{
          .entity_id = pos.id(),
          .yaw = pos.yaw(),
      });
   });
}

void Consumer::on_event(SpawnPlayer &pos) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, pos.uuid().data());

   server.for_each_connection([&pos, id](Connection *conn) {
      conn->send(MineNet::Message::SpawnPlayer{
          .entity_id = pos.id(),
          .id = id,
          .x = pos.x(),
          .y = pos.y(),
          .z = pos.z(),
          .yaw = pos.yaw(),
          .pitch = pos.pitch(),
      });
   });
}

void Consumer::on_event(Chat &msg) {
   server.for_each_connection([&msg](Connection *conn) {
      if (!conn)
         return;
      conn->send(MineNet::Message::Chat{
          .message = msg.message(),
      });
   });
}

void Consumer::on_event(RemovePlayer &msg) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, msg.uuid().data());

   server.for_each_connection([&msg, id](Connection *conn) {
      if (!conn)
         return;
      conn->send(MineNet::Message::RemovePlayer{
          .id = id,
      });
      conn->send(MineNet::Message::DestroyEntity{
          .entity_id = static_cast<uint32_t>(msg.entity_id()),
      });
   });
}

void Consumer::on_event(UpdateBlock &msg) {
   int chunk_x = msg.x() >= 0 ? (msg.x() / 16) : (msg.x() / 16 - 1);
   int chunk_z = msg.z() >= 0 ? (msg.z() / 16) : (msg.z() / 16 - 1);

   int offset_x = msg.x() & 15;
   int offset_z = msg.z() & 15;

   short offset = offset_x << 12 | msg.y() | offset_z << 8;

   MineNet::Message::MultiBlockChange change{
       .chunk_x = chunk_x,
       .chunk_z = chunk_z,
       .changes{
           MineNet::Message::MultiBlockChange::Change{
               .offset = offset,
               .state = static_cast<uint32_t>(msg.state()),
           },
       },
   };

   server.for_each_connection([change](Connection *conn) {
      if (!conn)
         return;
      conn->send(change);
   });
}

} // namespace Front
