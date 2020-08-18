#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include "udp_server.h"
#include <pqxx/pqxx>
#include <nlohmann/json.hpp>
#include <fstream>
#include <log4cplus/log4cplus.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/initializer.h>
#include <cli11/CLI11.hpp>


using boost::asio::ip::udp;
namespace po = boost::program_options;
using json = nlohmann::json;

void logger_test() {
    log4cplus::Initializer initializer;

    log4cplus::BasicConfigurator config;
    config.configure();

    log4cplus::Logger logger = log4cplus::Logger::getInstance(
            LOG4CPLUS_TEXT("main"));
    LOG4CPLUS_WARN(logger, LOG4CPLUS_TEXT("Hello, World!"));
}

namespace ns {
    struct server_settings {
        std::string ip;
        int port;
        std::string name;
        int max_users;
//        bool database;
    };

    void to_json(json& j, const server_settings& ss) {
        j = json{{"ip", ss.ip}, {"port", ss.port}, {"name", ss.name}, {"max_users", ss.max_users}, /*{"database", ss.database}*/};
    }

    void from_json(const json& j, server_settings& ss) {
        try {
            j.at("ip").get_to(ss.ip);
            j.at("port").get_to(ss.port);
            j.at("name").get_to(ss.name);
            j.at("max_users").get_to(ss.max_users);
//            j.at("database").get_to(ss.database);

        } catch (const json::out_of_range &e) {
            std::cerr << e.id << ": " << e.what() << std::endl;
        }
    }
}

void db_test() {
    try {
        pqxx::connection C("postgresql://guest:ataga@localhost/networking");

        if (C.is_open()) {
            std::cout << "Connected to " << C.dbname() << std::endl;
        } else {
            return;
        }

        pqxx::work W{C};

        pqxx::result R{W.exec("SELECT username FROM users")};

        std::cout << "Found " << R.size() << " users:\n";
        for (auto row: R) {
            std::cout << " -- " << row[0].c_str() << '\n';
        }

        C.disconnect ();
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
    }
}

void json_test() {
    std::ifstream i("../config.json");
    json j;
    i >> j;
    i.close();

    std::cout << j << std::endl;

    std::cout << "ip: " << j["ip"] << std::endl;

    auto p2 = j.get<ns::server_settings>();

    std::cout << p2.name << std::endl;
}

int main(int argc, char* argv[]) {
    logger_test();
    json_test();
    db_test();

    CLI::App app {"description"};

    // Define options
    int p = 0;
    app.add_option("-p,--port", p, "Port");
    app.allow_extras(true);

//    std::string req_real_file;
//    app.add_option("-f,--file", file, "Require an existing file")
//            ->required()
//            ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    std::cout << "Port value: " << p << std::endl;

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