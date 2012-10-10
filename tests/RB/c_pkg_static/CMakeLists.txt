#
# File: c_pkg_static/CMakeLists.txt
# Test: package of resource bundles as static library
#

cmake_minimum_required(VERSION 2.8.3) # inherit FindICU.cmake

set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../../..)

find_package(ICU COMPONENTS i18n io REQUIRED)

add_definitions(-DURESNAME="rb")
include_directories(${ICU_INCLUDE_DIRS})
add_executable(rb ../rb.c)
set_target_properties(rb PROPERTIES ENABLE_EXPORTS TRUE)
install(TARGETS rb DESTINATION bin)
target_link_libraries(rb ${ICU_LIBRARIES})

generate_icu_resource_bundle(
    PACKAGE rb
    TYPE static
    # DESTINATION has no sense
    DEPENDS rb # add_executable
    FILES ../root.txt ../fr/fr.txt ../es/es.txt ../es/es_ES.txt
)
