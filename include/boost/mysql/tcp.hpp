//
// Copyright (c) 2019-2021 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MYSQL_SOCKET_TCP_HPP
#define BOOST_MYSQL_SOCKET_TCP_HPP

#include <boost/mysql/socket_connection.hpp>
#include <boost/mysql/resultset.hpp>
#include <boost/mysql/prepared_statement.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace boost {
namespace mysql {

/// A connection to MySQL over a TCP socket.
using tcp_connection = socket_connection<boost::asio::ip::tcp::socket>;

/// A prepared statement associated to a [reflink tcp_connection].
using tcp_prepared_statement = prepared_statement<boost::asio::ip::tcp::socket>;

/// A resultset associated with a [reflink tcp_connection].
using tcp_resultset = resultset<boost::asio::ip::tcp::socket>;

} // mysql
} // boost

#endif