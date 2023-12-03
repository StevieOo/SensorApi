cmake_minimum_required(VERSION 3.15)

project(SensorApi)

find_package(Boost 1.40.0 REQUIRED)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

file (GLOB_RECURSE SensorApi_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE SensorApi_HEADERS CONFIGURE_DEPENDS "src/*.h")

set(LIB_PATHS ../crow/include)

set(SensorApi_Files ../crow/include)

foreach (_headerFile ${SensorApi_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND SensorApi_Files ${_dir})
endforeach()

list (REMOVE_DUPLICATES SensorApi_Files)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

add_executable(SensorApi ${SensorApi_SOURCES})
target_compile_options (SensorApi PUBLIC "-pthread")
target_link_libraries (SensorApi pthread)
target_include_directories (SensorApi PUBLIC ${LIB_PATHS})
