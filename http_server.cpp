#include <sys/socket.h>
#include <stdexcept>
#include <iostream>

#include "http_server.h"

HttpServer::HttpServer(std::string ipAddress, int port) 
    : m_socket(socket(AF_INET, SOCK_STREAM, 0)),
    m_ipAddress(ipAddress), // TODO: May not need to store these if I do all set up stuff in the constructor
    m_port(port)
{
    if (m_socket < 0)
    {
        throw std::runtime_error("ERROR: Socket creation failed");
    }
    
    // struct sockaddr_in server_addr;
    // kserver_addr.sin_family = AF_INET;


    // bind(m_socket, )
}

HttpServer::~HttpServer() {}

void HttpServer::listen()
{
    // 2. Listen
}

void HttpServer::logMessage(const std::string &message)
{
    std::cout << "LOG: " << message << std::endl;
}

void HttpServer::logError(const std::string &message)
{
    std::cout << "\x1b[31m" << "ERROR: " << message << "\x1b[0m" << std::endl;
}
