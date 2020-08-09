#pragma once

#include "connection.h"
#include "protocol/handler.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <functional>
#include <string>
#include <vector>
#include <map>

namespace Front {

using boost::asio::ip::tcp;

class Server {
public:
	explicit Server(boost::asio::io_context &ctx, short port,
					Protocol::Handler *play, Protocol::Handler *status,
					Protocol::Handler *login);

	void accept_conn();

	void handshake(const std::shared_ptr<Connection> &conn);

	void drop_connection(std::size_t id);

	void for_each_connection(
			std::function<void(const std::shared_ptr<Connection> &)>);

	bool has_connection(boost::uuids::uuid player_id);

	std::shared_ptr<Connection> connection_by_id(boost::uuids::uuid player_id);

	Protocol::Handler &get_handler(Protocol::State state);

	void index_connection(boost::uuids::uuid index, std::size_t id);

private:
	std::map<boost::uuids::uuid, std::size_t> conn_ids;
	std::vector<std::shared_ptr<Connection>> connections;
	tcp::acceptor acceptor;
	Protocol::Handler *handlers[3];
};

} // namespace Front
