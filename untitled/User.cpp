#include <iostream>
#include "User.h"
#include "Message.h"
#include "Database.h"
#include "stdlib.h"
#include <sstream>
#include <algorithm>
using namespace std;

extern Hashindex_db userindex_db;
extern Userdatabase user_db;
extern Messagedatabase message_db;
extern Usercache user_cache;
extern Messagecache msg_cache;

User::User()
{
}

void User::add_msg(int mid)
{
    fstream fio;
    message_delieverd[0]++;
    message_delieverd[message_delieverd[0]] = mid;
/*
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + MSG_DLVD,ios::beg);
    int cur_msg_number = 0;
    fio.read((char *)&cur_msg_number,sizeof(int));
    fio.seekg(-1 * sizeof(int),ios::cur);
    cur_msg_number++;
    fio.write((char *)&cur_msg_number,sizeof(int));
    fio.seekg(sizeof(int) * (cur_msg_number - 1),ios::cur);
    fio.write((char *)&mid,sizeof(int));
    fio.close();
/*/
    return;
}

void User::deliver_message()
{
    if (message_delieverd[0] >= MESSAGEDELIVERINGMAX)
    {
        cout << "You have delivered too much message!\n";
        cout << "Fail to deliver a message.\n";
        return;
    }
    cout << "Please input the message you want to deliver(less than 138 characters)\n"
         << "Enter RETURN to complete your input!\n";

    string msgcontent;
    cin >> msgcontent;
    while (msgcontent.length() >= 138)
    {
        cout << "Your message is too long!\n";
        cout << "Please input the message you want to deliver(less than 138 characters)\n"
             << "Enter RETURN to complete your input!\n";
        cin >> msgcontent;
    }
   Message new_msg(msgcontent,uid,0,name);
   int newmsg_mid = message_db.add_msg(new_msg);

   add_msg(newmsg_mid);
   cout << "You succeeded to delivered a message!\n";
   return;
}

void User::change_name()
{
    cout << "Input your name(less than 10 characters):";
    string name_tmp;
    cin >> name_tmp;
    while (name_tmp.length() > 10)
    {
        cout << "Input a shorter name plz!\n";
        cout << "Input your name(less than 10 characters):";
        cin >> name_tmp;
    }
    strcpy(name,name_tmp.c_str());
/*
    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + NAME,ios::beg);
    fio.write(name,sizeof(name));
    fio.close();
    return;
/*/
}

void User::change_birthday()
{
    cout << "Input your birthday(xx/xx/xx):";
    string tmp;
    cin >> tmp;
    while (true)
    {
        int count = 0;
        for (int i = 0;i < tmp.length();i++)
            if (tmp[i] = '/') count++;
        if (count == 2) break;
        cout << "Input the right form!\n";
        cout << "Input your birthday(xx/xx/xx):";
        cin >> tmp;
    }
    strcpy(birth,tmp.c_str());
/*
    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + BIRTH,ios::beg);
    fio.write(birth,sizeof(birth));
    fio.close();
/*/
    return;
}

void User::change_gender()
{
    cout << "Input your gender(0 for female,1 for male):";
    char tmp;
    cin >> tmp;
    while (true)
    {
        cin.sync();
        if (tmp == '0')
        {
            gender = false;
            break;
        }
        if (tmp == '1')
        {
            gender = true;
            break;
        }

        cout << "Input the right alpha!\n";
        cout << "Input your gender(0 for female,1 for male):";
        cin >> tmp;
    }
/*
    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + GENDER,ios::beg);
    fio.write((char *)&gender,sizeof(bool));
    fio.close();
/*/
    return;
}

void User::change_phonenumber()
{
    cout << "Input your phonenumber(less than 15 characters):";
    string tmp;
    cin >> tmp;
    while (tmp.length() > 15)
    {
        cout << "Input a shorter number plz!\n";
        cout << "Input your phonenumber(less than 15 characters):";
        cin >> tmp;
    }
    strcpy(phonenumber,tmp.c_str());

/*
    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + PHONENBR,ios::beg);
    fio.write(phonenumber,sizeof(phonenumber));
    fio.close();
/*/
    return;
}

