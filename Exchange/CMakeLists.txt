cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(PROJ_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PROJ_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROJ_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

include_directories(${PROJ_INC_DIR}
                    ${PROJ_TEST_DIR})
#link_directories(${gtest_LIB_DIRS})
add_executable(Exchange ${PROJ_SRC_DIR}/main.cc ${PROJ_SRC_DIR}/RequestReader.cc
               ${PROJ_SRC_DIR}/OrderReceiver.cc
               ${PROJ_SRC_DIR}/OrderBook.cc
               ${PROJ_SRC_DIR}/OrderBookMgr.cc
               ${PROJ_SRC_DIR}/Error.cc

              )
