#ifndef DATABASE_H
#define DATABASE_H
#include "User.h"
#include "Message.h"
#include <fstream>
#include <cstring>

#define      10000   //表示该哈希库中有多少个位置

const string userindex_filename = "userindex.dat";
const string userdata_filename = "userdata.dat";
const string messagedata_filename = "messagedata.dat";

const string moreslottag = "morethanone"; //代表该slot有多个key的stream

struct Userslotentry  //一个条目中有uid 和 login id
{
    int uid;
    char loginid[IDMAXLENGTH];
};

class Hashindex_db  //用户名的hash index  文件 "userindex.dat"
{
private:
    int slot_number; //标记同key值情况下存在多个储存对象的个数  比如 a-key=5 b-key=5 a b都在key=5的slot中 那这样的slot满足情况
    int data_number; //目前为止进入数据库中的数据个数
    int entry_size;   //进入数据库中的数据的大小  单位为byte
    Userslotentry hash_slots[HASHGROUPNUMBER];
public:
    Hashindex_db() { }
    void init();
    int get_keyvalue(string id);
    int search_loginid(string id, int* slotid, int* gap); //返回0代表未找到该用户 slotid代表该id对应的hashslot
    int registing_id(string id); //返回-1表示注册失败 0表示成功
};

class Userdatabase    //一个专门用来管理储存user数据的文件 该文件"userdata.dat"
{
private:
    fstream fio;

public:
    User get_user(int uid);
    void init();
    void add_user(User newer);
    Userdatabase(){}
};

class Messagedatabase //一个专门用来管理储存message数据的文件 该文件"messagedata.dat"
{
private:
    fstream fio;

public:
    Message get_message(int mid);
    void init();
    void add_msg(User new_msg);
    Messagedatabase() {}

};


#endif // DATABASE_H
