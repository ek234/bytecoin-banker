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
int __check(ptr_user user_list[], int hash_key)
{
    ptr_user temp = user_list[hash_key];
    if (temp == NULL)
        return 1;
    else
        return -1;
}
ptr_user register_usr(ptr_user user_list[], char name[], unsigned long int init_bal)
{
    int id;
    int check_val;
    time_t t = time(NULL);
    do
    {
        id = __find_id();
        check_val = __check(user_list, id);
    } while (check_val == -1);
    int hash_key = id;
    ptr_user temp = user_list[hash_key];

    user_list[hash_key] = (ptr_user)malloc(sizeof(user));
    user_list[hash_key]->bal = 0;

    ptr_user temp_user = (ptr_user)malloc(sizeof(user));
    temp_user->bal = init_bal;
    temp_user->id = id;
    strcpy(temp_user->name, name);
    temp_user->reg_time = *localtime(&t);
    temp = temp_user;
    return user_list;
}
unsigned long int delete_user(ptr_user user_list, int id)
{
    unsigned long int bal = user_list[id].bal;
    ptr_user temp = &user_list[id];
    free(temp);
    return bal;
}
