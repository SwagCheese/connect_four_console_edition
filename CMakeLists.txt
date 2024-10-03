cmake_minimum_required(VERSION 3.29)
project(connect_four_console_edition)

set(CMAKE_CXX_STANDARD 20)

add_executable(connect_four_console_edition main.cpp
        classes/ai/ai.h
        classes/player/player.h
        classes/ai/ai.cpp
        classes/bitboard/bitboard.cpp
        classes/bitboard/bitboard.h)
