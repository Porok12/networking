#include "udp_server.h"

std::string make_daytime_string() {
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

udp_server::udp_server(std::string address, int port)
        : socket_(io_service, udp::endpoint(address::from_string(address), port)) {
    start_receive();
}

void udp_server::start_receive() {
    socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_,
            boost::bind(&udp_server::handle_receive, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));

    io_service.run();
}

void udp_server::handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred) {
    std::istringstream archive_stream(recv_buffer_.data());
    example mystruct;
    boost::archive::text_iarchive archive(archive_stream);
    archive >> mystruct;

    std::cout << "(" << remote_endpoint_.address().to_string() << ") [" << mystruct.type << "] " << mystruct.id << ": " << mystruct.value << std::endl;

    if (!error || error == boost::asio::error::message_size) {
        boost::shared_ptr<std::string> message(new std::string(make_daytime_string()));

        socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
                              boost::bind(&udp_server::handle_send, this, message,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));

        start_receive();
    }
}

void udp_server::handle_send(boost::shared_ptr<std::string> messgage, const boost::system::error_code &, std::size_t) {
    std::cout << "Send back: " << *messgage << std::endl;
}
