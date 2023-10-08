#include<iostream>
#include<mysql.h>
#include "databaseContribute.h"
MYSQL conn;
bool connectMysql() {
    mysql_init(&conn); // 初始化mysql
    if (!(mysql_real_connect(&conn, "localhost", "root", "123456", "bms", 3306, NULL, 0))) {
        std::cout << "Error connecting to database:" + (std::string) mysql_error(&conn) << std::endl;
        return false;
    } else {
        puts("Connected...");
        return true;
    }
} // 声明connectMysql函数