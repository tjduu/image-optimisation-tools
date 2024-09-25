file(GLOB TESTS_FILES *.cpp)
add_executable(runTests ${TESTS_FILES})
target_link_libraries(runTests PRIVATE core_lib)