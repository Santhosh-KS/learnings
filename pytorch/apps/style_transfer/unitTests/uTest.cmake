CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
 
# Locate GTest
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
 
SET(bin_name unitTest)
SET(src_files unitTests/mainTest.cpp
              unitTests/UrlParserTest.cpp
              common/src/UrlParser.cpp)

# Link Unit tests with what we want to test and the GTest and pthread library
ADD_EXECUTABLE(${bin_name} ${src_files})
TARGET_INCLUDE_DIRECTORIES(${bin_name} PUBLIC client/inc common/inc)
TARGET_LINK_LIBRARIES(${bin_name} ${GTEST_LIBRARIES} pthread)
TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)
