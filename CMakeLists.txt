cmake_minimum_required(VERSION 3.16)
project(BookStore2021)

set(CMAKE_CXX_STANDARD 14)

add_executable(code
        main.cpp
        account.cpp
        command.cpp
        blocklist.cpp
        parser.cpp
        log.cpp
        book.cpp
        )
