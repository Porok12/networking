#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;
using boost::asio::ip::address;

class udp_client {
public:
    explicit udp_client(std::string address, int port);

    boost::asio::io_service io_service;
    udp::socket socket{io_service};
    boost::array<char, 256> recv_buffer;
    udp::endpoint remote_endpoint;

    void setEndpoint(std::string address, int port);

    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);

    void wait();

    void Receiver();

    void send(std::string in);

private:
    udp::endpoint remote_endpoint_;
};

#endif // UDP_CLIENT_H