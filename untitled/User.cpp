#include <iostream>
#include "User.h"
#include "Message.h"
#include "Database.h"
#include "stdlib.h"
#include <sstream>
using namespace std;

extern Messagedatabase message_db;

User::User()
{
}

void User::add_msg(int mid)
{
    fstream fio;
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
    return;
}

void User::deliver_message()
{
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
   Message new_msg(msgcontent,uid,0);
   int newmsg_mid = message_db.add_msg(new_msg);
   add_msg(newmsg_mid);
   cout << "You succeeded delivered a message!\n";
   return;
}

void User::change_name()
{
    cout << "Input a new name(less than 10 characters):";
    string name_tmp;
    cin >> name_tmp;
    while (name_tmp.length() > 10)
    {
        cout << "Input a shorter name plz!\n";
        cout << "Input a new name(less than 10 characters):";
        cin >> name_tmp;
    }
    strcpy(name,name_tmp.c_str());

    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + NAME,ios::beg);
    fio.write(name,sizeof(name));
    fio.close();
    return;
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

    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + BIRTH,ios::beg);
    fio.write(birth,sizeof(birth));
    fio.close();
    return;
}

void User::change_gender()
{
    cout << "Input your male(0 for female,1 for male):";
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
        cout << "Input your male(0 for female,1 for male):";
        cin >> tmp;
    }

    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + GENDER,ios::beg);
    fio.write((char *)&gender,sizeof(bool));
    fio.close();
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

    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + PHONENBR,ios::beg);
    fio.write(phonenumber,sizeof(phonenumber));
    fio.close();
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

    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + HOMETOWN,ios::beg);
    fio.write(hometown,sizeof(hometown));
    fio.close();
    return;
}


void User::change_information()
{
    cout << "Follow instructions below to continue:\n";
    char tmp;
    while (true)
    {
        cout << "Press [1] to change name.\n";
        cout << "Press [2] to change birthday.\n";
        cout << "Press [3] to change gender.\n";
        cout << "Press [4] to change phonenumber.\n";
        cout << "Press [5] to change hometown.\n";
        cout << "Press [0] to end changing your profile.\n";

        cin >> tmp;
        cin.sync();

        switch (tmp)
        {
        case '1':
            change_name();
            break;
        case '2':
            change_birthday();
            break;
        case '3':
            change_gender();
            break;
        case '4':
            change_phonenumber();
            break;
        case '5':
            change_hometown();
            break;
        case '0':
            return;
            break;
        default:
            cout << "Plz input a right number!\n";
            break;
        }
        cout << "Successful!\n";
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

    fstream fio;
    fio.open(userdata_filename,ios::out|ios::in);
    fio.seekg(sizeof(user) * (uid - 1) + PSD,ios::beg);
    fio.write(birth,sizeof(birth));
    fio.close();
    return;
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

    char tag;
    cin >> tag;
    cin.sync();
    if (tag != 'y')
    {
        cout << "Your account is still alive!\n";
        return;
    }

    is_disableuser = true;


}