void User::change_hometown()
{
    cout << "Input your hometown(less than 9 characters):";
    string tmp;
    cin >> tmp;
    while (tmp.length() > 9)
    {
        cout << "Input a shorter hometown plz!\n";
        cout << "Input your hometown(less than 9 characters):";
        cin >> tmp;
    }
    strcpy(hometown,tmp.c_str());
/*
    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + HOMETOWN,ios::beg);
    fio.write(hometown,sizeof(hometown));
    fio.close();
/*/
    return;
}


void User::change_information()
{
    cout << "Follow instructions below to continue:\n";
    char tmp;
    while (true)
    {
        cout << "Enter [1] to change name.\n";
        cout << "Enter [2] to change birthday.\n";
        cout << "Enter [3] to change gender.\n";
        cout << "Enter [4] to change phonenumber.\n";
        cout << "Enter [5] to change hometown.\n";
        cout << "Enter [0] to end changing your profile.\n";

        cin >> tmp;
        cin.sync();

        switch (tmp)
        {
        case '1':
            change_name();
            cout << "Successful!\n";
            break;
        case '2':
            change_birthday();
            cout << "Successful!\n";
            break;
        case '3':
            change_gender();
            cout << "Successful!\n";
            break;
        case '4':
            change_phonenumber();
            cout << "Successful!\n";
            break;
        case '5':
            change_hometown();
            cout << "Successful!\n";
            break;
        case '0':
            return;
            break;
        default:
            cout << "Plz input a right number!\n";
            break;
        }
    }
    return;
}

void User::change_password()
{
    cout << "Enter your old password:";
    string tmp;
    cin >> tmp;
    if ( tmp != password)
    {
        cout << "Password Wrong!\n"
             << "Changing Failed!\n";
        return;
    }

    cout << "Password Right!\n";\

    while (true)
    {
    cout << "Enter your new password(less than 16 characters):";
    cin >> tmp;

    while (tmp.length()>15)
    {
        cout << " Your password is too long!\n";
        cout << "Enter your new password(less than 16 characters):";\
        cin >> tmp;
    }

    string tmp_2;
    cout << "Re-enter your new password:";
    cin >> tmp_2;

    if (tmp == tmp_2)
        break;

    cout << "Thay are not the same! Plz do input again.\n";
    }

    strcpy(password,tmp.c_str());
/*
    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + PSD,ios::beg);
    fio.write(birth,sizeof(birth));
    fio.close();
    return;
/*/
}

void User::disable_account()
{
    cout << "You are disabling your account now!\n"
         << "Enter 'y' to continue,or go back to the menu:";
    char tag;
    cin >> tag;
    cin.sync();
    if (tag != 'y')
    {
        cout << "Your account is still alive!\n";
        return;
    }

    cout << "Enter your password:\n";
    string tmp;
    cin >> tmp;

    if ( tmp != password )
    {
        cout << "Password Wrong!\n";
        cout << "Your account is still alive!\n";
        return;
    }

    cout << "It's the last time that we inform you that your account can't be used or registered anymore!\n"
         << "Enter 'y' to disable your account,or go back to the menu:";

    cin >> tag;
    cin.sync();
    if (tag != 'y')
    {
        cout << "Your account is still alive!\n";
        return;
    }

    is_disableuser = true;
    log_out();
    cout << "Your account has been disabled.\n";
/*

/*/
    return;
}

void User::follow_someone(int u)
{
    int is_followed = 0;
    for (int i = 0; i <= user_followed[0]; i++)
        if (u == user_followed[i])
        {
            is_followed = 1;
            break;
        }
    if (is_followed)
    {
        cout << "You have followd the user before!\n";
        return;
    }

    if (user_followed >= FOLLOWEOTHERMAX)
    {
        cout << "You have followed too many guys!\n";
        cout << "Follow failed.\n";
        return;
    }


    user_followed[0]++;
    user_followed[user_followed[0]] = u;
    int target_cacheid = 0;
    target_cacheid = user_cache.get_id(u);
    user_cache.user[target_cacheid].user_following_me[0]++;
    user_cache.user[target_cacheid].user_following_me[user_cache.user[target_cacheid].user_following_me[0]];
    user_cache.writeback_id(target_cacheid);
    cout << "Follow " << user_cache.user[target_cacheid].name <<"successful!\n";
    return;
}

