cmake_minimum_required(VERSION 3.1)

project(fortuner)
set(FORTUNER_VERSION "0.6")

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

configure_file(config.h.in config.h)

set (fortuner_SRCS main.cpp trayicon.cpp trayicon.h)

find_package(Qt5Widgets REQUIRED)
add_executable(fortuner ${fortuner_SRCS})
target_link_libraries(fortuner Qt5::Widgets)
install(TARGETS fortuner DESTINATION bin)

file(GLOB icons "icons/*")
install(DIRECTORY ${icons} DESTINATION share/icons/hicolor)
install(FILES fortuner.desktop DESTINATION share/applications)
install(FILES fortuner.6 DESTINATION share/man/man6)
