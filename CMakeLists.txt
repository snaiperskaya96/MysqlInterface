#SimpleJSON from MJPA - https://github.com/MJPA/SimpleJSON
#mysql-connector from Oracle
#Sha256 from zedwood - http://www.zedwood.com/article/cpp-sha256-function
#IniReader from benhoyt - https://github.com/benhoyt/inih
cmake_minimum_required(VERSION 3.0)
project(MysqlListener)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

add_subdirectory(ThirdParty/SimpleJSON)
add_subdirectory(ThirdParty/mysql-connector)

find_package(Boost 1.48.0 REQUIRED)

set(SOURCE_FILES main.cpp Source/Server/Server.cpp Source/Server/Server.h Source/Util/Util.h Source/Util/Util.cpp Source/Server/Socket.cpp Source/Server/Socket.h Source/Mysql/Mysql.cpp Source/Mysql/Mysql.h Source/Util/Ini/INIReader.cpp Source/Util/Ini/INIReader.h Source/Util/Ini/ini.c Source/Util/Ini/ini.h Source/Util/Sha256/Sha256.cpp Source/Util/Sha256/Sha256.h)
add_executable(MysqlListener ${SOURCE_FILES})
target_include_directories(MysqlListener PUBLIC Source/ ThirdParty/SimpleJSON ThirdParty/mysql-connector ThirdParty/mysql-connector/driver ${Boost_INCLUDE_DIRS})
target_link_libraries(MysqlListener SimpleJSON mysqlcppconn-static ${Boost_LIBRARIES})

configure_file(Default/config.ini ${CMAKE_BINARY_DIR}/config.ini COPYONLY)