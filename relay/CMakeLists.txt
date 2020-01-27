cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(relay VERSION 0.0.1 LANGUAGES CXX)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO)
else()
	add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)
endif()

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(relay
	src/main.cpp
)

target_include_directories(relay
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_compile_options(relay PRIVATE -Werror -Wall -Wextra -pedantic-errors)
target_compile_features(relay PUBLIC cxx_std_17)

# MarlinPubsub
include("${CMAKE_CURRENT_LIST_DIR}/cmake/marlin-pubsub.cmake")
target_link_libraries(relay PUBLIC Marlin::pubsub)

# MarlinBeacon
include("${CMAKE_CURRENT_LIST_DIR}/cmake/marlin-beacon.cmake")
target_link_libraries(relay PUBLIC Marlin::beacon)

# spdlog
include("${CMAKE_CURRENT_LIST_DIR}/cmake/spdlog.cmake")
target_link_libraries(relay PUBLIC spdlog::spdlog)