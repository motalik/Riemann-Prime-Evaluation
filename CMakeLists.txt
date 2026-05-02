cmake_minimum_required(VERSION 3.10)
project(RiemannAnalysis)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-D_USE_MATH_DEFINES)

find_package(Boost REQUIRED COMPONENTS math)
find_package(OpenMP REQUIRED)
find_path(MPFR_INCLUDE_DIR NAMES mpfr.h)
find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(MPFR_LIB mpfr REQUIRED)
find_library(GMP_LIB gmp REQUIRED)

set(INCLUDE_DIRS
    include
    ${MPFR_INCLUDE_DIR}
    ${GMP_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

set(LIBS
    m
    ${MPFR_LIB}
    ${GMP_LIB}
    Boost::boost
    Boost::math
)

add_executable(TrovaZeri
    src/main.cpp
    src/zeta_logic.cpp
)
target_include_directories(TrovaZeri PRIVATE ${INCLUDE_DIRS})
target_link_libraries(TrovaZeri PRIVATE ${LIBS})
target_compile_options(TrovaZeri PRIVATE -O3 -march=native)

add_executable(TrovaPrimi
    src/main_primes.cpp
    src/prime_logic.cpp
    src/zeta_logic.cpp
)
target_include_directories(TrovaPrimi PRIVATE ${INCLUDE_DIRS})
target_link_libraries(TrovaPrimi PRIVATE ${LIBS})
target_compile_options(TrovaPrimi PRIVATE -O3 -march=native)
