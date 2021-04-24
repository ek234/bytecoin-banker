#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitcoin.h"
#include "user.h"

int main(){

    printf("Enter the user details:- \n Your unique ID: \n Initial Balance: \n");
    register_usr(user_list[], name[], bal);

    printf("Your generated unique ID is: ");
    AddUser();

    printf("The transaction details: "); //Sender UID, Receiver UID, Amount Transferred
    Transaction(S_uid, R_uid,  amount);

    printf("New Block: ");
    createBlock(prev, T, block_num);

    printf("Let's see who's taking the Majority Control!\n");
    printf("ATTACK!!!\n");
    Attack(B1);

    printf("--:Checking Validity:--");
    Validate(B);

    //initBlockArray();
    //updateBlockArray(Block* B1);
    //emptyBlock(Transact T);
    //initBlock(ElemType prev_block_hash, int block_num);
    //initTransaction();
    //initUsers();
    //Hash();

    //AddUser();
    //Transaction(int S_uid, int R_uid, double amount);
    //createBlock(Block prev, Transact T, int block_num);
    //Attack(Block* B1);
    //Validate(Block B);

    //register_usr(ptr_user user_list[], char name[], unsigned long int bal);
    //__find_id(char name[], char id[]);
    //__check(ptr_usr user_list[], int hash_key, char id[]);

    return 0;
}