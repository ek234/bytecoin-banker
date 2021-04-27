#include "./user.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int __find_id()
{
    srand(time(NULL));
    int id_num = rand() % 1000;
    return id_num;
}
int __check(Users user_list[], int hash_key)
{
    Users temp = user_list[hash_key];
    if (temp == NULL)
        return 1;
    else
        return -1;
}
Users register_usr(Users user_list[], double init_bal)
{
    int id;
    int check_val;
    time_t t = time(NULL); // stores current is seconds
    do
    {
        id = __find_id();                   //generates unique id
        check_val = __check(user_list, id); //checks id is unique
    } while (check_val == -1);

    int hash_key = id;
    Users temp = user_list[hash_key];

/****************************************** 
/*    adds user details in user directory *
/******************************************/

    user_list[hash_key] = (Users)malloc(sizeof(UserList));
    user_list[hash_key]->balance = 0;

    Users temp_user = (Users)malloc(sizeof(Users));
    temp_user->balance = init_bal;
    temp_user->UID = id;

    temp_user->join_time = *localtime(&t);   //ask ishan to change the struct  

    
    temp = temp_user;
    return user_list;
}
double delete_user(Users user_list[], int id)
{
    double bal = user_list[id]->balance;
    Users temp = user_list[id];
    free(temp);
    return bal;
}
