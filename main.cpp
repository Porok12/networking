#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/program_options.hpp>
#include "udp_client.h"

using boost::asio::ip::udp;
namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help", "help message")
                ("address", po::value<std::string>()->required(), "set ip address")
                ("port", po::value<int>()->required(), "set port")
                ("server-address", po::value<std::string>()->required(), "set server ip address")
                ("server-port", po::value<int>()->required(), "set server port")
                ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 1;
        }

        if (vm.count("address")) {
            std::cout << "Address was set to "
                      << vm["address"].as<std::string>() << ".\n";
        }

        if (vm.count("port")) {
            std::cout << "Port was set to "
                      << vm["port"].as<int>() << ".\n";
        }

        if (vm.count("server-address")) {
            std::cout << "Server address was set to "
                      << vm["server-address"].as<std::string>() << ".\n";
        }

        if (vm.count("server-port")) {
            std::cout << "Server port was set to "
                      << vm["server-port"].as<int>() << ".\n";
        }

        if (vm.count("address") && vm.count("port") && vm.count("server-address") && vm.count("server-port")) {
            try {
                std::cout << "------------------------------------------\n";
                udp_client client(vm["address"].as<std::string>(), vm["port"].as<int>());
                client.setEndpoint(vm["server-address"].as<std::string>(), vm["server-port"].as<int>());
                boost::thread r([&] { client.Receiver(); });

                std::string in;
                while (in != "quit") {
                    std::getline(std::cin, in);
                    client.send(in);
                }

                r.join();

            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }

        } else {
            std::cout << "Invalid parameters.\n";
        }

    } catch (const po::error &ex) {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}
