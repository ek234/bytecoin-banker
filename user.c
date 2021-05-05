#include "./user.h"
#include "./trans.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define digits 1000000;
int __find_id()
{
    int id_num = rand() % digits;
    return id_num;
}
int __check(Users *user_list, int id)
{

    Users temp = user_list[id % func];
    if (temp == NULL)
        return 1;
    else
        return -1;
}
Users __adduser(Users *user_list, Usernext user)
{
    int hash_key = user->UID % func;
    user_list[hash_key] = user;
    return user_list[hash_key];
}
Users register_usr(Users *user_list, double init_val, double value)
{
    int id;
    int check_val;
    time_t t = time(NULL); // stores current is seconds
    do
    {
        id = __find_id();                   //generates unique id
        check_val = __check(user_list, id); //checks id is unique
    } while (check_val == -1);

    /**************************************** 
    *    adds user details in user block    *
    *****************************************/

    Users temp_user = (Users)malloc(sizeof(Users));
    temp_user->balance = init_val / value;
    temp_user->UID = id;
    temp_user->T = NULL;
    temp_user->next = NULL;
    temp_user->join_time = *localtime(&t);

    ///// returns pointer to newly registered users details
    return __adduser(user_list, temp_user);
}

//takes pointer to new list and double the maximum no of users
void double_user(Users *user_list)
{
    Users new_list = (Users)malloc(2 * func * sizeof(UserList));
    func *= 2;
    for (unsigned int i = 0; i < func / 2; ++i)
    {
        if (user_list[i] != NULL)
            __adduser(&new_list, user_list[i]);
    }
    free(user_list);
    user_list = &new_list;
}
Users find_user(Users *user_list, int id)
{
    if (__check(user_list, id) == 1)
        return NULL; ////return NULL if id is wrong
    int hash_key = id % func;
    return user_list[hash_key];
}

double delete_user(Users *user_list, int id, double value)
{
    int hash_key = id % func;
    Users temp = user_list[hash_key];
    double bal = temp->balance * value;
    free(temp);
    return bal;
}
/* int main()
{
    printf("hello world\n");
} */