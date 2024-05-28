cmake_minimum_required(VERSION 3.20)
project(ipc-benchmark CXX)

##########################################################################
# general settings
##########################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-fpermissive)

message("==================================================")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message("==================================================")


##########################################################################
# build application
##########################################################################
set(TARGET_APP "ipc-benchmark")
set(GEN_SRC
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h
	${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/version.cpp
)
add_custom_command(
	OUTPUT ${GEN_SRC}
	COMMAND bash "${PROJECT_SOURCE_DIR}/script/version.sh"
	COMMENT "Try to update version"
)
add_custom_target(GEN_TARGET DEPENDS ${GEN_SRC})
add_executable(${TARGET_APP}
	${GEN_SRC}
	src/main.cpp
)
add_dependencies(${TARGET_APP} GEN_TARGET)
target_include_directories(${TARGET_APP} PRIVATE
	include
	src
)
