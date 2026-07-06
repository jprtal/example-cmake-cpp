if(FOO_WITH_TESTS)

  # Function to add a test
  function(add_project_test NAME SOURCE)
    add_executable(${NAME} ${SOURCE})
    target_include_directories(${NAME}
      PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
    )
    target_link_libraries(${NAME} PRIVATE
      ${PROJECT_NAME}
      Catch2::Catch2WithMain
    )
    add_test(NAME ${NAME} COMMAND ${NAME})
    catch_discover_tests(${NAME})

    # Create all tests target
    if(NOT TARGET ${PROJECT_NAME}_all_tests)
      add_custom_target(${PROJECT_NAME}_all_tests)
    endif()

    # Add test to global tests target
    add_dependencies(${PROJECT_NAME}_all_tests ${NAME})
  endfunction()

  # Add tests
  add_project_test(test_json_utils test_json_utils.cpp)

endif()
