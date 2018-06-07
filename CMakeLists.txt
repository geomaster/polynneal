cmake_minimum_required(VERSION 2.6)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(polynneal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
add_executable("polynneal"
    src/main.cpp
    src/gui.cpp
    src/line_shape.cpp
    src/polynneal.cpp
)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Detect and add SFML
find_package(SFML 2 REQUIRED network audio graphics window system)
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries("polynneal" ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Detect and add CGAL
find_package(CGAL REQUIRED)
if (CGAL_FOUND)
  include_directories(${CGAL_INCLUDE_DIR})
  target_link_libraries("polynneal" ${CGAL_LIBRARIES})
endif()

# Detect and add GMP
find_package(GMP REQUIRED)
if (GMP_FOUND)
  include_directories(${GMP_INCLUDE_DIR})
  target_link_libraries("polynneal" ${GMP_LIBRARIES})
endif()

# Detect and add MPFR
find_package(MPFR REQUIRED)
if (MPFR_FOUND)
  include_directories(${MPFR_INCLUDE_DIR})
  target_link_libraries("polynneal" ${MPFR_LIBRARIES})
endif()

# Install target
install(TARGETS "polynneal" DESTINATION bin)
