#include "./user.h"
#include "./trans.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define digits 10000000;
#define MINE_AMOUNT 10
static double coin_left = 10000000000; //fixed no of bytecoins
int __find_id()
{
    int id_num = rand() % digits;
    return id_num;
}
int __check(Users *user_list, int id, unsigned int usr_no)
{

    Users temp = user_list[id % usr_no];
    if (temp == NULL && id != 0)
        return 1;
    else
        return -1;
}
Users __adduser(Users *user_list, Usernext user, unsigned int usr_no)
{
    int hash_key = user->UID % usr_no;
    user_list[hash_key] = user;
    return user_list[hash_key];
}
Users register_usr(Users *user_list, double init_val, double value, unsigned int usr_no)
{
    int id;
    int check_val;
    time_t t = time(NULL); // stores current is seconds
    do
    {
        id = __find_id();                   //generates unique id
        check_val = __check(user_list, id, usr_no); //checks id is unique
    } while (check_val == -1);

    /**************************************** 
    *    adds user details in user block    *
    *****************************************/
    if (coin_left < init_val / value)
        return NULL;
    Users temp_user = (Users)malloc(sizeof(UserList));
    temp_user->balance = init_val / value;
    coin_left -= temp_user->balance;
    temp_user->UID = id;
    temp_user->T = NULL;
    temp_user->join_time = *localtime(&t);

    ///// returns pointer to newly registered users details
    Users return_val = __adduser(user_list, temp_user, usr_no);
    return return_val;
}

//takes pointer to new list and double the maximum no of users
void double_user(Users *user_list, unsigned int* usr_no)
{
    Users new_list = (Users)malloc(2 * *usr_no * sizeof(UserList));
    *usr_no *= 2;
    for (unsigned int i = 0; i < *usr_no / 2; ++i)
    {
        if (user_list[i] != NULL)
            __adduser(&new_list, user_list[i], *usr_no);
    }
    free(user_list);
    user_list = &new_list;
}

int mine(Users user)
{
    // if no more coins are left
    if (coin_left < MINE_AMOUNT)
        return -1;

    int success = rand() % 2;

    // if mine is not successful
    if (success == 0)
        return 0;

    // otherwise:
    user->balance += MINE_AMOUNT;

    return 1;
}

Users find_user(Users *user_list, int id, unsigned int usr_no)
{
    if (id <= 0)
        return NULL;
    if (__check(user_list, id, usr_no) == 1)
        return NULL; ////return NULL if id is wrong
    int hash_key = id % usr_no;
    return user_list[hash_key];
}

double delete_user(Users *user_list, int id, double value, unsigned int usr_no)
{
    int hash_key = id % usr_no;
    Users temp = user_list[hash_key];
    if (temp == NULL)
        return -1.00;
    double bal = temp->balance * value;
    coin_left += temp->balance;
    user_list[hash_key] = NULL;
    free(temp);
    return bal;
}