void User::unfollow_someone(int tagid)
{
    int target_uid = user_followed[tagid];
    user_followed[tagid]= user_followed[user_followed[0]];
    user_followed[user_followed[0]] = 0;
    user_followed[0]--;
    int target_cacheid = user_cache.get_id(target_uid);

    int self_tagid = 0;
    for (int i = 1; i <= user_cache.user[target_cacheid].user_following_me[0];i++)
        if (uid == user_cache.user[target_cacheid].user_following_me[i] )
        {
            self_tagid = i;
            break;
        }
    user_cache.user[target_cacheid].user_following_me[self_tagid] = user_cache.user[target_cacheid].user_following_me[user_cache.user[target_cacheid].user_following_me[0]];
    user_cache.user[target_cacheid][user_cache.user[target_cacheid].user_following_me[0]] = 0;
    user_cache.user[target_cacheid].user_following_me[0]--;
    user_cache.writeback_id(target_cacheid);
    cout << "unfollow" << user_cache.user[target_cacheid].name <<" successful!\n";
    return;
}


void User::check_i_followed_who_list()
{
    cout << "You have followed these users:\n";
    for (int i = 1; i <= user_followed[0]; i++)
    {
        cout << i <<".";
        int tag_id = user_cache.get_id(user_followed[i]);
        if (user_cache.user[tag_id].is_active())
                cout << user_cache.user[tag_id].get_logginid() << endl;
        else cout << "**THE USER HAS DISABLED HIS ACCOUNT**\n";
    }

    cout << "Follow instructions below to continue:\n";
    char tag;
    cin >> tag;
    cin.sync();

    int jumpout_tag = 1;
    while (jumpout_tag)
    {
        cout << "Enter [1] to check someone's messagelist from left-tag above.\n";
        cout << "Enter [2] to unfollow someone from left-tag above.\n";
        cout << "Enter [3] to recheck the list of whom you are following.\n";
        cout << "Enter [0] to go back to menu.\n";

        switch (tag)
        {
        case '1':
        {
            int looking_tag;
            cout << "Enter the left-tag shown above who you want to check:";
            cin >> looking_tag;
            while (!cin.good())
            {
                cout << "Plz input a number!\n";
                cin.clear();
                cin.sync();
                cin >> looking_tag;
            }
            while ( (looking_tag <= 0)&&(looking_tag >= user_following_me[0] ) )
            {
                cout << "please input a right left-tag shown above!\n";
                cin >> looking_tag;
                while (!cin.good())
                {
                    cout << "Plz input a number!\n";
                    cin.clear();
                    cin.sync();
                    cin >> looking_tag;
                }
            }

            User thetarget(user_cache[user_cache.get_id(user_following_me[looking_tag])]);
            for (int i = thetarget.message_delieverd[0];i > 0;i--)
                cout << msg_cache.msg[msg_cache.get_id(thetarget.message_delieverd[i])] << endl;

            cout << "Enter any key to back\n";
            string tmp;
            cin >> tmp;
            break;
        }
        case '2':
        {
            int looking_tag;
            cout << "Enter the left-tag shown above who you want to check:";
            cin >> looking_tag;
            while (!cin.good())
            {
                cout << "Plz input a number!\n";
                cin.clear();
                cin.sync();
                cin >> looking_tag;
            }
            while ( (looking_tag <= 0)&&(looking_tag >= user_following_me[0] ) )
            {
                cout << "please input a right left-tag shown above!\n";
                cin >> looking_tag;
                while (!cin.good())
                {
                    cout << "Plz input a number!\n";
                    cin.clear();
                    cin.sync();
                    cin >> looking_tag;
                }
            }

            int to_follower_uid;
            to_follower_uid = user_following_me[looking_tag];
            follow_someone(to_follower_uid);
            cout << "Enter any key to back\n";
            string tmp;
            cin >> tmp;
            break;
        }
        case '3':
        {
            cout << "You have followed these users:\n";
            for (int i = 1; i <= user_followed[0]; i++)
            {
                cout << i <<".";
                int tag_id = user_cache.get_id(user_followed[i]);
                if (user_cache.user[tag_id].is_active())
                        cout << user_cache.user[tag_id].get_logginid() << endl;
                else cout << "**THE USER HAS DISABLED HIS ACCOUNT**\n";
            }

            cout << "Follow instructions below to continue:\n";
            break;
        }
        case '0':
        {
            jumpout_tag = 0;
            break;
        }
        default:
            cout << "Plz input a right number!\n";
            cin >> tag;
            cin.sync();
            break;
        }
    }

    return;
}

