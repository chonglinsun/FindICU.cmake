#
# File: c_pkg_shared/CMakeLists.txt
# Test: package of resource bundles as shared library
#

cmake_minimum_required(VERSION 2.8.3) # inherit FindICU.cmake

project(rb C)

# set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../../..)

# set(ICU_DEBUG TRUE)
find_package(ICU COMPONENTS i18n io REQUIRED)

add_definitions(-DURESNAME=bar -DURES_SHARED)
include_directories(${ICU_INCLUDE_DIRS})
add_executable(rb ../rb.c)
install(TARGETS rb DESTINATION bin)
target_link_libraries(rb ${ICU_LIBRARIES})
set_target_properties(rb PROPERTIES COMPILE_FLAGS "-fPIC")

# To choose between ICU_C_SHARED_FLAGS and ICU_CXX_SHARED_FLAGS
get_property(ENABLED_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)
message("ENABLED_LANGUAGES = ${ENABLED_LANGUAGES}")
list(LENGTH "${ENABLED_LANGUAGES}" ENABLED_LANGUAGES_LENGTH)
if(ENABLED_LANGUAGES_LENGTH GREATER 1)
    message(WARNING "Project has more than one language enabled")
endif(ENABLED_LANGUAGES_LENGTH GREATER 1)
message("ICU_${ENABLED_LANGUAGES}_SHARED_FLAGS = ${ICU_${ENABLED_LANGUAGES}_SHARED_FLAGS}")


generate_icu_resource_bundle(
    PACKAGE bar
    TYPE library
    DESTINATION bin # share the same directory with the binary
    DEPENDS rb # add_executable
    FILES ../root.txt ../fr/fr.txt ../es/es.txt ../es/es_ES.txt
)
