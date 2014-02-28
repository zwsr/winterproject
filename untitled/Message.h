#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "User.h"
using namespace std;

#define CONTENTMAXLENGTH 139

class Message
{
private:
    int deliver_id;  //发送者的uid
    int source_msg;  //消息来源  0则为原创
    int transed_count; //被转发次数统计
    char content[CONTENTMAXLENGTH]; //138个字符为上限
    char logginid[IDMAXLENGTH];
public:
    Message()
    {
        memset(this,0,sizeof(Message));
    }
    Message(const Message& backer)
    {
        memcpy(this,&backer,sizeof(Message));
    }

    string get_content()
    {
        return content;
    }

    Message(string cont,int dlv_id, int src_msg, string logid); // src_msg 代表来源信息的mid logid是发送者的id
    string packed_tranferedcontent();
    friend ostream& operator<< (ostream& , const Message& );
};



#endif // MESSAGE_H
