#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>

using boost::asio::ip::udp;
using boost::asio::ip::address;

enum MessageType {
    MESSAGE = 0x01
};

struct example {
    int id;
    MessageType type;
    std::string value;

private:
    friend class boost::serialization::access;

    template <typename archive>
    void serialize(archive& ar, const unsigned /*version*/) {
        ar & id;
        ar & type;
        ar & value;
    }
};

class udp_server {
public:
    explicit udp_server(std::string address, int port);

private:
    void start_receive();

    void handle_receive(const boost::system::error_code& error,
                        std::size_t bytes_transferred);

    void handle_send(boost::shared_ptr<std::string> message,
                     const boost::system::error_code& /*error*/,
                     std::size_t /*bytes_transferred*/);

    boost::asio::io_service io_service;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 256> recv_buffer_;
};


#endif // UDP_SERVER_H