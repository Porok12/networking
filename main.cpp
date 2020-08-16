#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include "udp_server.h"
#include <pqxx/pqxx>

using boost::asio::ip::udp;
namespace po = boost::program_options;

void db_test() {
    try {
        pqxx::connection C("postgresql://guest:ataga@localhost/networking");
        std::cout << "Connected to " << C.dbname() << std::endl;
        pqxx::work W{C};

        pqxx::result R{W.exec("SELECT username FROM users")};

        std::cout << "Found " << R.size() << " users:\n";
        for (auto row: R) {
            std::cout << " -- " << row[0].c_str() << '\n';
        }

    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char* argv[]) {
    db_test();

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