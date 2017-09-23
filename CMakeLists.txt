cmake_minimum_required(VERSION 3.1)

project(fortuner VERSION 0.6 LANGUAGES CXX)

if (${CMAKE_VERSION} VERSION_LESS 3.8)
    set(CMAKE_CXX_STANDARD 14)
else()
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-DQT_DEPRECATED_WARNINGS -Wall -Wextra -pedantic)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(TRANSLATION_DIR ${CMAKE_INSTALL_PREFIX}/share/fortuner/translations)

configure_file(config.h.in config.h)

set(fortuner_SRCS main.cpp trayicon.cpp trayicon.h)
set(TS_FILES)

find_package(Qt5Widgets 5.6 REQUIRED)
find_package(Qt5LinguistTools)

qt5_add_translation(QM_FILES ${TS_FILES})

add_executable(fortuner ${fortuner_SRCS} ${QM_FILES})
target_link_libraries(fortuner Qt5::Widgets)

install(TARGETS fortuner DESTINATION bin)
install(FILES ${QM_FILES} DESTINATION ${TRANSLATION_DIR})
install(DIRECTORY icons DESTINATION share)
install(FILES fortuner.desktop DESTINATION share/applications)
install(FILES fortuner.6 DESTINATION share/man/man6)
