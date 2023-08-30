#include <iostream>
#include "ReadUI.cpp"
using namespace std;
int main(){
    system("chcp 65001");
    int identification;
    cout<<"欢迎进入图书管理系统，请输入您的身份：1.读者  2.普通员工  3.管理人员  4.啥也不是"<<endl;
    cin>>identification;
    while(identification != 1 && identification != 2 && identification != 3 && identification != 4) {
        cout << "请再次确认您的身份！"<<endl;
        cin  >>  identification;
    }
    if(identification==1){
        ReadUI *readUI=new ReadUI();
        readUI->reader();
    }
};