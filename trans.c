#include <./trans.h>

void __add_trans_in_usr(UserList *user, Transact transfer)
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
}
Transact *tarnsfer(UserList *sender, UserList *reciver, double amt)
{
    //condition if sufficient bal is avaliable
    if (sender->balance < amt)

        return NULL; //return null pointer if amount is not present

    time_t t = time(NULL); // stores current is seconds

    sender->balance -= amt;
    reciver->balance += amt;

    Transact temp = (Transact)mallco(sizeof(Transaction));
    temp->R_UID = reciver->UID;
    temp->S_UID = sender->UID;
    temp->tr_amount = amt;
    temp->time = *localtime(&t);
    temp->next = NULL;

    __add_trans_in_usr(sender, temp);
    __add_trans_in_usr(reciver, temp);

    // return address of transaction so that is can be adden in block chain
    return temp;
}

void initilize_bal(UserList *user, double deposit)
{
    /**************************************
    *  need to work on current value of   *
    *  bitcoin based on which parameter   *
    *  it will need also it can be passed  *
    ***************************************/
    double value = current_val();

    user->balance = deposit / value;
}

double capital_value(UserList *user)
{
    double value = current_val();
    return value * user->balance;
}
