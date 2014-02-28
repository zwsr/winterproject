#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <cstring>
#include "User.h"


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
    Message(Message backer)
    {
        memcpy(this,backer,sizeof(Message));
    }

    string get_content() const
    {
        return content;
    }
    Message(string cont,int dlv_id, int src_msg, string logid); // src_msg 代表来源信息的mid logid是发送者的id
    string packed_tranferedcontent();
    friend ostream& operator<<(ostream& , const Message& );
};
operator << (ostream& out, const Message &m)
{
    out << content << "\n";
    << "from " << m.logginid << "   Transfered times:"  << m.transed_count << endl;
}


#endif // MESSAGE_H
