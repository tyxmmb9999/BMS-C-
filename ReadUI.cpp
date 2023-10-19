#include <iostream>
#include <fstream>
#include <regex>
#include <mysql.h>
#include <limits>
#include "databaseContribute.h"


using namespace std;


class ReadUI {
private:
    MYSQL_RES *res; // 该结构代表返回行的一个查询结果集
    MYSQL_ROW row; // 一个行数据的类型安全(type-safe)的表示


    string curUser = "";

    int signUp() {
        int signUp;
        int cintry = 0;
        string account, pwd1, pwd2;
        cinAccount:
        if (cintry >= 3) {
            signUp = 1;
            return signUp;
        }
        cout << "请输入你的账号：";

        cin >> account;
        char query[256];
        snprintf(query, sizeof(query), "select account from user where account = '%s'", account.c_str());
        mysql_query(&conn, query);
        res = mysql_use_result(&conn);
        if (mysql_fetch_row(res) == NULL) {
            cinPwd:
            if (cintry >= 3) {
                cintry = 0;
                reader();
            }
            cout << "请输入你的密码：";
            cin >> pwd1;
            cout << "请再次输入您的密码：";
            cin >> pwd2;
            while (pwd1 != pwd2) {
                ++cintry;
                cout << "你输入的密码不一致，请再次输入!" << endl;
                goto cinPwd;
            }
            while (pwd1.length() <= 7 || pwd1.length() >= 17) {
                ++cintry;
                cout << "密码长度为8到16位!" << endl;
                goto cinPwd;
            }
            int sum = 0;
            sum = regex_search(pwd1, regex("[A-Z]")) ? ++sum : sum;
            sum = regex_search(pwd1, regex("[0-9]")) ? ++sum : sum;
            sum = regex_search(pwd1, regex("[a-z]")) ? ++sum : sum;
            sum = regex_search(pwd1, regex("[@#$]")) ? ++sum : sum;
            if (sum < 2) {
                ++cintry;
                cout << "您输入的密码不符合规范，请重新输入！" << endl;
                goto cinPwd;
            }
            char query1[256];
            snprintf(query1, sizeof(query1), "insert into user values('%s', '%s',1);", account.c_str(), pwd1.c_str());
            mysql_query(&conn, query1);
            cout << "注册成功,返回读者业务界面。" << endl;
            signUp = 0;
            return signUp;
        } else {
            cout << "该用户已存在！" << endl;
            ++cintry;
            mysql_free_result(res);
            goto cinAccount;
        }
    }

