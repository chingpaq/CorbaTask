cmake_minimum_required(VERSION 3.1)

project(Common)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


include(${PROJECT_SOURCE_DIR}/../../config/build/CORBA.cmake)
include(${PROJECT_SOURCE_DIR}/../../config/build/IDL.cmake)
include(${PROJECT_SOURCE_DIR}/../../config/build/outputs.cmake)


include_directories(${PROJECT_SOURCE_DIR}/include
                    ${IDL_OUT_DIR}
                    ${CORBA_INCLUDE})

file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES}
                            ${IDL_OUTPUTS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include
                                                  ${IDL_OUT_DIR})

