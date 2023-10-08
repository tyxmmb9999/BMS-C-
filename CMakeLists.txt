cmake_minimum_required(VERSION 3.16)

project(BMS)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(C:\\Program\ Files\\MYSQL\\MySQL\ Server\ 8.0\\include) ##本机MySQL下的include路径
link_directories(C:\\Program\ Files\\MYSQL\\MySQL\ Server\ 8.0\\lib) ##本机MySQL下的lib路径
link_libraries(libmysql) ##这个这样填就行

add_executable(MainUI MainUI.cpp ReadUI.cpp databaseContribute.h databaseContribute.cpp)
add_executable(test test.cpp)
add_executable(bookGenerate bookGenerate.cpp databaseContribute.cpp databaseContribute.h)
add_executable(StaffUI StaffUI.cpp)

target_link_libraries(MainUI libmysql) ##Clion改为自己的工程文件
target_link_libraries(test libmysql) ##Clion改为自己的工程文件
