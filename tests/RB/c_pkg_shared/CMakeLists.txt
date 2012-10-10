#
# File: c_pkg_library/CMakeLists.txt
# Test: package of resource bundles as shared library
#

cmake_minimum_required(VERSION 2.8.3) # inherit FindICU.cmake

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
    TYPE library
    DESTINATION bin # share the same directory with the binary
    DEPENDS rb # add_executable
    FILES ../root.txt ../fr/fr.txt ../es/es.txt ../es/es_ES.txt
)
