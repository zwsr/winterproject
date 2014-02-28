#include "Database.h"

int Hashindex_db::get_keyvalue(string id)
{
    int key = 0;
    int psycho = 1;
    for (int i = 0 ; i < id.length(); i++ )
    {
        int temp = id[i];
        temp = temp % 10;
        key += temp * psycho;
        psycho++;
        if (psycho == 5) psycho = 1;
    }
    key = key % HASHGROUPNUMBER;
    return key;
}

void Hashindex_db::init()
{
    fstream fio;
    fio.open(userindex_filename.c_str(),ios::in);
    if (fio)
    {
        fio.read((char *)this,sizeof(Hashindex_db));
        fio.close();
    }
    else
    {
        fio.open(userindex_filename.c_str(),ios::out);
        slot_number = 0;
        data_number = 0;
        entry_size = 0;
        memset(hash_slots,0,sizeof(Userslotentry)*HASHGROUPNUMBER);
        fio.write((char *)this,sizeof(Hashindex_db));
        fio.close();
    }
    return;
}

int Hashindex_db::search_loginid(string id, int *slotid, int *gap)
{
//phase_1
    int key_slot = get_keyvalue(id);
    *slotid = key_slot;
    if (hash_slots[key_slot].loginid != moreslottag)
    {
        if ( hash_slots[key_slot].uid == 0 ) return 0;
        if ( hash_slots[key_slot].loginid == id ) return hash_slots[key_slot].uid;
        else return 0;
    }
//phase_2
    else
    {
        int slotnumber = hash_slots[key_slot].uid;
        fstream fio;
        fio.open(userindex_filename.c_str(),ios::in|ios::out);
        fio.seekg(sizeof(Hashindex_db),ios::beg);
        *gap = 0;
        int tmp = 1;
        while (tmp != slotnumber)
        {
            int cur_slotamount;
            fio.read((char *)&cur_slotamount,sizeof(int));
            fio.seekg(sizeof(Userslotentry)*cur_slotamount,ios::cur);
            *gap += 4 + sizeof(Userslotentry)*cur_slotamount;
            tmp++;
        }
        int cur_slotamount;
        fio.read((char *)&cur_slotamount,sizeof(int));
        for (int i = 0; i < cur_slotamount;i++)
        {
            Userslotentry tmp_id;
            fio.read((char *)&tmp_id,sizeof(tmp_id));
            if ( id == tmp_id.loginid )
            {
                fio.close();
                return tmp_id.uid;
            }
        }
        fio.close();
        return 0;
    }
}

int Hashindex_db::registing_id(string id)
{
    int slotid,gap;
    int ret_value = search_loginid(id,&slotid,&gap);
    if (ret_value) return -1;

    data_number++;
    fstream fio;
    fio.open(userindex_filename.c_str(),ios::in|ios::out);
//regist case1    hash的槽位为空
    if (hash_slots[slotid].uid == 0)
    {
        hash_slots[slotid].uid = data_number;
        strcpy(hash_slots[slotid].loginid,id);
        fio.seekg(sizeof(int) * 3 + sizeof(Userslotentry) * slotid,ios::beg);
        fio.write((char *)&(hash_slots[slotid]),sizeof(Userslotentry));
        fio.close();
    }
//regist case2    hash的槽位不为空 但只有一个1个key
    if (hash_slots[slotid].loginid != moreslottag)
    {
        slot_number++;
        Userslotentry tmp_entry = hash_slots[slotid];
        hash_slots[slotid].uid = slot_number;
        strcpy(hash_slots[slotid].loginid,moreslottag);
        fio.seekg(sizeof(int) * 3 + sizeof(Userslotentry) * slotid,ios::beg);
        fio.write((char *)&(hash_slots[slotid]),sizeof(Userslotentry));
        fio.seekg(0,ios::end);
        int tmp = 2;
        fio.write((char *)&tmp,sizeof(int));
        fio.write((char *)&tmp_entry,sizeof(Userslotentry));
        tmp_entry.uid = data_number;
        strcpy(tmp_entry.loginid,id);
        fio.write((char *)&tmp_entry,sizeof(Userslotentry));
        fio.close();
    }

//regist case 3   hash的槽位不为空 且已经有多个key储存在其中
    fio.close();
    fio.open(userindex_filename.c_str(),ios::app|ios::out);
    Userslotentry fueler;
    fio.write((char *)&fueler,sizeof(Userslotentry));
    fio.close();
    fio.open(userindex_filename.c_str(),ios::in|ios::out);
    fio.seekg(sizeof(Hashindex_db) + gap,ios::beg);
    int tmp_number = 0;
    fio.read((char *)&tmp_number,sizeof(int));
    tmp_number++;
    fio.seekg(-1 * sizeof(int),ios::cur);
    fio.write((char *)&tmp_number,sizeof(int));
    fio.seekg(sizeof(Userslotentry)*(tmp_number - 1),ios::cur);
    long size_1 = fio.tellg();
    fio.seekg(-1 * sizeof(Userslotentry), ios::end);
    long size_2 = fio.tellg();
    long size = size_2 - size_1;
    fio.seekg(size_1);
    char *buffer;
    buffer = new char[size];
    fio.read(buffer,size);
    fio.seekg(size_1);
    fueler.uid = data_number;
    strcpy(fueler.loginid,id);
    fio.write((char *)&fueler,sizeof(Userslotentry));
    fio.write(buffer,size);
    fio.close();
}

User Userdatabase::get_user(int uid)
{
    fio.open(userdata_filename,ios::in|ios::out);
    fio.seekg((uid - 1)*sizeof(User),ios::beg);
    User tmp_user;
    fio.read((char *)&tmp_user,sizeof(User));
    fio.close();
    return tmp_user;
}

void Userdatabase::init()
{
    fio.open(userdata_filename,ios::in);
    if (!fio)
        fio.open(userdata_filename,ios::out);
    fio.close();
    return;
}

void Userdatabase::add_user(User newer)
{
    fio.open(userdata_filename,ios::out|ios::app);
    fio.write((char *)&newer,sizeof(User));
    fio.close();
    return;
}

Message Messagedatabase::get_message(int mid)
{
    fio.open(messagedata_filename,ios::in|ios::out);
    fio.seekg((uid - 1)*sizeof(Message),ios::beg);
    Message tmp_msg;
    fio.read((char *)&tmp_msg,sizeof(Message));
    fio.close();
    return tmp_msg;
}

void Messagedatabase::init()
{
    fio.open(messagedata_filename,ios::in);
    if (!fio)
        fio.open(messagedata_filename,ios::out);
    fio.close();
    return;
}

void Messagedatabase::add_msg(User new_msg)
{
    fio.open(messagedata_filename,ios::out|ios::app);
    fio.write((char *)&new_msg,sizeof(Message));
    fio.close();
    return;
}
