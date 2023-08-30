#include<iostream>
using namespace std;
class ReadUI{
private:
    void signUp(){

    }
public:
    void reader(){
        int readerChoice;
        cout<<"您已经进入读者界面，请选择：1.登录  2.注册  3.返回主界面"<<endl;
        cin>>readerChoice;
        while(readerChoice!=1&&readerChoice!=2&&readerChoice!=3){
            cout<<"请再次确认您的操作！"<<endl;
            cin>>readerChoice;
        }
        if(readerChoice==2){

        }
    }
};