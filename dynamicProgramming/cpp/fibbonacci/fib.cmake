Project(DynamicProgramming)

SET(bin_src fibbonacci/fib.cpp)
            

SET(bin_name Fibbonacci)

ADD_EXECUTABLE(${bin_name} ${bin_src}) 
TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)
