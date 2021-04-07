//
// Copyright (c) 2019-2021 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MYSQL_TEST_INTEGRATION_STREAM_LIST_HPP
#define BOOST_MYSQL_TEST_INTEGRATION_STREAM_LIST_HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/local/stream_protocol.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/use_future.hpp>

namespace boost {
namespace mysql {
namespace test {

// A TCP socket that has use_future as default completion token
class future_executor : public boost::asio::io_context::executor_type
{
public:
    future_executor(const boost::asio::io_context::executor_type& inner) :
        boost::asio::io_context::executor_type(inner) {}
    using default_completion_token_type = boost::asio::use_future_t<>;
    
    // Required to build in MSVC for some arcane reason
    operator boost::asio::any_io_executor() const
    {
        return boost::asio::any_io_executor(static_cast<const boost::asio::io_context::executor_type>(*this));
    }
};

// The actual streams we will be using to test
using tcp_socket = boost::asio::ip::tcp::socket;
using tcp_ssl_socket = boost::asio::ssl::stream<tcp_socket>;
using tcp_ssl_future_socket = boost::asio::ssl::stream<
    boost::asio::basic_stream_socket<
        boost::asio::ip::tcp,
        future_executor
    >
>;

#ifdef BOOST_ASIO_HAS_LOCAL_SOCKETS
using unix_socket = boost::asio::local::stream_protocol::socket;
using unix_ssl_socket = boost::asio::ssl::stream<unix_socket>;
#endif

// Stream names
template <class Stream> constexpr const char* get_stream_name();
template <> constexpr const char* get_stream_name<tcp_socket>() { return "tcp"; }
template <> constexpr const char* get_stream_name<tcp_ssl_socket>() { return "tcp_ssl"; }
template <> constexpr const char* get_stream_name<tcp_ssl_future_socket>() { return "tcp_ssl_default_token"; }

#ifdef BOOST_ASIO_HAS_LOCAL_SOCKETS
template <> constexpr const char* get_stream_name<unix_socket>() { return "unix"; }
template <> constexpr const char* get_stream_name<unix_ssl_socket>() { return "unix_ssl"; }
#endif

// Supports SSL (doesn't use the lib's type trait for test independance)
template <class Stream> constexpr bool supports_ssl();
template <> constexpr bool supports_ssl<tcp_socket>() { return false; }
template <> constexpr bool supports_ssl<tcp_ssl_socket>() { return true; }
template <> constexpr bool supports_ssl<tcp_ssl_future_socket>() { return true; }

#ifdef BOOST_ASIO_HAS_LOCAL_SOCKETS
template <> constexpr bool supports_ssl<unix_socket>() { return false; }
template <> constexpr bool supports_ssl<unix_ssl_socket>() { return true; }
#endif

} // test
} // mysql
} // boost

#endif