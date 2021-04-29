#ifndef __USER_H__
#define __USER_H__
#include <./bitcoin.h>
typedef struct tm _time;

Users register_usr(Users user_list[], double init_val, double value);
double delete_user(Users user_list[], int id, double value);

#endif __USER_H__