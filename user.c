#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int __find_id(char name[], char id[])
{
    srand(time(NULL));
    int len = strlen(name);
    strcpy(id, name);
    int id_num = rand() % 1000;
    int num = 10;
    for (int i = len + 2; i >= len; --i)
    {
        id[i] = (id_num % num) / (num / 10);
        num *= 10;
    }
    id[len + 3] = '\0';
    return id_num;
}
int __check(ptr_user user_list[], int hash_key, char id[])
{
    ptr_user temp = user_list[hash_key];
    if (temp == NULL)
        return 1;
    else
    {
        while (temp->next != NULL)
        {
            if (strcmp(temp->next->id, id) == 0)
                return -1;
            temp = temp->next;
        }
    }
    return 1;
}
ptr_user register_usr(ptr_user user_list[], char name[], unsigned long int init_bal)
{
    char id[24];
    int check_val;
    int hash_key;
    do
    {
        hash_key = __find_id(name, id);
        check_val = __check(user_list, hash_key, id);
    } while (check_val == -1);
    ptr_user temp = user_list[hash_key];
    if (user_list[hash_key] == NULL)
    {
        user_list[hash_key] = (ptr_user)malloc(sizeof(user));
        user_list[hash_key]->bal = 0;
        user_list[hash_key]->next = NULL;
    }

    while (temp->next != NULL)
        temp = temp->next;
    ptr_user uid = (ptr_user)malloc(sizeof(user));
    uid->bal = init_bal;
    strcpy(uid->id, id);
    strcpy(uid->name, name);
    uid->next = NULL;
    temp->next = uid;
    return user_list;
}