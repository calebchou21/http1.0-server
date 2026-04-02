#include <iostream>
#include "response_serializer.h"
#include "test_file_service.h"
#include "request.h"
#include "response.h"
#include "file_service.h"

int runFileServiceTests() {
    int res = 0;
    res += getRequestWithUnsafePath();
    res += getRequestWithNonExistantFile();
    res += getRequestNotModified();
    res += getRequestOk();

    res += headRequestWithUnsafePath();
    res += headRequestWithNonExistantFile();
    res += headRequestNotModified();
    res += headRequestOk();

    return res;
}

int getRequestWithUnsafePath() {
    HttpRequest request = {
        HttpRequestMethod::GET,
        "this/is/a/../unsafe/path",
        "1.1",
        {{"Host", "example.com"}, {"Connection", "close"}},
        ""    
    };

    HttpResponse response = FileService::serveFile(request, request.path);
    if (response.status == HttpStatus::FORBIDDEN) {
        return 0;
    }

    std::cerr << "GET request expected FORBIDDEN" << std::endl;
    return 1;
}

int getRequestWithNonExistantFile() {
    HttpRequest request = {
        HttpRequestMethod::GET,
        "this/is/a/missing/path",
        "1.1",
        {{"Host", "example.com"}, {"Connection", "close"}},
        ""    
    };

    HttpResponse response = FileService::serveFile(request, request.path);
    if (response.status == HttpStatus::NOT_FOUND) {
        return 0;
    }

    std::cerr << "GET request expected NOT_FOUND" << std::endl;
    return 1;
}

int getRequestNotModified() {
    HttpRequest request = {
        HttpRequestMethod::GET,
        "static_test_files/index.html",
        "1.1",
        {{"If-Modified-Since", "Wed, 01 Oct 2100 08:12:31 GMT"}},
        ""
    };

    HttpResponse response = FileService::serveFile(request, request.path);
    if (response.status == HttpStatus::NOT_MODIFIED) {
        return 0;
    }

    std::cerr << "GET request expected NOT_MODIFIED, got: " 
        << ResponseSerializer::statusMethodToPhrase(response.status) << std::endl;
    return 1;
}

int getRequestOk() {
    HttpRequest request = {
        HttpRequestMethod::GET,
        "static_test_files/index.html",
        "1.1",
        {{"Host", "example.com"}, {"Connection", "close"}},
        ""
    };

    HttpResponse response = FileService::serveFile(request, request.path);
    if (response.status == HttpStatus::OK) {
        return 0;
    }

    std::cerr << "GET request expected OK, got: " 
        << ResponseSerializer::statusMethodToPhrase(response.status) << std::endl;
    return 1;
}

int headRequestWithUnsafePath() {
    HttpRequest request = {
        HttpRequestMethod::HEAD,
        "this/is/a/../unsafe/path",
        "1.1",
        {{"Host", "example.com"}, {"Connection", "close"}},
        ""    
    };

    HttpResponse response = FileService::serveFile(request, request.path);
    if (response.status == HttpStatus::FORBIDDEN) {
        return 0;
    }

    std::cerr << "HEAD request expected FORBIDDEN" << std::endl;
    return 1;
}

int headRequestWithNonExistantFile() {
    HttpRequest request = {
        HttpRequestMethod::HEAD,
        "this/is/a/missing/path",
        "1.1",
        {{"Host", "example.com"}, {"Connection", "close"}},
        ""    
    };

    HttpResponse response = FileService::serveFile(request, request.path);
    if (response.status == HttpStatus::NOT_FOUND) {
        return 0;
    }

    std::cerr << "HEAD request expected NOT_FOUND" << std::endl;
    return 1;
}

int headRequestNotModified() {
    HttpRequest request = {
        HttpRequestMethod::HEAD,
        "static_test_files/index.html",
        "1.1",
        {{"If-Modified-Since", "Wed, 01 Oct 2113 08:12:31 GMT"}},
        ""
    };

    HttpResponse response = FileService::serveFile(request, request.path);
    if (response.status == HttpStatus::NOT_MODIFIED) {
        std::cerr << "HEAD request should ignore If-Modified-Since header" << std::endl;
        return 1;
    }

    if (response.status != HttpStatus::OK) {
        std::cerr << "HEAD request expected OK, got: " <<
            ResponseSerializer::statusMethodToPhrase(response.status) << std::endl;
        return 1;
    }

    return 0;
}

int headRequestOk() {
    HttpRequest request = {
        HttpRequestMethod::HEAD,
        "static_test_files/index.html",
        "1.1",
        {{"Host", "example.com"}, {"Connection", "close"}},
        ""
    };

    HttpResponse response = FileService::serveFile(request, request.path);
    if (response.status == HttpStatus::OK && response.body.size() == 0) {
        return 0;
    }

    std::cerr << "HEAD request expected OK" << std::endl;
    return 1;
}

