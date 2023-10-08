#include<iostream>
#include "databaseContribute.h"

using namespace std;

int main() {
    connectMysql();
    for (int i = 1; i <= 1000; i++) {
        char query[256];

        if (i < 10){
            snprintf(query,sizeof(query),"insert into book (name, status) values ('000%d', 0)", i);
            mysql_query(&conn,query);
        }

        else if (i < 100) {
            snprintf(query, sizeof(query),"insert into book (name, status) values ('00%d', 0)", i );
            mysql_query(&conn, query);
        }
        else if(i<1000){
            snprintf(query, sizeof(query), "insert into book (name, status) values ('0%d', 0)", i);
            mysql_query(&conn, query);
        }else{
            snprintf(query, sizeof(query), "insert into book (name, status) values ('%d', 0)", i);
            mysql_query(&conn, query);
        }
    }
}