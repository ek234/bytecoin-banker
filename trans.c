#include "./trans.h"
#include <stdlib.h>
#include <stdio.h>
Users __add_trans_in_usr(Users user, Transact transfer)
{
	Transact temp = (Transact)malloc(sizeof(Transaction));
	temp->next = user->T;
	temp->R_UID = transfer->R_UID;
	temp->time.tm_hour = transfer->time.tm_hour;
	temp->time.tm_min = transfer->time.tm_min;
	temp->S_UID = transfer->S_UID;
	temp->tr_amount = transfer->tr_amount;
	user->T = temp;

	return user;
}
Transact transfer(Users *sender, Users *reciver, double amt)
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
