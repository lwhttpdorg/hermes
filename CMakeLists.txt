cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(Hermes VERSION 1.0.0 LANGUAGES CXX)

option(COMPILE_BASE64 "Compile the Base64 encoding/decoding library" ON)
option(COMPILE_URL "Compile the URL encoding/decoding library" ON)

set(HERMES_SRCS)

if(COMPILE_BASE64)
	file(GLOB BASE64_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/base64/*.cpp")
	list(APPEND HERMES_SRCS ${BASE64_SRCS})
endif()

if(COMPILE_URL)
	file(GLOB URL_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/url/*.cpp")
	list(APPEND HERMES_SRCS ${URL_SRCS})
endif()

add_library(hermes SHARED ${HERMES_SRCS})
target_compile_features(hermes PUBLIC cxx_std_11)

target_include_directories(hermes PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/base64>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/url>
		$<INSTALL_INTERFACE:include/hermes>
)
