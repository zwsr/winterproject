#include <iostream>
#include "Database.h"
#include "User.h"
#include "Message.h"
using namespace std;

Hashindex_db userindex_db;
Userdatabase user_db;
Messagedatabase message_db;
Usercache user_cache;
Messagecache msg_cache;

void init_db()
{
    userindex_db.init();
    user_db.init();
    message_db.init();
    return;
}

void main_window()
{
    cout << "----------------Welcome to the SE Community----------------\n";
    cout << "Wish have a good time here!\n";

    cout << "Enter [1] to sign-in!(old user)\n";
    cout << "Enter [2] to sign-up!(new user)\n";
    cout << "Enter [0] to exit this system.\n";
    char tag;
    cin >> tag;
    cin.sync();
    while (true)
    {
        if (tag == '1') break;
        if (tag == '2') break;
        if (tag == '0') break;
        cout << "Please input a right number!\n";
        cin >> tag;
        cin.sync();
    }
    if (tag == '0')
        exit(0);

    User active_user;
    if (tag == '2')
    {
        cout << "Welcom! please input your id you want to register:";
        string new_id;
        cin >> new_id;
        while (new_id.length() >= IDMAXLENGTH )
        {
            cout << "Sorry! Your ID is fairly too long!\n";
            cout << "Input a shorter one:";
            cin >> new_id;
        }
        int jump_tag = 1;
        int new_uid = -1;
        new_uid = userindex_db.registing_id(new_id);
        while (new_uid == -1)
        {
            cout << "Sorry! The ID your want to use has been registered by other before.\n";
            cout << "Enter a new one:";
            cin >> new_id;
            while (new_id.length() >= IDMAXLENGTH )
            {
                cout << "Sorry! Your ID is fairly too long!\n";
                cout << "Input a shorter one:";
                cin >> new_id;
            }
            new_uid = userindex_db.registing_id(new_id);
        }
        User newer;
        newer.registing(new_id,new_uid);
        memcpy(&active_user,&newer,sizeof(User));
    }
    else
    {
        cout << "Welcome back!\n";
        cout << "Input your id:";
        string active_id;

        int active_uid, meaningless;
        int jump_tag2 = 1;
        while (jump_tag2)
        {
            cin >> active_id;
            active_uid = userindex_db.search_loginid(active_id,&meaningless,&meaningless);
            while (active_uid == 0)
            {
                cout << "The ID your want to log-in isn's existed.\n";
                cout << "Enter the ID again:";
                cin >> active_id;
                active_uid = userindex_db.registing_id(new_id);
            }

            if (!user_cache.user[user_cache.get_id(active_uid)].is_active());
            {
                cout << "The account you tried to log-in has been disabled.\n";
                return;
            }
            break;
        }

        User newer(user_cache.user[user_cache.get_id(active_uid)]);
        memcpy(&active_user,&newer,sizeof(User));
    }

    cout << "Hello " << active_user.get_logginid() << "!\n";
    cout << "You can do many things according to below instructions!\n";

    char instr;
    int log_outtag = 1;
    while (log_outtag)
    {
        cin >> instr;
        cin.sync();
        cout << "Enter [1] to deliver a message.\n";
        cout << "Enter [2] to look messages your friends and you delivered.\n";
        cout << "Enter [3] to check the list of users you have followed.\n";
        cout << "Enter [4] to see who are following you.\n";
        cout << "Enter [5] to search user with some condition.\n";
        cout << "Enter [6] to change your password.\n";
        cout << "Enter [0] to log out.\n";

        switch (instr)
        {

        case '1':
            active_user.deliver_message();
            break;
        case '2':
            active_user.check_msg();
            break;


        }



    }




}



int main()
{
    init_db();
    main_window();
    return;
}