    int readBusiness() {
        int readBusiness = 0;
        business:
        cout << "您已经进入读者业务界面，请选择您要进行的操作：1.借书 2.还书 3.查询 4.退出登录" << endl;
        int businessChoice;
        cin >> businessChoice;
        int cinTry = 1;
        while (businessChoice != 1 && businessChoice != 2 && businessChoice != 3 && businessChoice != 4) {
            cin.clear(); // 清除错误标志位
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区的无效输入
            cinTry++;
            if(cinTry == 4){
                return 1;
            }
            cout << "请再次确认您的操作！" << endl;
            cin >> businessChoice;
        }
        string borrowName;
        if (businessChoice == 1) {
            bookBorrow:
            cout << "请输入您要借的书名：";
            cin >> borrowName;
            char query0[256];
            snprintf(query0, sizeof(query0), "select * from book where name = '%s' ", borrowName.c_str());
            mysql_query(&conn, query0);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "该书不存在！" << endl;
                mysql_free_result(res);
                goto bookBorrow;
            }
            mysql_free_result(res);
            snprintf(query0, sizeof(query0), "select status from book where name='%s'", borrowName.c_str());
            mysql_query(&conn, query0);
            res = mysql_use_result(&conn);
            //char*类型的1转换成string类型等于49

            if ((string) mysql_fetch_row(res)[0] == "1") {
                cout << "您想要的书已经被借出！" << endl;
                mysql_free_result(res);
                goto bookBorrow;

            } else {
                char query1[256];
                snprintf(query1, sizeof(query1), "update book set status = %d , user_name = '%s' where name = '%s'", 1,
                         curUser.c_str(),
                         borrowName.c_str());
                mysql_query(&conn, query1);
                mysql_free_result(res);
                cout << "借书成功,正在返回读者业务界面。" << endl;
                goto business;
            }
        } else if (businessChoice == 2) {
            returnBook:
            cout << "请输入您要还的书名：";
            string returnName;
            cin >> returnName;
            char query2[256];
            snprintf(query2, sizeof(query2), "select user_name from book where name = '%s'", returnName.c_str());
            mysql_query(&conn, query2);
            res = mysql_use_result(&conn);
            char *c = mysql_fetch_row(res)[0];
            if (c == nullptr || (string) c != curUser) {
                cout << "此书并没有被您借出！" << endl;
                mysql_free_result(res);
                goto returnBook;
            } else {
                mysql_free_result(res);
                char query3[256];
                snprintf(query3, sizeof(query3), "UPDATE book SET status = 0, user_name = NULL WHERE name = '%s'",
                         returnName.c_str());
                mysql_query(&conn, query3);
                mysql_free_result(res);
                cout << "还书成功,正在返回读者业务界面。" << endl;
                goto business;
            }
        } else if (businessChoice == 3) {
            char query9[256];
            snprintf(query9, sizeof(query9), "select name from book where user_name = '%s'", curUser.c_str());
            mysql_query(&conn, query9);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "未查询到相关记录，正在返回..." << endl;
                mysql_free_result(res);
                goto business;
            }
            mysql_free_result(res);
            cout << "用户:" << curUser << endl;
            cout << "借出的书为：";
            char query4[256];
            snprintf(query4, sizeof(query4), "select name from book where user_name = '%s'", curUser.c_str());
            mysql_query(&conn, query4);
            res = mysql_use_result(&conn);
            while ((row = mysql_fetch_row(res)) != NULL) {
                cout << row[0] << " ";
            }
            mysql_free_result(res);
            cout << endl;
            cout << "正在返回读者业务界面。" << endl;
            goto business;
        } else if (businessChoice == 4) {
            cout << "您已退出登录,正在退回读者界面。" << endl;
            return readBusiness;
        }
    }

    int signIn() {
        int signIn;
        int cinTry = 0;
        string account;
        string password;
        cinAccountAndPassword:
        if (cinTry >= 5) {
            signIn = 1;
            return signIn;
        }
        cout << "请输入您的账号：";
        cin >> account;
        cout << "请输入您的密码：";
        cin >> password;

        char query[256];
        snprintf(query, sizeof(query), "select * from user where account = '%s' and password = '%s' and user_role = 1",
                 account.c_str(),
                 password.c_str());
        mysql_query(&conn, query);
        res = mysql_use_result(&conn);
        if (mysql_fetch_row(res) == NULL) {
            ++cinTry;
            cout << "您输入的账号或密码有误，请重新输入！" << endl;
            goto cinAccountAndPassword;
        } else {
            cout << "登录成功！" << endl;
            mysql_free_result(res);
            curUser = account;
            signIn = readBusiness();
            return signIn;
        }
    }

public:
    int reader() {
        cinChoice:
        int readerChoice;
        cout << "您已经进入读者界面，请选择：1.登录  2.注册  3.返回主界面" << endl;
        cin >> readerChoice;
        int cinTry = 1;
        while (readerChoice != 1 && readerChoice != 2 && readerChoice != 3) {
            cin.clear(); // 清除错误标志位
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区的无效输入
            cinTry++;
            if(cinTry == 4){
                cout << "您因操作错误返回！" << endl;
                goto cinChoice;
            }
            cout << "请再次确认您的操作！" << endl;
            cin >> readerChoice;
        }
        if (readerChoice == 2) {
            int readerChoice2 = signUp();
            if (readerChoice2 == 0)
                cout << "您已成功注册！" << endl;
            else
                cout << "您因重复输入多次退出！" << endl;
            goto cinChoice;
        } else if (readerChoice == 1) {
            int readerChoice1 = signIn();
            if (readerChoice1 == 0)
                cout << "用户成功退出。" << endl;
            else
                cout << "您因重复输入多次退出！" << endl;
            curUser = "";
            goto cinChoice;
        } else if(readerChoice == 3) {
            cout << "成功返回主界面！" << endl;
            return 1;
        }
    }
};