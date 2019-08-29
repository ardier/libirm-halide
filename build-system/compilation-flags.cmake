set (CMAKE_CXX_FLAGS -std=c++11 ${CMAKE_CXX_FLAGS})
if (LIBIRM_BUILD_32_BITS)
  set (CMAKE_CXX_FLAGS -m32 ${CMAKE_CXX_FLAGS})
endif()

set (LIBIRM_CMAKE_CXX_FLAGS)
set (LIBIRM_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)