cmake_minimum_required(VERSION 3.10)

project(voicevox_client_cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

set(cpprestsdk_LIBRARIES cpprestsdk::cpprest)

include_directories(
  include
)

add_library(${PROJECT_NAME} SHARED
  src/${PROJECT_NAME}/client.cpp
)
target_link_libraries(${PROJECT_NAME}
  ${cpprestsdk_LIBRARIES}
  ${OPENSSL_LIBRARIES}  # to avoid linker error
)
install(
  TARGETS
    ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# samples
set(SAMPLE_NAMES
  get_speakers
  get_version
  get_core_versions
)
foreach(sample_name IN LISTS SAMPLE_NAMES)
  add_executable(${PROJECT_NAME}_sample_${sample_name}
    src/${PROJECT_NAME}/sample/${sample_name}.cpp
  )
  target_link_libraries(${PROJECT_NAME}_sample_${sample_name}
    ${PROJECT_NAME}
  )
  install(
    TARGETS
      ${PROJECT_NAME}_sample_${sample_name}
    EXPORT ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
  )
endforeach()


#
# add_executable(${PROJECT_NAME}_use_simple_class
#   src/${PROJECT_NAME}/use_simple_class.cpp
# )
# target_link_libraries(${PROJECT_NAME}_use_simple_class
#   ${CMAKE_DL_LIBS}
# )
# install(
#   TARGETS
#     ${PROJECT_NAME}_use_simple_class
#   EXPORT ${PROJECT_NAME}
#   ARCHIVE DESTINATION lib
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION bin
#   INCLUDES DESTINATION include
# )
# if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#   set_target_properties(${PROJECT_NAME}_use_simple_class
#     PROPERTIES INSTALL_RPATH "@executable_path/../lib")
# endif()
#
# install(
#   DIRECTORY include/
#   DESTINATION include)
