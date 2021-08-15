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

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib)

if("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" STREQUAL "")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ".")
endif()
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(TOUCH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/__init__.py)

add_library(nlp_algorithm nlp_algorithm.cpp)

SET_SOURCE_FILES_PROPERTIES(nlp_algorithm.i PROPERTIES CPLUSPLUS ON)
swig_add_library(nlp_algorithm_swig
  TYPE SHARED
  LANGUAGE python
  OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
  SOURCES nlp_algorithm.i)

target_include_directories(nlp_algorithm_swig
  PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${Python_INCLUDE_DIRS}
)

swig_link_libraries(nlp_algorithm_swig nlp_algorithm)