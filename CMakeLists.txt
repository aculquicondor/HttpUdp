cmake_minimum_required(VERSION 3.0)
project(http_udp)

find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(ALL_FILES)
set(SERVER_PROXY_FILES
        server_proxy.cpp
        UdpServer.cpp UdpServer.h
        TcpClient.cpp TcpClient.h)
set(CLIENT_PROXY_FILES
        client_proxy.cpp
        TcpServer.cpp TcpServer.h
        UdpClient.cpp UdpClient.h UdpServer.cpp UdpServer.h)

add_executable(server_proxy ${ALL_FILES} ${SERVER_PROXY_FILES})
add_executable(client_proxy ${ALL_FILES} ${CLIENT_PROXY_FILES})

target_link_libraries(server_proxy ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(client_proxy ${CMAKE_THREAD_LIBS_INIT})