void User::check_i_am_followed_by_who_list()
{
    cout << "These guys are following:\n";
    for (int i = 1; i <= user_following_me[0]; i++)
    {
        cout << i <<".";
        int tag_id = user_cache.get_id(user_following_me[i]);
        if (user_cache.user[tag_id].is_active())
                cout << user_cache.user[tag_id].get_logginid() << endl;
        else cout << "**THE USER HAS DISABLED HIS ACCOUNT**\n";
    }

    cout << "Follow instructions below to continue:\n";
    char tag;


    int jumpout_tag = 1;
    while (jumpout_tag)
    {
        cout << "Enter [1] to check someone's messagelist from left-tag above.\n";
        cout << "Enter [2] to follow someone from left-tag above.\n";
        cout << "Enter [3] to recheck the list of who are following you.\n";
        cout << "Enter [0] to go back to menu.\n";

        cin >> tag;
        cin.sync();
        switch (tag)
        {
        case '1':
        {
            int looking_tag;
            cout << "Enter the left-tag shown above who you want to check:";
            cin >> looking_tag;
            while (!cin.good())
            {
                cout << "Plz input a number!\n";
                cin.clear();
                cin.sync();
                cin >> looking_tag;
            }
            while ( (looking_tag <= 0)&&(looking_tag >= user_followed[0] ) )
            {
                cout << "please input a right left-tag shown above!\n";
                cin >> looking_tag;
                while (!cin.good())
                {
                    cout << "Plz input a number!\n";
                    cin.clear();
                    cin.sync();
                    cin >> looking_tag;
                }
            }

            User thetarget(user_cache[user_cache.get_id(user_followed[looking_tag])]);
            for (int i = thetarget.message_delieverd[0];i > 0;i--)
                cout << msg_cache.msg[msg_cache.get_id(thetarget.message_delieverd[i])] << endl;

            cout << "Enter any key to back\n";
            string tmp;
            cin >> tmp;
            break;
        }
        case '2':
        {
            int looking_tag;
            cout << "Enter the left-tag shown above who you want to check:";
            cin >> looking_tag;
            while (!cin.good())
            {
                cout << "Plz input a number!\n";
                cin.clear();
                cin.sync();
                cin >> looking_tag;
            }
            while ( (looking_tag <= 0)&&(looking_tag >= user_followed[0] ) )
            {
                cout << "please input a right left-tag shown above!\n";
                cin >> looking_tag;
                while (!cin.good())
                {
                    cout << "Plz input a number!\n";
                    cin.clear();
                    cin.sync();
                    cin >> looking_tag;
                }
            }

            unfollow_someone(looking_tag);
            cout << "Enter any key to back\n";
            string tmp;
            cin >> tmp;
            break;
        }
        case '3':
        {
            cout << "These guys are following:\n";
            for (int i = 1; i <= user_following_me[0]; i++)
            {
                cout << i <<".";
                int tag_id = user_cache.get_id(user_following_me[i]);
                if (user_cache.user[tag_id].is_active())
                        cout << user_cache.user[tag_id].get_logginid() << endl;
                else cout << "**THE USER HAS DISABLED HIS ACCOUNT**\n";
            }
            break;
        }
        case '0':
        {
            jumpout_tag = 0;
            break;
        }
        default:
            cout << "Plz input a right number!\n";
            cin >> tag;
            cin.sync();
            break;
        }
    }

    return;
}

