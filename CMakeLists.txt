cmake_minimum_required(VERSION 3.1)

project(fortuner)
set(FORTUNER_VERSION "0.6")

if (${CMAKE_VERSION} VERSION_LESS 3.8)
    set(CMAKE_CXX_STANDARD 14)
else()
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -pedantic)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

configure_file(config.h.in config.h)

set(fortuner_SRCS main.cpp trayicon.cpp trayicon.h)

find_package(Qt5Widgets REQUIRED)
add_executable(fortuner ${fortuner_SRCS})
target_link_libraries(fortuner Qt5::Widgets)
install(TARGETS fortuner DESTINATION bin)

install(DIRECTORY icons DESTINATION share)
install(FILES fortuner.desktop DESTINATION share/applications)
install(FILES fortuner.6 DESTINATION share/man/man6)
