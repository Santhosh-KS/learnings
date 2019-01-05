Project(StyleTransferProject)

SET(bin_src client/src/ClientUi.cpp
            client/src/main.cpp
            ../common/src/TcpClient.cpp
            ../common/src/TcpServer.cpp
            ../common/src/UrlParser.cpp
            ../common/src/JsonFileParser.cpp
            ../common/src/JsonStringParser.cpp
            ../common/src/Utils.cpp)

SET(bin_name Client)
SET(rapid_json /opt/rapidjson/include)
SET(wt_inc /usr/include/Wt)

FIND_PACKAGE(Threads REQUIRED)
ADD_EXECUTABLE(${bin_name} ${bin_src}) 
TARGET_LINK_LIBRARIES(${bin_name} pthread) 
TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)
TARGET_INCLUDE_DIRECTORIES(${bin_name} PUBLIC client/inc common/inc ${rapid_json} ${wt_inc})

TARGET_LINK_LIBRARIES(${bin_name}
  debug wtd      optimized wt
  debug wthttpd  optimized wthttp)
