#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <cstring>


#define CONTENTMAXLENGTH 139

class Message
{
private:
    int deliver_id;  //发送者的uid
    int source_msg;  //消息来源  0则为原创
    int transed_count; //被转发次数统计
    char content[CONTENTMAXLENGTH]; //138个字符为上限
    bool is_deleted;
public:
    Message()
    {
        memset(this,0,sizeof(Message));
    }
    Message(string cont,int dlv_id, int src_msg);
    void delete_itself();
};

#endif // MESSAGE_H
