add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_include_directories(
  ${CMAKE_PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/finite_state_machine/)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${project_options}
                                                    ${project_warnings})
