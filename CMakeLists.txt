cmake_minimum_required(VERSION 3.9)
project(Library_Max)

set(CMAKE_CXX_STANDARD 11)

add_executable(Library_Max
        Book.cpp
        Book.h
        Item.cpp
        Item.h
        Library.cpp
        Library.h
        Movie.cpp
        Movie.h
        MusicAlbum.cpp
        MusicAlbum.h
        mycpplibrary.cpp)
