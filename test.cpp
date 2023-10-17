#include <mysql.h>
#include <iostream>

using namespace std;

MYSQL conn;
MYSQL_RES *res; // 该结构代表返回行的一个查询结果集
MYSQL_ROW row; // 一个行数据的类型安全(type-safe)的表示

void connectMysql() {
    mysql_init(&conn); // 初始化mysql
    if (!(mysql_real_connect(&conn, "localhost", "root", "123456", "bms", 3306, NULL, 0))) {
        cout << "Error connecting to database:" + (string) mysql_error(&conn) << endl;
    } else {
        puts("Connected...");
    }
}


int main() {
    // connectMysql();
    //
    // mysql_query(&conn, "insert into user values('123', '456')");
    //
    // mysql_query(&conn, "select * from user");
    //
    // res = mysql_use_result(&conn);
    //
    // while ((row = mysql_fetch_row(res)) != NULL) {
    //     cout << row[0] << ": " << row[1] << endl;
    // }
    //
    // mysql_free_result(res);
    // mysql_close(&conn);
    // char query[256];
    // snprintf(query,sizeof(query),"");
    // mysql_query(&conn,query);
    //
    // char c = '1';
    // int i = (int) c;
    // cout << i;
    int x = 60, y = 50, num = 0;
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 20; j++) {
            if (0.13 * x * i + 0.28 * y * j <= 90) {
                num = max(num, j);
            }
        }
        cout << "鸡蛋：" << i << "鸡胸肉：" << num << endl;
        num = 0;
    }
}