void User::check_msg()
{
    int msg_tmpamout[10000000];
    int msg_number = 0;
    for (int i = 0; i <= user_followed[0]; i++)
    {
        if (i == 0)
        {
            for (int j = 1; j <= message_delieverd[0];j++)
            {
                msg_tmpamout[msg_number] = message_delieverd[j];
                msg_number++;
            }
            continue;
        }
        int tagid = user_cache.get_id(user_followed[i]);
        int ones_msg_number = user_cache.user[tagid].message_delieverd[0];
        for (int j = 1;j <= ones_msg_number; j++)
        {
            msg_tmpamout[msg_number] = user_cache.user[tagid].message_delieverd[j];
            msg_number++;
        }
    }
    int* msg_amout;
    msg_amout = new int[msg_number];
    memcpy(msg_amout,msg_tmpamout,sizeof(int) * msg_number);
    sort(msg_amout,msg_amout+msg_number);

    int tmp_number =msg_number;

    if ( msg_number <= 30 )
    {
    for (int i = msg_number-1; i >=0 ; i--)
        cout << "Tag-" << i <<":" << msg_cache.msg[msg_cache.get_id(msg_amout[i])] << endl;
    cout << "That's all.\n";

    char tag;
    int jmp_tag = 1;
    while (jmp_tag)
    {
        cout << "Enter [1] to tranfer a message according to above tag.\n";
        cout << "Enter [0] to go back to menu.\n";

        cin >> tag;
        cin.sync();

        switch (tag)
        {
        case '1':
            cout << "Choose the message you want to tranfer via inputing tag shown above:\n";

            int msg_tag;
            cin >> msg_tag;
            while (!cin.good())
            {
                cout << "Plz input a number!\n";
                cin.clear();
                cin.sync();
                cin >> msg_tag;
            }
            while ( (msg_tag <= 0)&&(msg_tag >= user_following_me[0] ) )
            {
                cout << "please input a right left-tag shown above!\n";
                cin >> msg_tag;
                while (!cin.good())
                {
                    cout << "Plz input a number!\n";
                    cin.clear();
                    cin.sync();
                    cin >> msg_tag;
                }
            }


        }

    }
    }
    else
    {

    }


    delete msg_amout;
    return;
}

