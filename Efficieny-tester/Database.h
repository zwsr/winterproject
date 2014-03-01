#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <cstring>

#define HASHGROUPNUMBER 10000   //表示该哈希库中有多少个位置
#define CACHESIZE 100       //表示user缓存中最多有多少数据
#define MSGCACHESIZE 100       //表示msg缓存中最多有多少数据

extern const std::string test_filename;
const std::string moreslottag = "more"; //代表该slot有多个key的stream

struct Userslotentry  //一个条目中有uid 和 login id
{
    int uid;
    char loginid[8];
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
    ~Hashindex_db()
    {
        write_back();
    }
};



#endif // DATABASE_H
