cmake_minimum_required (VERSION 3.8)

project("networking")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "socket.cpp" "packet.h")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)