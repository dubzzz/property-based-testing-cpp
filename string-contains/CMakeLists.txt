set(PROJECT_NAME string-contains)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} rapidcheck)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

