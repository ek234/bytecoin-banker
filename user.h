#ifndef __USER_H__
#define __USER_H__
#include <./bitcoin.h>
typedef struct tm _time;

Users register_usr(Users user_list[] ,double bal);
double delete_user(Users user_list[],int id);


#endif __USER_H__