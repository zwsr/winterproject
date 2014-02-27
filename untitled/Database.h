#ifndef DATABASE_H
#define DATABASE_H
#include "User.h"

#define HASHGROUPNUMBER 10000   //表示该哈希库中有多少个位置

struct Userslotentry  //一个条目中有uid 和 login id
{
    int uid;
    char loginid[IDMAXLENGTH];
};

class Hashindex_db
{
private:
    int slot_number; //标记同key值情况下存在多个储存对象的个数  比如 a-key=5 b-key=5 a b都在key=5的slot中 那这样的slot满足情况
    int data_number; //目前为止进入数据库中的数据个数
    int data_size;   //进入数据库中的数据的大小  单位为byte
    Userslotentry hash_slots[HASHGROUPNUMBER];
    char* slotform_starter;
public:
    Hashindex_db();
    int get_keyvalue(string id);
    int search_loginid(string id, int* slotid = NULL); //返回0代表未找到该用户 slotid代表该id对应的hashslot
    int
};

#endif // DATABASE_H
