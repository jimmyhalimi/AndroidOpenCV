cmake_minimum_required(VERSION 3.5)
project(readFrame)

###########
## Build ##
###########

message(STATUS ${GTEST_INCLUDE_DIRS})
message(STATUS ${GTEST_BOTH_LIBRARIES})

include_directories(
  include/opencv/include
)

#The toolchain builds for armeabi-v7a
add_library(opencv SHARED IMPORTED)
# set_target_properties(opencv PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/arm64-v8a/libopencv_java3.so)
set_target_properties(opencv PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/armeabi-v7a/libopencv_java3.so)
# set_target_properties(opencv PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/x86/libopencv_java3.so)
# set_target_properties(opencv PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/x86_64/libopencv_java3.so)

# add_executable(Driver_Test
#   src/main.cpp
# )

# set lib to build itself
add_library(
  ${PROJECT_NAME} SHARED
  src/readFrame.cpp
)

target_include_directories( ${PROJECT_NAME} PRIVATE 
  opencv/include
)

target_link_libraries( ${PROJECT_NAME}
  opencv
)

#############
## TESTING ##
#############

#add_subdirectory(test)

#############
## Install ##
#############

# to be discussed, we want to expose data types only!
install(
  TARGETS ${PROJECT_NAME} EXPORT SoundProcessing-config
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

## install headers
install(
  DIRECTORY include/DSPFilters
  DESTINATION include/SoundProcessing/
  PATTERN "CMakeLists.txt" EXCLUDE
)
