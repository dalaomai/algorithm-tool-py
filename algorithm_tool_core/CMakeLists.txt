cmake_minimum_required(VERSION 3.8)
project(algorithm-tool)

# SWIG: use standard target name.
if(POLICY CMP0078)
  cmake_policy(SET CMP0078 NEW)
endif()

# SWIG: use SWIG_MODULE_NAME property.
if(POLICY CMP0086)
  cmake_policy(SET CMP0086 NEW)
endif()

find_package(SWIG 4.0 COMPONENTS python REQUIRED)
if(SWIG_FOUND)
  message("SWIG found: ${SWIG_EXECUTABLE}")
endif()
include (UseSWIG)

find_package(Python COMPONENTS Interpreter Development)
if(Python_FOUND)
  message("python found: ${Python_LIBRARIES}")
endif()

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

add_library(ltest test.cpp)

SET_SOURCE_FILES_PROPERTIES(test.i PROPERTIES CPLUSPLUS ON)
swig_add_library(test
  TYPE SHARED
  LANGUAGE python
  OUTPUT_DIR ${LIBRARY_OUTPUT_PATH}
  SOURCES test.i)

target_include_directories(test
  PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${Python_INCLUDE_DIRS}
)

swig_link_libraries(test ltest)