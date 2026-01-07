cmake_minimum_required(VERSION 3.8)
project(more_interfaces)

# Compiler warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --------------------
# Find dependencies
# --------------------
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rosidl_default_runtime REQUIRED)

# --------------------
# Interface files
# --------------------
set(msg_files
  "msg/AddressBook.msg"
)

# Generate interfaces
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
)

# --------------------
# Node executable
# --------------------
add_executable(publish_address_book
  src/publish_address_book.cpp
)

ament_target_dependencies(publish_address_book
  rclcpp
)

# Link generated interfaces (ONLY because msg is in same package)
rosidl_target_interfaces(publish_address_book
  ${PROJECT_NAME}
  "rosidl_typesupport_cpp"
)

# --------------------
# Install
# --------------------
install(TARGETS
  publish_address_book
  DESTINATION lib/${PROJECT_NAME}
)

# --------------------
# Export runtime dependency
# --------------------
ament_export_dependencies(rosidl_default_runtime)

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
