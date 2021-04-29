#ifndef __BITCOIN_H
#define __BITCOIN_H

#include <stdio.h>
#include <time.h>

typedef int ElemType;

//hash table for storing data of users
//linked lists for storing transactions
//linked list for blockchain

struct Array
{
    int Nonce;
    struct BlockChain *B;
};

struct Array BlockArray;

typedef struct UserList UserList;
typedef UserList *Users;

struct UserList
{
    int UID;
    double balance;
    Transact T; //we can also store the transaction history in an array
    //time_t join_time;
    Users next;
};

typedef struct Transaction Transaction;
typedef struct Transaction *Transact;

struct Transaction
{
    int S_UID;
    int R_UID;
    double tr_amount;
    Transact next;
    //time_t time;
};

typedef struct BlockChain BlockChain;
typedef BlockChain *Block;

Block head;
Block tail;

struct BlockChain
{
    ElemType hash_val;
    ElemType prev_block_hash;
    int block_num;
    int Nonce;
    Transact T;
    Block next;
    Block prev;
};

void initBlockArray();
void updateBlockArray(Block *Bl);

Block emptyBlock(Transact T);
Block initBlock(ElemType prev_block_hash, int block_num);
Transact initTransaction();
Users initUsers();

ElemType Hash();

int AddUser();                                            //return 1 if addition is successful
int Transaction(int S_uid, int R_uid, double amount);     //return -1 if transaction declined
Block createBlock(Block prev, Transact T, int block_num); //we will pass the header to the block, and that of the transaction list
int Attack(Block *Bl);
int Validate(Block B);

#endif
