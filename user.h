#ifndef __USER_H__
#define __USER_H__
typedef struct user user;
typedef user* ptr_user;
typedef struct tm _time;
struct user{
    int id;
    char name[20];
    unsigned long int bal;
    _time reg_time;
    //transaction list;
};
ptr_user register_usr(ptr_user user_list,char name[] ,unsigned long int bal);

#endif __USER_H__