#include "Message.h"
#include <iostream>
#include <string>
#include <Database.h>
extern Messagecache msg_cache;

Message::Message(string cont, int dlv_id, int src_msg, string logid)
{
    transed_count = 0;
    strcpy(content,cont.c_str());
    strcpy(logginid,logid.c_str());
    deliver_id = dlv_id;
    source_msg = src_msg;
    int src_tmp = src_msg;
    while (src_tmp)
    {
        msg_cache.msg[msg_cache.get_id(source_msg)].transed_count++;
        src_tmp = msg_cache.msg[msg_cache.get_id(source_msg)].source_msg;
    }
}

string Message::packed_tranferedcontent()
{
    string tmp,tmp_2;
    tmp = logginid;
    tmp_2 = "Transfered from:";
    tmp = tmp_2 + tmp;
    tmp = tmp + "  ";
    tmp_2 = content;
    tmp = tmp + tmp_2;
    return tmp;
}


ostream& operator<< (ostream& out, const Message &m)
{
    out << m.content << "\n"
        << "from " << m.logginid << "   Transfered times:"  << m.transed_count << endl;
    return out;
}

