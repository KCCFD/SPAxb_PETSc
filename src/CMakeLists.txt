cmake_minimum_required(VERSION 3.20.3)


project(ddm_library)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

INCLUDE_DIRECTORIES(${PETSC_DIR}/lib/petsc/conf/variables)
INCLUDE_DIRECTORIES(${PETSC_DIR}/lib/petsc/conf/rules)

INCLUDE_DIRECTORIES(${PETSC_DIR}/include)

INCLUDE_DIRECTORIES(${PETSC_DIR}/${PETSC_ARCH}/include)

MESSAGE(STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})
MESSAGE(STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})
MESSAGE(STATUS "PETSC LIB : " ${PETSCLIB})
MESSAGE(STATUS "PETSC INCLUDE : " ${PETSCINC})

INCLUDE_DIRECTORIES(${PETSC_DIR}/)
ADD_DEFINITIONS(${PETSC_DEFINITIONS})

#find_package(MPI)
#include_directories(SYSTEM ${MPI_INCLUDE_PATH})


#file(GLOB SOURCES "../src/*.cpp" "${PETSC_DIR}/include/*.h")
file(GLOB SOURCES "../src/*.cpp")

add_executable(SPAxb ${SOURCES})

target_include_directories(SPAxb PRIVATE ${PETSCINC})


target_link_libraries(SPAxb ${MPI_C_LIBRARIES} ${PETSCLIB})
