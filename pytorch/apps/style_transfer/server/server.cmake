Project(StyleTransferProject)

SET(bin_src server/src/RequestHandler.cpp
            server/src/main.cpp
            ../common/src/TcpClient.cpp
            ../common/src/TcpServer.cpp
            ../common/src/JsonFileParser.cpp
            ../common/src/JsonStringParser.cpp
            ../common/src/Utils.cpp)

SET(bin_name Server)
SET(rapid_json /opt/rapidjson/include)

FIND_PACKAGE(Threads REQUIRED)
ADD_EXECUTABLE(${bin_name} ${bin_src}) 
TARGET_LINK_LIBRARIES(${bin_name} pthread) 
TARGET_COMPILE_FEATURES(${bin_name} PUBLIC  cxx_lambda_init_captures)
TARGET_INCLUDE_DIRECTORIES(${bin_name} PUBLIC server/inc common/inc ${rapid_json})
