add_executable (cpp-console-2048 "cpp-console-2048.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cpp-console-2048 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
