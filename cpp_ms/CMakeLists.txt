# szg - cpp_ms library for lattice enumeration
cmake_minimum_required(VERSION 3.15)

message(STATUS "Building cpp_ms library")

# Create static library
add_library(cpp_ms STATIC)

# Source files
target_sources(cpp_ms PRIVATE
  ms_solve.cpp
)

# Headers - use generator expressions for export compatibility  
target_include_directories(cpp_ms PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Link dependencies
if(TARGET Eigen3::Eigen)
  target_link_libraries(cpp_ms PUBLIC Eigen3::Eigen)
  message(STATUS "Linked Eigen3 to cpp_ms")
endif()

if(FPLLL_FOUND AND FPLLL_LIBRARIES)
  target_link_libraries(cpp_ms PUBLIC ${FPLLL_LIBRARIES})
  message(STATUS "Linked FPLLL libraries: ${FPLLL_LIBRARIES}")
endif()

if(FPLLL_INCLUDE_DIRS)
  target_include_directories(cpp_ms PUBLIC 
    $<BUILD_INTERFACE:${FPLLL_INCLUDE_DIRS}>
  )
endif()

# Use C++17
target_compile_features(cpp_ms PRIVATE cxx_std_17)

# Disable warnings
if(UNIX)
  target_compile_options(cpp_ms PRIVATE -w -Wno-redundant-decls)
elseif(MSVC)
  target_compile_options(cpp_ms PRIVATE /w)
endif()

# Define the macro
target_compile_definitions(cpp_ms PUBLIC HIGHS_LATTICE_ENUM)

# Installation (single install command)
install(TARGETS cpp_ms
  EXPORT highs-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ms_solve.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

message(STATUS "cpp_ms target configured successfully")