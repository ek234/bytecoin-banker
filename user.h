#ifndef __USER_H__
#define __USER_H__
#include "./bytecoin.h"
typedef struct tm _time;
typedef Usernext Users;
extern unsigned int usr_no;

Users register_usr(Users *user_list, double init_val, double value, unsigned int usr_no);
int mine(Users user);
double delete_user(Users *user_list, int id, double value, unsigned int usr_no);
void double_user(Users *user_list, unsigned int* usr_no);
Users find_user(Users *user_list, int id, unsigned int usr_no);

#endif
