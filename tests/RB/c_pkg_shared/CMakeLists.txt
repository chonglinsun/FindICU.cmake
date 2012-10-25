#
# File: c_pkg_shared/CMakeLists.txt
# Test: package of resource bundles as shared library
#

cmake_minimum_required(VERSION 2.8.3) # inherit FindICU.cmake

set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../../..)

find_package(ICU COMPONENTS i18n io REQUIRED)

add_definitions(-DURESNAME=bar)
include_directories(${ICU_INCLUDE_DIRS})
add_executable(rb ../rb.c)
install(TARGETS rb DESTINATION bin)
target_link_libraries(rb ${ICU_LIBRARIES})
set_target_properties(rb PROPERTIES COMPILE_FLAGS "-fPIC")

generate_icu_resource_bundle(
    PACKAGE bar
    TYPE library
    DESTINATION bin # share the same directory with the binary
    DEPENDS rb # add_executable
    FILES ../root.txt ../fr/fr.txt ../es/es.txt ../es/es_ES.txt
)
