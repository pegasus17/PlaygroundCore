cmake_minimum_required(VERSION 3.20)

# set the project name
project(cicd_core VERSION 1.0.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set (INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/package)
install(FILES LICENSE DESTINATION ${INSTALL_DIR})

# Core Library - Build
add_library(${PROJECT_NAME} SHARED
 src/cicd_logger.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Core Library - installs 
set (INSTALL_INLCUDES
  include/cicd_core.h
  include/cicd_logger.h
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR}/lib)
install(FILES ${INSTALL_INLCUDES} DESTINATION ${INSTALL_DIR}/include)
