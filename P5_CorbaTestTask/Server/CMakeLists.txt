cmake_minimum_required(VERSION 3.1)

project(Server)


include(${PROJECT_SOURCE_DIR}/../../config/build/CORBA.cmake)
include(${PROJECT_SOURCE_DIR}/../../config/build/outputs.cmake)


include_directories(${CORBA_INCLUDE})

find_package(Boost COMPONENTS chrono system thread REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
                      Common
                      ${CORBA_LINK}
                      ${Boost_LIBRARIES}
                      Threads::Threads)

