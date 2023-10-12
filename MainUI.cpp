#include <iostream>
#include <limits>
#include "ReadUI.cpp"
#include "databaseContribute.h"
#include "StaffUI.cpp"
#include "ManageUI.cpp"


using namespace std;


int main() {
    // system("chcp 65001");
    connectMysql();
    cinIdentification:
    int identification;
    cout << "欢迎进入图书管理系统，请输入您的身份：1.读者  2.普通员工  3.管理人员" << endl;
    cin >> identification;
    while (identification != 1 && identification != 2 && identification != 3) {
        cout << "请再次确认您的身份！" << endl;
        cin.clear(); // 清除错误标志位
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区的无效输入
        goto cinIdentification;
    }
    if (identification == 1) {
        auto *readUI = new ReadUI();
        int readerReturn=readUI->reader();
        if(readerReturn==1){
            goto cinIdentification;
        }
    }else if(identification==2){
        auto *staffUI = new StaffUI();
        int staffReturn = staffUI->staff();
        if(staffReturn==1) {
            goto cinIdentification;
        }else{
            cout<< "您因操作错误而退出！" << endl;
            goto cinIdentification;
        }
    }else if(identification == 3){
        auto *manageUI = new ManageUI();
        int manageReturn = manageUI->manage();
        if( manageReturn == 1){
            goto cinIdentification;
        }else{
            cout << "您因操作错误而退出！" << endl;
            goto cinIdentification;
        }
    }
};