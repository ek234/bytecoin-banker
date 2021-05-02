#include "./trans.h"
#include <stdlib.h>
#include <stdio.h>
Users __add_trans_in_usr(Users user, Transact transfer)
{
    Transact temp = user->T;
    if (temp == NULL)
    {
        temp = (Transact)malloc(sizeof(Transaction));
        temp->next = NULL;
        temp->tr_amount = 0;
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = transfer;
    return user;
}
Transact tarnsfer(Users *sender, Users *reciver, double amt)
{
    //condition if sufficient bal is avaliable
    Users temp_s = *sender, temp_r = *reciver;

    if (temp_s->balance < amt || *sender == NULL || *reciver == NULL)

        return NULL; //return null pointer if amount is not present

    time_t t = time(NULL); // stores current is seconds

    temp_s->balance -= amt;
    temp_r->balance += amt;

    Transact temp = (Transact)malloc(sizeof(Transaction));
    temp->R_UID = temp_r->UID;
    temp->S_UID = temp_s->UID;
    temp->tr_amount = amt;
    temp->time = *localtime(&t);
    temp->next = NULL;

    temp_s = __add_trans_in_usr(temp_s, temp);
    temp_r = __add_trans_in_usr(temp_r, temp);
    *sender = temp_s;
    *reciver = temp_r;

    // return address of transaction so that is can be adden in block chain
    return temp;
}
/* int main()
{
    printf("hello world\n");
} */