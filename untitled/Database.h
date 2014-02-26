#ifndef DATABASE_H
#define DATABASE_H

#define HASHGROUPNUMBER 10000   //表示该哈希库中有多少个位置

class Hashindex_db
{
private:
    int slot_number; //标记同key值情况下存在多个储存对象的个数  比如 a-key=5 b-key=5 a b都在key=5的slot中 那这样的slot满足情况
    int data_number; //目前为止进入数据库中的数据个数
    int data_size;   //进入数据库中的数据的大小  单位为byte
public:
    Hashindex_db();
};

#endif // DATABASE_H
