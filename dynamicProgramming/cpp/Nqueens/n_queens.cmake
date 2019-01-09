Project(DynamicProgramming)

SET(bin_src Nqueens/Nqueens.cpp)
            

SET(bin_name Nqueens)

ADD_EXECUTABLE(${bin_name} ${bin_src}) 
TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)
