#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include "udp_server.h"

using boost::asio::ip::udp;
namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help", "help message")
                ("address", po::value<std::string>()->required(), "set ip address")
                ("port", po::value<int>()->required(), "set port");

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

        if (vm.count("address") && vm.count("port")) {
            std::cout << "------------------------------------------\n";
            try {
                udp_server server(vm["address"].as<std::string>(), vm["port"].as<int>());

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