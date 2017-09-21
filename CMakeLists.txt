cmake_minimum_required(VERSION 2.8)

project(fortuner)

set(VER_MAJOR 0)
set(VER_MINOR 4)
set(VER_MICRO 0)
set(VERSION_STRING "${VER_MAJOR}.${VER_MINOR}.${VER_MICRO}")

install(FILES README DESTINATION share/doc/${PROJECT_NAME})
file(GLOB icons "icons/*")
install(DIRECTORY ${icons} DESTINATION share/icons/hicolor)
install(FILES misc/fortuner.desktop DESTINATION share/applications)
install(FILES doc/fortuner.6 DESTINATION share/man/man6)

set(LOCALEDIR "${CMAKE_INSTALL_PREFIX}/share/locale")

option(
  USE_GETTEXT
  "Use GNU Gettext for i18n. Disable for no translation."
  ON
)

add_subdirectory(src)
