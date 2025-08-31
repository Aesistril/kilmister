# pkg-config packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(LIBADWAITA REQUIRED libadwaita-1)
pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(CJSON REQUIRED libcjson)
pkg_check_modules(LIBSECRET REQUIRED libsecret-1)
pkg_check_modules(LIBCONFIG REQUIRED libconfig)

include_directories(
    ${GTK4_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${LIBADWAITA_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
    ${CJSON_INCLUDE_DIRS}
    ${LIBSECRET_INCLUDE_DIRS}
    ${LIBCONFIG_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

link_directories(
    ${GTK4_LIBRARY_DIRS}
    ${GLIB_LIBRARY_DIRS}
    ${LIBADWAITA_LIBRARY_DIRS}
    ${CURL_LIBRARY_DIRS}
    ${CJSON_LIBRARY_DIRS}
    ${LIBCONFIG_LIBRARY_DIRS}
    ${LIBSECRET_LIBRARY_DIRS}
)

add_definitions(
    ${GTK4_CFLAGS_OTHER}
    ${GLIB_CFLAGS_OTHER}
    ${LIBADWAITA_CFLAGS_OTHER}
    ${CURL_CFLAGS_OTHER}
    ${CJSON_CFLAGS_OTHER}
    ${LIBSECRET_CFLAGS_OTHER}
    ${LIBCONFIG_CFLAGS_OTHER}
)

set(SOURCES
    src/main.c
    src/creds.c
    src/config.c
    src/import_ui.c
    src/signals_gui.c
    src/api/request.c
    src/api/v3/auth.c
    src/api/v4/auth.c
)

add_executable(Kilmister ${SOURCES})

target_link_libraries(Kilmister
    ${GTK4_LIBRARIES}
    ${GLIB_LIBRARIES}
    ${LIBADWAITA_LIBRARIES}
    ${CURL_LIBRARIES}
    ${CJSON_LIBRARIES}
    ${LIBSECRET_LIBRARIES}
    ${LIBCONFIG_LIBRARIES}
)

# Copy UI files
file(COPY src/ui DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
