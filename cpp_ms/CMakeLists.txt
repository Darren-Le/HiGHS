# cpp_ms library for lattice enumeration
cmake_minimum_required(VERSION 3.15)

# Create static library
add_library(cpp_ms STATIC)

# Source files - just your original ms_solve.cpp
target_sources(cpp_ms PRIVATE
  ms_solve.cpp
)

# Headers
target_include_directories(cpp_ms PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies
target_link_libraries(cpp_ms PUBLIC
  Eigen3::Eigen
  ${FPLLL_LIBRARIES}
)

# Include directories
target_include_directories(cpp_ms PUBLIC 
  ${FPLLL_INCLUDE_DIRS}
)

# Compiler options
target_compile_options(cpp_ms PUBLIC 
  ${FPLLL_CFLAGS_OTHER}
)

# Use C++17 for cpp_ms (your original standard)
target_compile_features(cpp_ms PRIVATE cxx_std_17)

# Disable warnings
if(UNIX)
  target_compile_options(cpp_ms PRIVATE -w)
elseif(MSVC)
  target_compile_options(cpp_ms PRIVATE /w)
endif()

# Define the macro
target_compile_definitions(cpp_ms PUBLIC HIGHS_HAVE_LATTICE_ENUM)