void User::seek_user()
{
    cout << "Follow instructions below to continue:\n";
    char tag;

    int jumpout_tag = 1;
    while (jumpout_tag)
    {
        cout << "Enter [1] to search user via ID specified.\n";
        cout << "Enter [2] to search user via UID specified.\n";
        cout << "Enter [0] to go back to menu.\n";
        cin >> tag;
        cin.sync();

        switch (tag)
        {
        case '1':
        {
            string search_id;
            cout << "Please input the id who you are searching:";
            cin >> search_id;
            int meaningless;
            int geted_uid = userindex_db.search_loginid(search_id,&meaningless,&meaningless);
            if (geted_uid == 0)
            {
                cout << "User not found!\n";
                break;
            }
            int tagid = user_cache.get_id(geted_uid);
            cout << "Succeeded to find the user:"
                 << user_cache.user[tagid].name
                 << endl;

            int jumpout_tag2 = 1;
            while (jumpout_tag2)
            {
            cout << "Enter [1] to follow him.\n";
            cout << "Enter [0] to go back to semi-menu.\n";
            char tag_2;
            cin >> tag_2;

            switch (tag_2)
            {
            case '1':
                follow_someone(geted_uid);
                break;
            case '0':
                jumpout_tag2 = 0;
                break;
            default:
                cout << "Plz input a right number!\n";
                break;
            }
            }
        }
        case '2':
        {
            cout << "Please input the uid that you want to search:";
            int uid_nbr;
            while(true)
            {
                string tmp_s;
                cin >> tmp_s;
                uid_nbr = atoi(tmp_s.c_str());
                stringstream cmp_s;
                cmp_s << uid_nbr;
                if (cmp_s.str() != tmp_s)
                {
                    cout << "Please input a number!\n";
                    continue;
                }
                break;
            }

            if (uid_nbr > userindex_db.get_data_number())
            {
                cout << "User not found!\n";
                break;
            }

            int geted_uid = uid_nbr;
            int tagid = user_cache.get_id(geted_uid);
            cout << "Succeeded to find the user:"
                 << user_cache.user[tagid].name
                 << endl;


            int jumpout_tag2 = 1;
            while (jumpout_tag2)
            {
            cout << "Enter [1] to follow him.\n";
            cout << "Enter [0] to go back to semi-menu.\n";
            char tag_2;
            cin >> tag_2;

            switch (tag_2)
            {
            case '1':
                follow_someone(geted_uid);
                break;
            case '0':
                jumpout_tag2 = 0;
                break;
            default:
                cout << "Plz input a right number!\n";
                break;
            }
            }
        }
        case '0':
            jumpout_tag = 0;
            break;
        default:
            cout << "Plz input a right number!\n";
            break;
        }
    }
    return;
}

void User::trans_message(int mid)
{
    if (message_delieverd[0] >= MESSAGEDELIVERINGMAX)
    {
        cout << "You have delivered too much message!\n";
        cout << "Fail to deliver a message.\n";
        return;
    }
    cout << "Please input some comment ont the message(less than 138 characters with the old message)\n"
         << "Enter RETURN to complete your input!\n";
    string msg_commnet,msg_formalcontent;

    cin >> msg_commnet;
    msg_formalcontent = msg_cache.msg[msg_cache.get_id(mid)].packed_tranferedcontent();


    string msgcontent = msg_commnet + "  " + msg_formalcontent;
    cin >> msgcontent;
    while (msgcontent.length() >= 138)
    {
        cout << "Your comment is too long!\n";
        cout << "Please input some comment ont the message(less than 138 characters with the old message)\n"
             << "Enter RETURN to complete your input!\n";
        cin >> msg_commnet;
        msgcontent = msg_commnet + "  " + msg_formalcontent;
    }

    Message new_msg(msgcontent,uid,mid,name);
    int newmsg_mid = message_db.add_msg(new_msg);

    add_msg(newmsg_mid);
    cout << "You succeeded to delivered a message!\n";
    return;
}

void User::registing(string logid, int u)
{
    strcpy(loginid,logid);
    uid = u;

    while (true)
    {
    cout << "Please input your password(less than 16 characters):";
    cin >> tmp;

    while (tmp.length()>15)
    {
        cout << " Your password is too long!\n";
        cout << "Please input your password(less than 16 characters):";
        cin >> tmp;
    }

    string tmp_2;
    cout << "Re-enter your new password:";
    cin >> tmp_2;

    if (tmp == tmp_2)
        break;

    cout << "Thay are not the same! Plz do input again.\n";
    }
    strcpy(password,tmp.c_str());

    cout << "Now,please file some basic information, it's neccessary.\n";
    change_name();
    change_birthday();
    change_gender();
    cout << "Would you mind filling some extrainformation?\n";
    cout << "Enter [n] for Nope,other for yes.\n";
    char tag;
    cin >> tag;
    cin.sync();
    if (tag != 'n')
    {
        change_phonenumber();
        change_hometown();
    }

    user_db.add_user(*this);
    cout << "You have finished the Registration, now you will log in automatically.\n";
    return;
}

int User::log_in()
{
    cout << "Please input your password:";
    string psd;
    cin >> psd;
    if (psd == password)
        return 0;
    return -1;
}\

int User::log_out()
{
    user_db.writeback_user(uid,*this);
    cout << "You have successfully logged out!\n";
    return;

}



