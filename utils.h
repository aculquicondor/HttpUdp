#ifndef HTTP_UDP_UTILS_H
#define HTTP_UDP_UTILS_H

#include <string>
#include <sstream>
#include <iomanip>

#include <unistd.h>


extern std::string getLine(int fd);

extern std::string lower(std::string str);

extern std::size_t from_hexadecimal(std::string str);

extern std::string httpRead(int socket);

extern std::string to_10_digit_string(std::size_t size);

#endif //HTTP_UDP_UTILS_H
