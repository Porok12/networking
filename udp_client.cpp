#include "udp_client.h"

udp_client::udp_client(std::string address, int port)
        : remote_endpoint_(udp::endpoint(address::from_string(address), port)){

}

void udp_client::handle_receive(const boost::system::error_code &error, size_t bytes_transferred) {
    if (error) {
        std::cout << "Receive failed: " << error.message() << "\n";
        return;
    }

    std::cout << "Received: '";
    std::cout.write(recv_buffer.data(), bytes_transferred-1);
    std::cout << "' (" << error.message() << ")" << std::endl;

    wait();
}

void udp_client::wait() {
    socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
                              boost::bind(&udp_client::handle_receive, this,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));
}

void udp_client::Receiver() {
    socket.open(udp::v4());
    socket.bind(remote_endpoint_);

    wait();

    io_service.run();
}

void udp_client::send(std::string in) {
    boost::system::error_code err;

    example mystruct;
    mystruct.id = 1;
    mystruct.type = MessageType::MESSAGE;
    mystruct.value = in;
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << mystruct;

    socket.send_to( boost::asio::buffer(archive_stream.str()), remote_endpoint, 0, err);
}

void udp_client::setEndpoint(std::string address, int port) {
    remote_endpoint = udp::endpoint(address::from_string(address), port);
}
