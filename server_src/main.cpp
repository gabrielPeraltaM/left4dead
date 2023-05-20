#include <iostream>
#include "./server.h"

#define SUCCESS 0
#define ERROR 1
#define SERVICE_NAME argv[1]

int main(int argc, char* argv[]) { try {
    if (argc != 2)
        throw std::runtime_error("Invalid arguments. Usage: ./server <service-name>");
    Server server(SERVICE_NAME);
    Server::execute();
    return SUCCESS;
} catch (const std::exception& err) {
    std::cerr
        << "Something gets wrong and an exception was caught: "
        << err.what() << std::endl;
    return ERROR;
} catch (...) {
    std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
    return ERROR;
} }
