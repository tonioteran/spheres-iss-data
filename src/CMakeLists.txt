project( spheres-iss-data )
cmake_minimum_required(VERSION 2.8)

###########
# Enable C++ 2011 support
set (CMAKE_CXX_STANDARD 11)
# For PCL source installation (/usr/local/include)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

###########
# Eigen
###########
find_package( Eigen3 REQUIRED )
include_directories(${EIGEN3_INCLUDE_DIR})

###########
# PCL
###########
set(pclEnabled on)
if(pclEnabled)
	find_package(PCL 1.8 REQUIRED)
	include_directories(${PCL_INCLUDE_DIRS})
	link_directories(${PCL_LIBRARY_DIRS})
	add_definitions(${PCL_DEFINITIONS})
endif(pclEnabled)	
###########

# ----- Code directories:
INCLUDE_DIRECTORIES( "geometry" )
ADD_SUBDIRECTORY   ( "geometry" )



