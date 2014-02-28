#ifndef _USER_H_
#define _USER_H_
#include <iostream>
#include <cstring>
#define IDMAXLENGTH 12
#define HOMEMAXLENGTH 10
#define FOLLOWEOTHERMAX 60
#define FOLLOWEDMAX 120
#define MESSAGEDELIVERINGMAX 200
#define PASSWORDMAXLENGTH 16

//ID限制11个字符 家乡9个 密码15个

//接下来的宏为各数据在user中的相对位置

//结束
#define NAME 0
#define BIRTH 12
#define GENDER 24
#define HOMETOWN 25
#define PHONENBR 35
#define IS_DIABLED 39
#define USER_FOLLOWED 40
#define USER_FOLLOWING_ME 284
#define MSG_DLVD 768
#define LOGINID 1572
#define PSD 1584
#define UID 1600

class User
{
private:
//essential information
    char name[IDMAXLENGTH];                          //12 here
    char birth[12];                                      //12 + 12 = 24 here
    bool gender; // true for male  false for female  //25 here

//extra information    
    char hometown[HOMEMAXLENGTH];                    //25 + 10 = 35 here
    int phonenumber;                                 //35 +  4 = 39 here

//other informantion
    bool is_disableuser; //true 表示该账号已被删除  但不能被注册/使用  40 here
    int user_followed[FOLLOWEOTHERMAX+1]; //自己关注的人的UID 上限60人 [0]是目前关注的人的个数 61 * 4 + 40 = 284  here
    int user_following_me[FOLLOWEDMAX+1]; //关注自己的人的UID 上限120人 [0]是关注自己人的个数  121 * 4 + 284 = 768 here


    int message_delieverd[MESSAGEDELIVERINGMAX+1]; //记录发过的信息的mid [0]是总消息数  1572 here

//basic information
    char loginid[IDMAXLENGTH];  // 1584 here
    char password[PASSWORDMAXLENGTH]; // 1600here
    int uid; //user id   1604here

public:
    User()
    {
        memset(this,0,sizeof(User));
    }
    void deliver_message();
    void change_information();
    void change_password();
    void disable_account();
    void check_i_followed_who_list();
    void check_i_am_followed_by_who_list();
    void check_msg();
    void seek_user();  //id only
    void see_one_msglist(int uid);
    void trans_message(int mid);
};
#endif // USER_H
