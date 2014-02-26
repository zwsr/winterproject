#ifndef _USER_H_
#define
#include <iostream>

#define IDMAXLENGTH 12
#define HOMEMAXLENGTH 10
#define FOLLOWEOTHERMAX 60
#define FOLLOWEDMAX 120
#define MESSAGEDELIVERINGMAX 200
#define PASSWORDMAXLENGTH 16

class Date
{
private:
    int year,month,day;
public:
    read_birth(int y, int m, int d);
};

class User
{
private:
//essential information
    char name[IDMAXLENGTH];                          //12 here
    Date birth;                                      //12 + 12 = 24 here
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


};
#endif // USER_H
