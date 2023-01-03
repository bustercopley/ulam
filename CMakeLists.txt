cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    ulam
    VERSION 0.1.0
    DESCRIPTION "Ulam spiral rotated by 45 degrees"
    HOMEPAGE_URL "https://buster.me.uk/"
    LANGUAGES CXX
)

include(cmake/variables.cmake)

find_package(PNG REQUIRED)

# ---- Declare executable ----

add_executable(ulam_exe
  source/main.cpp
  source/write_png.cpp
)
add_executable(ulam::exe ALIAS ulam_exe)

set_property(TARGET ulam_exe PROPERTY OUTPUT_NAME ulam)

target_compile_features(ulam_exe PRIVATE cxx_std_20)
target_link_libraries(ulam_exe PRIVATE PNG::PNG)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT ulam_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of ulam"
  )
endif()

include(cmake/dev-mode.cmake)
