#include "utils.h"


std::string getLine(int fd) {
    std::string line;
    char c;
    while (read(fd, &c, 1) > 0) {
        line.push_back(c);
        if (c == '\n')
            break;
    }
    return line;
}


std::string lower(std::string str) {
    for (char &c : str) {
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
    }
    return str;
}


std::size_t from_hexadecimal(std::string str) {
    std::size_t r = 0;
    for (char c : lower(str)) {
        if (c == '\r' or c == '\n')
            break;
        r = r * 16 + (c <= '9' ? c - '0' : c - 'a');
    }
    return r;
}


std::string to_10_digit_string(std::size_t size) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(10);
    ss << size;
    return ss.str();
}


std::string httpRead(int socket) {
    std::string content, line;
    std::size_t contentLength = 0;
    bool chunked = false;
    do {
        line = getLine(socket);
        content += line;
        std::size_t colon = line.find(':');
        if (colon != line.size()) {
            std::string header = line.substr(0, colon);
            if (lower(header) == "content-length") {
                std::stringstream ss(line.substr(colon + 1));
                ss >> contentLength;
            } else if (lower(header) == "transfer-encoding") {
                chunked = true;
            }
        }
    } while (line != "\n" and line != "\r\n");

    if (contentLength > 0) {
        line.resize(contentLength);
        read(socket, &line[0], contentLength);
        content += line;
    } else if (chunked) {
        while (true) {
            line = getLine(socket);
            content += line;
            contentLength = from_hexadecimal(line);
            if (contentLength == 0)
                break;
            line.resize(contentLength);
            read(socket, &line[0], contentLength);
            content += line;
        }
    }
    return content;
}

