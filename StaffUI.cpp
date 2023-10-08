#include <iostream>
#include <fstream>
#include <regex>
#include <mysql.h>
#include "databaseContribute.h"

using namespace std;

class StaffUI {
private:
    MYSQL_RES *res; // 该结构代表返回行的一个查询结果集
    MYSQL_ROW row; // 一个行数据的类型安全(type-safe)的表示

    string curUser = "";
    string curReader = "";

    int staffBusiness() {

        business:
        cout << "您已进入员工业务界面，请选择：1.借书 2.还书 3.查询 4.退出登录" << endl;
        int businessChoice;
        int cinBusinessChoice = 0;
        cinBusinessChoice:
        cin >> businessChoice;
        if (businessChoice == 1) {
            int cinAccount = 0;
            cinBorrowerAccount:
            cinAccount++;
            if(cinAccount == 4){
                cout << "您因多次输入而退出！" << endl;
                goto business;
            }
            cout << "请输入读者账号：";
            string borrowerAccount;
            cin >> borrowerAccount;
            char query1[256];
            snprintf(query1, sizeof(query1), "select * from user where account = '%s' and user_role = 1",
                     borrowerAccount.c_str());
            mysql_query(&conn, query1);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "该用户不存在！" << endl;
                mysql_free_result(res);
                goto cinBorrowerAccount;
            }
            mysql_free_result(res);
            int cinPassword = 0;
            cinBorrowerPassword:
            cinPassword++;
            if(cinPassword == 4){
                cout << "您因多次输入而退出！" << endl;
                goto business;
            }
            cout << "请输入读者密码：";
            string borrowerPassword;
            cin >> borrowerPassword;
            char query3[256];
            snprintf(query3, sizeof(query3), "select * from user where account = '%s' and user_role = 1 and password = '%s'",
                     borrowerAccount.c_str(),borrowerPassword.c_str());
            mysql_query(&conn, query3);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "读者密码错误！" << endl;
                mysql_free_result(res);
                goto cinBorrowerPassword;
            }
            mysql_free_result(res);
            curReader = borrowerAccount;
            int cinBookName = 0;
            bookBorrow:
            cinBookName++;
            if(cinBookName == 5){
                cout << "您因多次输入而退出！" << endl;
                goto business;
            }
            cout << "请输入想要借出的书名：";
            string borrowName;
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
                mysql_free_result(res);
                char query1[256];
                snprintf(query1, sizeof(query1), "update book set status = 1 , user_name = '%s' where name = '%s'",
                         curReader.c_str(),
                         borrowName.c_str());
                mysql_query(&conn, query1);
                cout << "借书成功,正在返回员工业务界面。" << endl;
                curReader = "";
                goto business;
            }
        } else if (businessChoice == 2){
            int cinAccount = 0;
            int cinPassword = 0;
            cinReturnAccount:
            ++cinAccount;
            if( cinAccount == 4) {
                cout<<"您因输入错误次数太多返回！"<<endl;
                goto business;
            }
            cout << "请输入读者账号：";
            string returnAccount;
            cin >> returnAccount;
            char query1[256];
            snprintf(query1, sizeof(query1), "select * from user where account = '%s' and user_role = 1",
                     returnAccount.c_str());
            mysql_query(&conn, query1);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "该用户不存在！" << endl;
                mysql_free_result(res);
                goto cinReturnAccount;
            }
            mysql_free_result(res);
            cinReturnPassword :
            cinPassword++;
            if(cinPassword == 4){
                cout<<"您因输入错误次数太多而返回！"<<endl;
                goto business;
            }
            cout << "请输入读者密码：" ;
            string returnPassword;
            cin >> returnPassword;
            char query2[256];
            snprintf(query2, sizeof(query2), "select * from user where account = '%s' and user_role = 1 and password = '%s'",
                     returnAccount.c_str(),returnPassword.c_str());
            mysql_query(&conn, query2);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "读者密码错误！" << endl;
                mysql_free_result(res);
                goto cinReturnPassword;
            }
            curReader = returnAccount;
            int cinBookName = 0;
            bookReturn:
            cinBookName++;
            if(cinBookName == 4){
                cout << "您因多次输入而退出！" << endl;
                goto business;
            }
            cout << "请输入想要归还的书名：";
            string bookName;
            cin >> bookName;
            mysql_free_result(res);
            char query0[256];
            snprintf(query0, sizeof(query0), "select * from book where name = '%s' ", bookName.c_str());
            mysql_query(&conn, query0);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "该书不存在！" << endl;
                mysql_free_result(res);
                goto bookReturn;
            }
            mysql_free_result(res);
            snprintf(query0, sizeof(query0), "select status from book where name='%s'", bookName.c_str());
            mysql_query(&conn, query0);
            res = mysql_use_result(&conn);
            //char*类型的1转换成string类型等于49

            if ((string) mysql_fetch_row(res)[0] == "0") {
                cout << "该书并没有被借出！" << endl;
                mysql_free_result(res);
                goto bookReturn;
            } else {
                mysql_free_result(res);
                char query1[256];
                snprintf(query1, sizeof(query1), "update book set status = 0 , user_name = NULL where name = '%s'",
                         bookName.c_str());
                mysql_query(&conn, query1);
                cout << "还书成功,正在返回员工业务界面。" << endl;
                curReader = "";
                goto business;
            }
        }else if(businessChoice == 3){
            int cinReaderName = 0;
            cinReaderName:
            cinReaderName++;
            if(cinReaderName == 4){
                cout << "您因输入多次而退出！" << endl;
                goto business;
            }
            cout << "请输入读者名：";
            string readerName;
            cin >> readerName;
            char query4[256];
            snprintf(query4, sizeof(query4), "select * from user where account = '%s' and user_role = 1",
                     readerName.c_str());
            mysql_query(&conn, query4);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "该用户不存在！" << endl;
                mysql_free_result(res);
                goto cinReaderName;
            }
            mysql_free_result(res);
            int cinPassword = 0;
            cinReaderPassword:
            cinPassword++;
            if(cinPassword == 4){
                cout << "您因多次输入而退出！" << endl;
                goto business;
            }
            cout << "请输入读者密码：";
            string readerPassword;
            cin >> readerPassword;
            char query5[256];
            snprintf(query5, sizeof(query5), "select * from user where account = '%s' and user_role = 1 and password = '%s'",
                     readerName.c_str(),readerPassword.c_str());
            mysql_query(&conn, query5);
            res = mysql_use_result(&conn);
            if ((row = mysql_fetch_row(res)) == NULL) {
                cout << "读者密码错误！" << endl;
                mysql_free_result(res);
                goto cinReaderPassword;
            }
            mysql_free_result(res);
            curReader = readerName;
            cout << "读者：" << curReader << "借出的书为：" << endl;
            char query6[256];
            snprintf(query6, sizeof(query6), "select name from book where user_name = '%s'", curReader.c_str());
            mysql_query(&conn, query6);
            res = mysql_use_result(&conn);
            while ((row = mysql_fetch_row(res)) != NULL) {
                cout << row[0] << " ";
            }
            mysql_free_result(res);
            cout << endl;
            cout << "正在返回员工业务界面。" << endl;
            goto business;
        }else if (businessChoice == 4){
            return 0;
        }
        while(businessChoice!=1&&businessChoice!=2&&businessChoice!=3&&businessChoice!=4){
            if(cinBusinessChoice == 3){
                cout << "您因操作错误而返回！" << endl;
                goto business;
            }
            cout << "请确认您的操作！";
            cinBusinessChoice++;
            goto cinBusinessChoice;
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
        snprintf(query, sizeof(query), "select * from user where account = '%s' and password = '%s' and user_role = 2",
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
            signIn = staffBusiness();
            return signIn;
        }
    }

public:
    int staff() {
        int staffChoice;
        cinChoice:
        cout << "您已经进入员工页面，请选择：1.登录  2.返回主界面" << endl;
        cin >> staffChoice;
        if (staffChoice == 1) {
            if (signIn() == 0)
                cout << "用户成功退出。" << endl;
            else
                cout << "您因输入多次退出！" << endl;
            goto cinChoice;
        }
    }


};