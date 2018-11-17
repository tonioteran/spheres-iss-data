cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH ../bin)

file( GLOB SRC_FILES "./*.cpp" "./*.h" "./*.hpp" )

add_executable( StereoFrame stereoFrame.cpp )
target_link_libraries( StereoFrame
  ${PCL_LIBRARIES})
