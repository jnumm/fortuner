cmake_minimum_required(VERSION 3.1)
project(fortuner VERSION 0.6 LANGUAGES CXX)

find_package(Qt5Widgets 5.6 REQUIRED)
find_package(Qt5LinguistTools)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_WIN32_EXECUTABLE ON)
set(CMAKE_MACOSX_BUNDLE ON)

add_definitions(-DQT_DEPRECATED_WARNINGS)
if(NOT MSVC)
    add_compile_options(-Wall -Wextra -pedantic)
endif()

set(FORTUNER_QRESOURCE_ICON ${APPLE}${WIN32} CACHE BOOL
"Embed icon in executable. If this variable is false or not set, the icon is \
assumed to be available through a system icon theme.")

if(FORTUNER_QRESOURCE_ICON)
    set(QRC_FILES resources.qrc)
endif()

set(TS_FILES)
set(TRANSLATION_DIR ${CMAKE_INSTALL_PREFIX}/share/fortuner/translations)
qt5_add_translation(QM_FILES ${TS_FILES})

configure_file(config.h.in config.h)

add_executable(fortuner main.cpp trayicon.cpp trayicon.h ${QRC_FILES} ${QM_FILES})
target_link_libraries(fortuner Qt5::Widgets)

install(TARGETS fortuner DESTINATION bin)
install(FILES ${QM_FILES} DESTINATION ${TRANSLATION_DIR})
install(DIRECTORY icons DESTINATION share)
install(FILES fortuner.desktop DESTINATION share/applications)
install(FILES fortuner.6 DESTINATION share/man/man6)
