cmake_minimum_required(VERSION 3.14)
project(PlacesAPI VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CURL_USE_STATIC_LIBS ON)

include_directories(src/headers)
file(GLOB SOURCES "src/*.c")

find_package(CURL REQUIRED)
add_executable(PlacesAPI ${SOURCES})
target_link_libraries(PlacesAPI PRIVATE CURL::libcurl)
