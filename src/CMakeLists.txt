set(RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/dfa.txt)

add_executable(dfa ${CMAKE_CURRENT_SOURCE_DIR}/dfa.cpp ${RESOURCE_FILES})
target_include_directories(
  dfa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/finite_state_machine/)
target_link_libraries(dfa PRIVATE ${project_options} ${project_warnings})

add_executable(lambda_nfa ${CMAKE_CURRENT_SOURCE_DIR}/lambda_nfa.cpp
                          ${RESOURCE_FILES})
target_include_directories(
  lambda_nfa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/finite_state_machine/)
target_link_libraries(lambda_nfa PRIVATE ${project_options} ${project_warnings})
