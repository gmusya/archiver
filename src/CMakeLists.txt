cmake_minimum_required(VERSION 3.16)
project(archiver)

set(CMAKE_CXX_STANDARD 20)

add_executable(archiver main.cpp trie.cpp reader.cpp encoder.cpp vertex.cpp argument_parser.cpp writer.cpp decoder.cpp util.cpp priority_queue.cpp node.cpp)
