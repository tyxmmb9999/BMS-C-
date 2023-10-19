#include <iostream>
#include <mysql.h>
#include <limits>
#include "databaseContribute.h"

using namespace std;

class ManageUI {
private:
    MYSQL_RES *res; // 该结构代表返回行的一个查询结果集
    MYSQL_ROW row; // 一个行数据的类型安全(type-safe)的表示

    string curUser = "";
    string curReader = "";

    int manageBusiness() {
        business:
        cout << "您已进入管理人员业务界面，请选择：1.注册 2.注销 3.查询 4.退出登录" << endl;
        int businessChoice;
        cin >> businessChoice;
        int cinTry = 1;
        while (businessChoice != 1 && businessChoice != 2 && businessChoice != 3 && businessChoice != 4) {
            cin.clear(); // 清除错误标志位
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区的无效输入
            cinTry++;
            if (cinTry == 4) {
                return 1;
            }
            cout << "请再次确认您的操作！" << endl;
            cin >> businessChoice;
        }
        if (businessChoice == 2) {
            int cinAccount = 0;
            cinStaffAccount:
            cinAccount++;
            if (cinAccount == 4) {
                cout << "您因多次输入而返回！" << endl;
                goto business;
            }
            cout << "请输入员工账号：";
            string StaffAccount1;
            cin >> StaffAccount1;
            cout << "请确认员工账号：";
            string StaffAccount2;
            cin >> StaffAccount2;
            while (StaffAccount2 != StaffAccount1) {
                cout << "两次输入不一致，请重新输入！" << endl;
                goto cinStaffAccount;
            }
            string StaffAccount = StaffAccount1;
            char query1[256];
            snprintf(query1, sizeof(query1), "select * from user where account = '%s' and user_role = 2",
                     StaffAccount.c_str());
            mysql_query(&conn, query1);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "该员工不存在！" << endl;
                mysql_free_result(res);
                goto cinStaffAccount;
            }
            mysql_free_result(res);
            char query2[256];
            snprintf(query2, sizeof(query2), "delete from user where account = '%s' and user_role = 2;",
                     StaffAccount.c_str());
            mysql_query(&conn, query2);
            cout << "注销成功，正在返回管理人员业务界面..." << endl;
            goto business;
        } else if (businessChoice == 1){
            int signUp;
            int cinSUAccount = 0;
            string account, pwd1, pwd2;
            cinAccount:
            if (cinSUAccount >= 3) {
                cout << "您因输入多次而返回！" << endl;
                goto business;
            }
            cout << "请输入员工账号：";
            cin >> account;
            char query3[256];
            snprintf(query3, sizeof(query3), "select account from user where account = '%s'", account.c_str());
            mysql_query(&conn, query3);
            res = mysql_use_result(&conn);
            if (mysql_fetch_row(res) == NULL) {
                cinPwd:
                if (cinSUAccount >= 3) {
                    cout << "您因输入多次而返回！" << endl;
                    goto business;
                }
                cout << "请输入员工密码：";
                cin >> pwd1;
                cout << "请再次输入员工密码：";
                cin >> pwd2;
                while (pwd1 != pwd2) {
                    ++cinSUAccount;
                    cout << "你输入的密码不一致，请再次输入!" << endl;
                    goto cinPwd;
                }
                while (pwd1.length() <= 7 || pwd1.length() >= 17) {
                    ++cinSUAccount;
                    cout << "密码长度为8到16位!" << endl;
                    goto cinPwd;
                }
                int sum = 0;
                sum = regex_search(pwd1, regex("[A-Z]")) ? ++sum : sum;
                sum = regex_search(pwd1, regex("[0-9]")) ? ++sum : sum;
                sum = regex_search(pwd1, regex("[a-z]")) ? ++sum : sum;
                sum = regex_search(pwd1, regex("[@#$]")) ? ++sum : sum;
                if (sum < 2) {
                    ++cinSUAccount;
                    cout << "您输入的密码不符合规范，请重新输入！" << endl;
                    goto cinPwd;
                }
                char query4[256];
                snprintf(query4, sizeof(query4), "insert into user values('%s', '%s',2);", account.c_str(), pwd1.c_str());
                mysql_query(&conn, query4);
                cout << "注册成功,返回管理人员业务界面。" << endl;
                goto business;
            } else {
                cout << "该员工已存在！" << endl;
                ++cinSUAccount;
                mysql_free_result(res);
                goto cinAccount;
            }
        } else if (businessChoice == 3){
            char query5[256];
            snprintf(query5, sizeof(query5), "select * from user where user_role = 2");
            mysql_query(&conn, query5);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "未查询到相关记录，正在返回..." << endl;
                mysql_free_result(res);
                goto business;
            }
            mysql_free_result(res);
            cout << "所有员工用户名如下：" << endl;
            char query6[256];
            snprintf(query6, sizeof(query6), "select * from user where user_role = 2");
            mysql_query(&conn, query6);
            res = mysql_use_result(&conn);
            while ((row = mysql_fetch_row(res)) != NULL) {
                cout << row[0] << " ";
            }
            cout << endl;
            mysql_free_result(res);
            goto business;
        } else if (businessChoice == 4){
            return 0;
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
            mysql_free_result(res);
            return signIn;
        }
        cout << "请输入您的账号：";
        cin >> account;
        cout << "请输入您的密码：";
        cin >> password;

        char query[256];
        snprintf(query, sizeof(query), "select * from user where account = '%s' and password = '%s' and user_role = 3",
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
            signIn = manageBusiness();
            return signIn;
        }
    }

public:


    int manage() {
        cinChoice:
        int manageChoice;
        cout << "您已经进入管理人员界面，请选择：1.登录 2.返回主界面" << endl;
        cin >> manageChoice;
        int cinTry = 1;
        while (manageChoice != 1 && manageChoice != 2) {
            cin.clear(); // 清除错误标志位
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区的无效输入
            cinTry++;
            if (cinTry == 6) {
                cout << "您因操作错误返回！" << endl;
                goto cinChoice;
            }
            cout << "请再次确认您的操作！" << endl;
            cin >> manageChoice;
        }
        if (manageChoice == 1) {
            int readerChoice1 = signIn();
            if (readerChoice1 == 0)
                cout << "用户成功退出。" << endl;
            else
                cout << "您因重复输入多次退出！" << endl;
            curUser = "";
            goto cinChoice;
        } else if (manageChoice == 2) {
            cout << "成功返回主界面！" << endl;
            return 1;
        }
    }

};