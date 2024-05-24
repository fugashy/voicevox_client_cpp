find_package(GTest REQUIRED)

include_directories(
  include
)
include(GoogleTest)

message(STATUS "build test for ${PROJECT_NAME}")

set(TEST_NAMES request)
foreach(test_name IN LISTS TEST_NAMES)
  set(target ${PROJECT_NAME}_test_${test_name})
  message(STATUS "-- test: ${target}")
  add_executable(${target}
    test_${test_name}.cpp)
  target_link_libraries(${target}
    GTest::GTest GTest::Main
    ${PROJECT_NAME})
  gtest_discover_tests(${target})
endforeach()
