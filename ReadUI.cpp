#include<iostream>
#include<fstream>
#include<regex>
using namespace std;
class ReadUI{
private:
    void signUp(){
        int cintry=0;
        string account,pwd1,pwd2;
        cout<<"请输入你的账号：";
        cin >> account;
        cinPwd:
        if(cintry>=3){
            reader();
        }
        cout<<"请输入你的密码：";
        cin>>pwd1;
        cout<<"请再次输入您的密码：";
        cin>>pwd2;
        while(pwd1!=pwd2){
            ++cintry;
            cout<<"你输入的密码不一致，请再次输入!"<<endl;
            goto cinPwd;
        }
        while(pwd1.length()<=7||pwd1.length()>=17){
            ++cintry;
            cout<<"密码长度为8到16位!"<<endl;
            goto cinPwd;
        }
        int sum=0;
        sum= regex_search(pwd1, regex("[A-Z]")) ? ++sum : sum;
        sum= regex_search(pwd1,regex("[0-9]")) ? ++sum:sum;
        sum= regex_search(pwd1,regex("[a-z]")) ? ++sum:sum;
        sum= regex_search(pwd1,regex("[@#$]")) ? ++sum:sum;
        if(sum<2){
            ++cintry;
            cout<<"您输入的密码不符合规范，请重新输入！" << endl;
            goto cinPwd;
        }else{
            cout<<"注册成功！";
            ofstream user("user.txt", ios::app);
            user << account << " " << pwd1 << endl;
            user.close();
        }

    }
    void signIn(){
        fstream  user("user.txt",ios::in);
        cout<<"请输入您的账号：";
        string account;
        cin>>account;
        if(user.is_open()){
            char buff[1000]{0};
            int time=0;
            user>>buff;
            string buffStr=buff;
            int i=0,j=0;
            int index[100];
            while(buffStr[i]){
                while(buffStr[i]!=' '){
                    i++;
                }
                index[++j]=i++;
            }//buffstr[index[j]+1]到buffstr[index[j+1]-1]为一串账号或者密码


        }

    }
public:
    void reader(){
        int readerChoice;
        cout << "您已经进入读者界面，请选择：1.登录  2.注册  3.返回主界面" << endl;
        cin >> readerChoice;
        while(readerChoice!=1&&readerChoice!=2&&readerChoice!=3){
            cout<<"请再次确认您的操作！"<<endl;
            cin>>readerChoice;
        }

        if(readerChoice==2){
            signUp();
        }else if(readerChoice==1){

        }
    }
};