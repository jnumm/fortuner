cmake_minimum_required(VERSION 3.1)
project(fortuner VERSION 0.6 LANGUAGES CXX)

find_package(Qt5 5.6 REQUIRED COMPONENTS Widgets LinguistTools)

add_executable(fortuner main.cpp trayicon.cpp trayicon.h)
set_target_properties(fortuner PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    AUTOMOC ON
    AUTORCC ON
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}"
    COMPILE_DEFINITIONS QT_DEPRECATED_WARNINGS
    LINK_LIBRARIES Qt5::Widgets)

if(NOT MSVC)
    target_compile_options(fortuner PRIVATE -Wall -Wextra -pedantic)
endif()

set(FORTUNER_QRESOURCE_ICON ${APPLE}${WIN32} CACHE BOOL
"Embed icon in executable. If this variable is false or not set, the icon is \
assumed to be available through a system icon theme.")

if(FORTUNER_QRESOURCE_ICON)
    target_sources(fortuner PRIVATE resources.qrc)
endif()

set(TRANSLATION_DIR "${CMAKE_INSTALL_PREFIX}/share/fortuner/translations")
qt5_add_translation(QM_FILES
    # Add fortuner_<lang>.ts files here.
)
target_sources(fortuner PRIVATE ${QM_FILES})

configure_file(config.h.in config.h)

install(TARGETS fortuner DESTINATION bin)
install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_DIR}")
install(DIRECTORY icons DESTINATION share)
install(FILES fortuner.desktop DESTINATION share/applications)
install(FILES fortuner.6 DESTINATION share/man/man6)
