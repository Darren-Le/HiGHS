# cpp_ms library for lattice enumeration
cmake_minimum_required(VERSION 3.15)

message(STATUS "Building cpp_ms library")
# Create static library
add_library(cpp_ms STATIC)

# Source files - just your original ms_solve.cpp
target_sources(cpp_ms PRIVATE
  ms_solve.cpp
)

message(STATUS "Added source files to cpp_ms")

# Headers
target_include_directories(cpp_ms PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Check if dependencies are available
if(BUILD_LATTICE_ENUM)
  # Link dependencies with error checking
  if(TARGET Eigen3::Eigen)
    target_link_libraries(cpp_ms PUBLIC Eigen3::Eigen)
    message(STATUS "Linked Eigen3 to cpp_ms")
  else()
    message(WARNING "Eigen3::Eigen target not found")
  endif()
  
  if(FPLLL_FOUND AND FPLLL_LIBRARIES)
    target_link_libraries(cpp_ms PUBLIC ${FPLLL_LIBRARIES})
    message(STATUS "Linked FPLLL libraries: ${FPLLL_LIBRARIES}")
  else()
    message(WARNING "FPLLL libraries not found")
  endif()
  
  # Include directories
  if(FPLLL_INCLUDE_DIRS)
    target_include_directories(cpp_ms PUBLIC ${FPLLL_INCLUDE_DIRS})
    message(STATUS "Added FPLLL include dirs: ${FPLLL_INCLUDE_DIRS}")
  endif()
endif()

# Use C++17 for cpp_ms (your original standard)
target_compile_features(cpp_ms PRIVATE cxx_std_17)

# Disable warnings
if(UNIX)
  target_compile_options(cpp_ms PRIVATE -w)
elseif(MSVC)
  target_compile_options(cpp_ms PRIVATE /w)
endif()

message(STATUS "cpp_ms target configured successfully")