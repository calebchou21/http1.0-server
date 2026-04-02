#ifndef CONNECTION_H
#define CONNECTION_H

#include <filesystem>
#include <string>

#include "response.h"
#include "http_parser.h"

class Connection {
public:
    explicit Connection(int fd);
    ~Connection();

    void handle();

private:
    int m_fd;
    int m_requestSize = 0; // bytes
    std::string m_writeBuffer;
    HttpParser m_parser;
    static constexpr std::string_view SERVE_FROM = "website";
    
    HttpResponse handlePost(const HttpRequest &request);
    bool readFromSocket();
    HttpResponse processRequest(const HttpRequest &request);
    bool writeToSocket(const std::string &serializedResponse);
};
#endif
