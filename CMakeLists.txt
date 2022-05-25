cmake_minimum_required(VERSION 3.13.4)
project(dumb-trace)

# LLVM setup
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 14)

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# The instrumenter
add_executable(dumb-instrument 
    src/dumb-instrument.cpp 
)
llvm_map_components_to_libnames(llvm_libs support core irreader ipo)
target_link_libraries(dumb-instrument ${llvm_libs})

# The libdumb-trace.a
add_library(dumb-trace STATIC 
    src/dumb-trace.cpp
)

# The libdumb-hist.a
add_library(dumb-hist STATIC 
    src/dumb-hist.cpp
)