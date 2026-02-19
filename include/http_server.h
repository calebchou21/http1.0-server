#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>

class HttpServer 
{
    public:
        HttpServer(std::string ipAddress, int port);
        ~HttpServer();

        void listen();

    private:
        int m_socket;
        std::string m_ipAddress;
        int m_port;
        
        void logMessage(const std::string &message);
        void logError(const std::string &message);
};
#endif
