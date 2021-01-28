#include "server.h"
#include "protocol/protocol.h"
#include <boost/asio.hpp>
#include <minecpp/network/msg/reader.h>
#include <spdlog/spdlog.h>
#include <utility>

namespace Front {

Server::Server(boost::asio::io_context &ctx, short port,
			   Protocol::Handler *play, Protocol::Handler *status,
			   Protocol::Handler *login)
		: acceptor(ctx, tcp::endpoint(tcp::v4(), port)), handlers{play, status,
																  login} {
	accept_conn();
}

void Server::accept_conn() {
	auto conn = std::make_shared<Connection>(
			(boost::asio::io_context &) acceptor.get_executor().context(), this);
	acceptor.async_accept(
			conn->socket, [this, conn](const boost::system::error_code &err) {
				if (err) {
					spdlog::error("error accepting connection: {}", err.message());
					accept_conn();
					return;
				}

				handshake(conn);
				accept_conn();
			});
}

void Server::handshake(const std::shared_ptr<Connection> &conn) {
	uint8_t packet_size;
	try {
		packet_size = conn->read_packet_size();
	} catch (std::exception &e) {
		return;
	}

	if (packet_size == 0) {
		return;
	}

	boost::asio::streambuf buff(packet_size);

	try {
		conn->read(buff);
	} catch (std::exception &e) {
		return;
	}

	std::istream s(&buff);
	MineNet::Message::Reader r(s);

	if (r.read_byte() != 0) {
		return;
	}

	auto protocol_version = r.read_varint();
	auto host = r.read_string();
	auto port = r.read_big_endian<uint16_t>();
	auto request_state = static_cast<Protocol::State>(r.read_varint());

	if (request_state != Protocol::Login && request_state != Protocol::Status) {
		return;
	}

	conn->set_non_blocking();

	conn->set_state(request_state);

	conn->id = connections.size();
	connections.emplace_back(conn);

	conn->async_read_packet(conn, *handlers[request_state]);
}

void Server::drop_connection(std::size_t id) {
	if (id >= connections.size())
		return;
	connections[id] = nullptr;
}

void Server::for_each_connection(
		std::function<void(const std::shared_ptr<Connection> &)> f) {
	std::for_each(connections.begin(), connections.end(), std::move(f));
}

Protocol::Handler &Server::get_handler(const Protocol::State state) {
	return *handlers[state];
}

void Server::index_connection(boost::uuids::uuid index, std::size_t id) {
	conn_ids[index] = id;
}

bool Server::has_connection(boost::uuids::uuid player_id) {
	return conn_ids.contains(player_id);
}

std::shared_ptr<Connection>
Server::connection_by_id(boost::uuids::uuid player_id) {
	return connections.at(conn_ids.at(player_id));
}

} // namespace Front
