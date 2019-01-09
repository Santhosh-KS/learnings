Project(DynamicProgramming)

SET(bin_src towerOfHanoi/towerOfHanoi.cpp)
            

SET(bin_name TowerOfHanoi)

ADD_EXECUTABLE(${bin_name} ${bin_src}) 
TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)
