#ifndef DATABASE_H
#define DATABASE_H

#include "User.h"
#include "User.h"
#include "Message.h"
#include <fstream>
#include <cstring>

#define HASHGROUPNUMBER 10000   //表示该哈希库中有多少个位置
#define CACHESIZE 100       //表示user缓存中最多有多少数据
#define MSGCACHESIZE 100       //表示msg缓存中最多有多少数据

const std::string userindex_filename = "userindex.dat";
const std::string userdata_filename = "userdata.dat";
const std::string messagedata_filename = "messagedata.dat";

const std::string moreslottag = "morethanone"; //代表该slot有多个key的stream

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
    void write_back();
    int get_keyvalue(std::string id);
    int get_data_number() const
    {
        return data_number;
    }
    int search_loginid(std::string id, int* slotid, int* gap); //返回0代表未找到该用户 slotid代表该id对应的hashslot
    int registing_id(std::string id); //返回-1表示注册失败 非0的uid表示成功
};

class Userdatabase    //一个专门用来管理储存user数据的文件 该文件"userdata.dat"
{
private:
    std::fstream fio;

public:
    User get_user(int uid);
    void init();
    void add_user(User newer);
    void writeback_user(int uid,User u);
    Userdatabase(){}
};

class Messagedatabase //一个专门用来管理储存message数据的文件 该文件"messagedata.dat"
{
private:
    std::fstream fio;
    int msg_number;

public:
    Message get_message(int mid);
    void init();
    int add_msg(Message new_msg); //返回mid
    void writeback_msg(int mid, Message backer);
    Messagedatabase():msg_number(0)
    {}
    ~Messagedatabase()
    {
        fio.open(messagedata_filename.c_str(),std::ios::out|std::ios::in);
        fio.write((char *)&msg_number,sizeof(int));
        fio.close();
    }

};

class Usercache    //使用队列方式管理缓存
{
private:
    int uid[CACHESIZE];
    int tag;
    int search_user(int u);   //输入UID  查看该用户是否在cache当中 -1代表不存在


public:
    int insert_user(int u);
    User user[CACHESIZE];
    void writeback_id(int id);   //把cahce中的某用户写回硬盘 刷新用

    Usercache()
    {
        memset(this,0,sizeof(Usercache));
    }
    int get_id(int u);
};

class Messagecache    //使用队列方式管理缓存
{
private:
    int mid[MSGCACHESIZE];
    int tag;
    int search_msg(int m);   //输入mid  查看该msg是否在cache当中 -1代表不存在


public:
    int insert_msg(int m);
    Message msg[MSGCACHESIZE];
    void writeback_id(int id);   //把cahce中的某用户写回硬盘 刷新用

    Messagecache()
    {
        memset(this,0,sizeof(Messagecache));
    }
    int get_id(int m);
};


#endif // DATABASE_H
