cmake_minimum_required(VERSION 3.19)
project(niudac_new LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Charts)

qt_standard_project_setup()


add_subdirectory(libs)
add_subdirectory(app)

#qt cmake scripts-----------------------------------------------------------------
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET niudac_new
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
# end of qt cmake scripts ------------------------------------------------------

# copping resources from working dir to build dir
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
set(DEST_DIR "${CMAKE_BINARY_DIR}/app")
file(COPY ${RESOURCE_DIR} DESTINATION ${DEST_DIR})
