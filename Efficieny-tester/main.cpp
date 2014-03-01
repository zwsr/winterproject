#include <iostream>
#include "Database.h"
#include <sstream>
#include "stdlib.h"
#include "time.h"
using namespace std;
const string test_filename = "Test.dat";

#define MAXLEN 4

char randChar()
{
  const size_t MOD = 128;
  char tmp;
  for (tmp = rand() % MOD;
       tmp != '\0' && !isalnum(tmp) && !ispunct(tmp); tmp = rand() % MOD)
    ;
  return tmp;
}

string randString()
{
  string str;
  char tmp('\0');
  while (tmp == '\0')
    tmp = randChar();
  while (str.length() < MAXLEN - 1 && tmp != '\0')
    {
      str += tmp;
      tmp = randChar();
    }
  return str;
}

#define MAX_DATA 10000
#define TST_NUMBER 10

int main()
{
    srand(time(NULL));
    Hashindex_db test_db;
    test_db.init();
    long start_tag, end_tag;
    double duration;


    string s[MAX_DATA];
    for (int i = 0; i < MAX_DATA; i++)
    {
        string tmp_s = randString();
        s[i] = tmp_s;
    }

    ofstream fo1,fo2;
    fo1.open("Database_Inserting2.txt");
    fo2.open("Database_Searching2.txt");

    int tst_insert[TST_NUMBER] = {10,20,30,50,70,100,150,200,250,500};
    for (int j=0; j < TST_NUMBER; j++)
    {
    test_db.init();
    fo1 << tst_insert[j] << " ";
    fo2 << tst_insert[j] << " ";
    start_tag = clock();
    for (int i = 0; i < tst_insert[j]; i++)
        test_db.registing_id(s[i]);
    end_tag = clock();
    duration = (double)(end_tag - start_tag)/1000.0;

    fo1 << duration << endl;
    cout << duration << endl;

    int ass;
    start_tag = clock();
    for (int i = 0; i <tst_insert[j] ; i++)
        test_db.search_loginid(s[i],&ass,&ass);
    end_tag = clock();
    duration = (double)(end_tag - start_tag)/1000.0;

    fo2 << duration << endl;
    cout << duration << endl;
    }

    return 0;
}

