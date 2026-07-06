# Define public headers
set(FOO_PUBLIC_HEADERS
  json_utils.h
)

# if(BarOpt_FOUND AND FOO_USE_BAROPT)
#   list(APPEND FOO_PUBLIC_HEADERS bar/mathbar.h)
# endif()

# Create the includes strings for the unified header
set(HEADER_INCLUDES "")
foreach(header ${FOO_PUBLIC_HEADERS})
  string(APPEND HEADER_INCLUDES "#include <${PROJECT_NAME_LOWER}/${header}>\n")
endforeach()

# Generate the unified header
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/unified_header.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}.h"
)

# Get the current Git commit for the version header
find_package(Git)
if(Git_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} --no-pager log -n 1 HEAD "--pretty=format:%h"
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    RESULT_VARIABLE git_result
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(git_result EQUAL 0)
    message(STATUS "Last ${PROJECT_NAME} Git commit: ${GIT_COMMIT_HASH}")
  endif()
endif()

# Generate the version header
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
)

# Define source files
set(FOO_SOURCES
  json_utils.cpp
)

# Create the target
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Generate export header
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

# Add sources to the target
target_sources(${PROJECT_NAME}
  PRIVATE
    ${FOO_SOURCES}
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS
      ${PROJECT_SOURCE_DIR}
    FILES
      ${FOO_PUBLIC_HEADERS}
)

# Add generated sources to the target
target_sources(${PROJECT_NAME}
  PUBLIC
    FILE_SET public_headers_generated
    TYPE HEADERS
    BASE_DIRS
      ${PROJECT_BINARY_DIR}
    FILES
      # Generated headers
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}.h
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME_LOWER}_export.h
      ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

# Add compile definitions
target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    # $<$<BOOL:${FOO_WITH_SOME_FLAG}>:FOO_WITH_SOME_FLAG>
  PRIVATE
    $<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:DEBUG>
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    nlohmann_json::nlohmann_json
  PRIVATE
    # "$<$<BOOL:${FOO_USE_BAR}>:Bar::Bar>"
)
