cmake_minimum_required(VERSION 3.15)

project(SensorApi)

file (GLOB_RECURSE SensorApi_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE SensorApi_HEADERS CONFIGURE_DEPENDS "src/*.h")

set(LIB_PATHS ../boost_1_83_0/ ../crow/include)

set(SensorApi_Files ../boost_1_83_0/ ../crow/include)

foreach (_headerFile ${SensorApi_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND SensorApi_Files ${_dir})
endforeach()

list (REMOVE_DUPLICATES SensorApi_Files)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

add_executable(SensorApi ${SensorApi_SOURCES})
target_include_directories (SensorApi PUBLIC ${LIB_PATHS})
