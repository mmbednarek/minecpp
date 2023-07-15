#include "StatusHandler.h"
#include "../Connection.h"

#include "minecpp/format/Format.h"
#include "minecpp/net/status/Clientbound.schema.h"
#include "minecpp/net/status/Serverbound.schema.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::front::protocol {

StatusHandler::StatusHandler() = default;

extern const char *g_favicon;

void StatusHandler::handle(Connection &conn, minecpp::network::message::Reader &r)
{
   net::status::sb::visit_message(*this, conn, r);
}

void StatusHandler::on_status(Connection &connection,
                              const net::status::sb::Status & /*status*/)
{
   using minecpp::format::Color;

   format::Builder builder;
   builder.bold(Color::Gold, "MineCPP Server\n").text("This server implementation is under development");

   std::stringstream ss;
   ss << R"({"description":)" << builder.to_string() << R"(,)";
   ss << R"("favicon":"data:image/png;base64,)" << g_favicon << R"(",)";
   ss << R"("players":{"max":10000,"online":6142},)";
   ss << R"("version":{"name": "1.19.3", "protocol": 761}})";

   net::status::cb::Status status;
   status.status = ss.str();
   connection.send_message_then_read(status, *this);
}

void StatusHandler::on_ping(Connection &connection, const net::status::sb::Ping &ping)
{
   net::status::cb::Ping response;
   response.payload = ping.payload;
   connection.send_message_then_disconnect(response);
}

void StatusHandler::handle_disconnect(Connection & /*conn*/) {}

void StatusHandler::on_failure(Connection &/*connection*/,
                               const std::uint8_t message_id)
{
   spdlog::debug("[status protocol] unknown operation code {}", static_cast<int>(message_id));
}

const char *g_favicon = R"(
iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAIAAAAlC+aJAAABhGlDQ1BJQ0MgcHJvZmlsZQAAKJF9
kT1Iw0AcxV9TpaIVQTuIOGSoTnZRkeJUq1CECqFWaNXB5NIvaNKQpLg4Cq4FBz8Wqw4uzro6uAqC
4AeIq4uToouU+L+k0CLWg+N+vLv3uHsHCPUy06yuGKDptplKxMVMdlUMvMKPQfQhilmZWcacJCXR
cXzdw8fXuwjP6nzuz9Gv5iwG+ETiGDNMm3iDeGbTNjjvE4dYUVaJz4knTLog8SPXFY/fOBdcFnhm
yEyn5olDxGKhjZU2ZkVTI54mDquaTvlCxmOV8xZnrVxlzXvyFwZz+soy12mOIoFFLEGCCAVVlFCG
jQitOikWUrQf7+Afcf0SuRRylcDIsYAKNMiuH/wPfndr5acmvaRgHOh+cZyPMSCwCzRqjvN97DiN
E8D/DFzpLX+lDkQ/Sa+1tPARMLANXFy3NGUPuNwBhp8M2ZRdyU9TyOeB9zP6piwwdAv0rnm9Nfdx
+gCkqavkDXBwCIwXKHu9w7t72nv790yzvx8HnXLi5LMWtAAAAAlwSFlzAAAuIwAALiMBeKU/dgAA
AAd0SU1FB+cDEgwAKTGNBVYAAAAZdEVYdENvbW1lbnQAQ3JlYXRlZCB3aXRoIEdJTVBXgQ4XAAAD
FUlEQVRo3u1aUW7bMAx9JGU7G4rdahfaHXrhoVhtSRT3kbRdbCqNA6dZWvHDQGjH5hPJR1I2/fz1
CE90nLATrJHS+fpsydezuvqIaakkYvdirlkjuwGj4mpSs36t8KmTKz1wE+GtblSLn63ErFwXwN17
oAH4qgACgELq8a6QkfufxPnoFroxWTFLKbpUjhgHG+YAXOsBmCmRmOlp6wFkUQAoYBaP7zPgLITB
/AJKujfXPTvRtCKEltZf4uISWg40AA1AAwCMGKt1oNqfscN0AlGoR94BHjOO7D+YQDUm9SaEqCUL
z63Vkk+ynNf/KReX1wuUISM/nzsPIFXIG5H8U1rydUPofOsBBPj9d836jvuWxA1AA/Ap54GCwuD9
cdEnz3k06Ns10eK809boE4j0tcdPaV4lqK9OF7mkykCD8np843VyqsweUipxxRIJpQrlx+TUuOW6
XBhCXBnHbiWqaR0A1wMfIF2Sr5XEnxfA2hxIiJsYlDq9bw+szQGnmc4aAZSOgoVMubbzMU/6nP0V
km5B5zFwv9YDh82bJYCsVde71ldXIgw5T171iTVlFuf+VBA53nEIrbL+ZBKnbeoAZ7oNC7U6cG8A
3Aw+vdFwGwBuT3uB9OhXGurnUlA6dNFi/ELzB43CAITjWmEC0sPxX6XIoNO03P4mQzhpa+J0XIW8
pl+6qTy/U8he7T78DPaygZOPDSIT2xs9n07IiSIj5ByXfUnsUm36WQ5GWVPFAR+SxFedLDYD8Cf+
bjTaAPzPIhbWAZCVPcz3/sdNgIVxepqpdsPDgRbHp2H3MOdKjLVtfeqOmNWS7pWjORReUATO7OK+
fAAQeXpxhbwz0OwhFbE9hvnp3bmvTWd4zreVxIsL88epm+UAG183iVm3KT9u/DQabQC8jMyb3Of8
V5c39kAh/xs4wrrcCwDQM2KpPkle0xoAivcJC5MQsftd3o6+uXlssBO2lsUrXkFwnRzQ8wGDcxd1
kThXmsJA7GCIFJnEc70kiwXl3FAhgTmBumUI1b6MPH+ZL0izxkINQANQ2/+B3gWAv5hjW5zpJFU/
AAAAAElFTkSuQmCC
)";

}// namespace minecpp::service::front::protocol
