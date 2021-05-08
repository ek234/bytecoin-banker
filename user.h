#ifndef __USER_H__
#define __USER_H__
#include "./bitcoin.h"
typedef struct tm _time;
typedef Usernext Users;
unsigned int usr_no;

Users register_usr(Users *user_list, double init_val, double value);
double delete_user(Users *user_list, int id, double value);
void double_user(Users *user_list);
Users find_user(Users *user_list, int id);

#endif
