#include <mysql.h>
#include "iostream"


// databaseContribute.h
#ifndef DATABASE_CONTRIBUTE_H
#define DATABASE_CONTRIBUTE_H

bool connectMysql(); // 函数声明
extern MYSQL conn; // 变量声明

#endif // DATABASE_CONTRIBUTE_H