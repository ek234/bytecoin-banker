#ifndef __USER_H__
#define __USER_H__
typedef struct user user;
typedef user* ptr_user;
struct user{
    char id[24];
    char name[20];
    unsigned long int bal;
    //transaction list;
    user* next;
};
ptr_user register_usr(ptr_user user_list,char name[] ,unsigned long int bal);


#endif __USER_H__