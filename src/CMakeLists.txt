cmake_minimum_required(VERSION 2.8)

project(fortuner)

set(CMAKE_CXX_STANDARD 14)

set(fortuner_SRCS
  aboutdialog.cpp
  fortuner.cpp
  main.cpp
  settings.cpp
  statusicon.cpp
)

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

if(USE_GETTEXT)
  find_package(Gettext)
  add_definitions(-DENABLE_NLS)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

pkg_check_modules(LIBNOTIFY REQUIRED libnotify)

include_directories(
  ${PROJECT_BINARY_DIR}
  ${GTKMM_INCLUDE_DIRS}
  ${LIBNOTIFY_INCLUDE_DIRS}
)
link_directories(${GTKMM_LIBRARY_DIRS} ${LIBNOTIFY_LIBRARY_DIRS})
add_executable(${PROJECT_NAME} ${fortuner_SRCS})
add_definitions(${GTKMM_CFLAGS_OTHER} ${LIBNOTIFY_CFLAGS_OTHER})
target_link_libraries(
  ${PROJECT_NAME}
  ${GTKMM_LIBRARIES}
  ${LIBNOTIFY_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
