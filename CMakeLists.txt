cmake_minimum_required(VERSION 3.26)
project(MIRSU)

set(CMAKE_CXX_STANDARD 17)


#---------------------------------------------------------------------------------------------------
# Sources
#---------------------------------------------------------------------------------------------------
set(MIRSU_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(MIRSU_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/source)

set(MIRSU__SOURCES
        ${MIRSU_SOURCE_DIR}/main.cpp
        ${MIRSU_SOURCE_DIR}/blocks/gain.cpp
        ${MIRSU_SOURCE_DIR}/blocks/integrator.cpp
        ${MIRSU_SOURCE_DIR}/ControlObject3D.cpp
        ${MIRSU_SOURCE_DIR}/ControlObject3DDiscrete.cpp
)

#---------------------------------------------------------------------------------------------------
# Executable
#---------------------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${MIRSU__SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${MIRSU_INCLUDE_DIR})

