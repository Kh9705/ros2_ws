cmake_minimum_required(VERSION 3.8)
project(polygon_plugins)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --------------------
# Dependencies
# --------------------
find_package(ament_cmake REQUIRED)
find_package(polygon_base REQUIRED)
find_package(pluginlib REQUIRED)

# --------------------
# Plugin library
# --------------------
add_library(polygon_plugins SHARED
  src/polygon_plugins.cpp
)

target_include_directories(polygon_plugins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(
  polygon_plugins
  polygon_base
  pluginlib
)

# --------------------
# Plugin description
# --------------------
pluginlib_export_plugin_description_file(
  polygon_base
  plugins.xml
)

# --------------------
# Install
# --------------------
install(
  TARGETS polygon_plugins
  LIBRARY DESTINATION lib
)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  FILES plugins.xml
  DESTINATION share/${PROJECT_NAME}
)

# --------------------
# Testing
# --------------------
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
