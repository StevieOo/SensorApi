# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.25
cmake_policy(SET CMP0009 NEW)

# SensorApi_SOURCES at CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/steve/CIS566_Project/SensorApi/src/*.cpp")
set(OLD_GLOB
  "/home/steve/CIS566_Project/SensorApi/src/Aht10Driver.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/Aht10Humidity.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/Aht10Temperature.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/Configuration.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/Measurement.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/SensorFactory.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/SensorMonitor.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/Utils.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/WeatherData.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/WebApi.cpp"
  "/home/steve/CIS566_Project/SensorApi/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/steve/CIS566_Project/SensorApi/build/CMakeFiles/cmake.verify_globs")
endif()

# SensorApi_HEADERS at CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/steve/CIS566_Project/SensorApi/src/*.h")
set(OLD_GLOB
  "/home/steve/CIS566_Project/SensorApi/src/Aggregate.h"
  "/home/steve/CIS566_Project/SensorApi/src/Aht10Driver.h"
  "/home/steve/CIS566_Project/SensorApi/src/Aht10Humidity.h"
  "/home/steve/CIS566_Project/SensorApi/src/Aht10Temperature.h"
  "/home/steve/CIS566_Project/SensorApi/src/Configuration.h"
  "/home/steve/CIS566_Project/SensorApi/src/Iterator.h"
  "/home/steve/CIS566_Project/SensorApi/src/List.h"
  "/home/steve/CIS566_Project/SensorApi/src/ListIterator.h"
  "/home/steve/CIS566_Project/SensorApi/src/Measurement.h"
  "/home/steve/CIS566_Project/SensorApi/src/Sensor.h"
  "/home/steve/CIS566_Project/SensorApi/src/SensorFactory.h"
  "/home/steve/CIS566_Project/SensorApi/src/SensorMonitor.h"
  "/home/steve/CIS566_Project/SensorApi/src/Utils.h"
  "/home/steve/CIS566_Project/SensorApi/src/WeatherData.h"
  "/home/steve/CIS566_Project/SensorApi/src/WebApi.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/steve/CIS566_Project/SensorApi/build/CMakeFiles/cmake.verify_globs")
endif()