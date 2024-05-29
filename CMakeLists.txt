cmake_minimum_required(VERSION 3.20)
project(ipc-benchmark CXX)

##########################################################################
# general settings
##########################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-fpermissive)

##########################################################################
# dependent packages
##########################################################################
include(FetchContent)
FetchContent_Declare(
	guutil
	GIT_REPOSITORY https://github.com/gunjae-yoon/guutil.git
	GIT_TAG v0.1.2
)
FetchContent_MakeAvailable(guutil)
#find_package(guutil REQUIRED)

message("==================================================")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "guutil: ${guutil_VERSION}")
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
	src/ipc-benchmark/base/performance.cpp
	src/ipc-benchmark/boost/shm_branch.cpp
	src/ipc-benchmark/boost/shm_trunk.cpp
)
add_dependencies(${TARGET_APP} GEN_TARGET)
target_include_directories(${TARGET_APP} PRIVATE
	include
	src
)
target_link_libraries(${TARGET_APP} PRIVATE
	guutil
)
