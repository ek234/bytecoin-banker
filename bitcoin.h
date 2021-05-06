#ifndef __BITCOIN_H
#define __BITCOIN_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
typedef struct tm _time;

typedef int ElemType;
typedef struct Transaction Transaction;
typedef struct Transaction *Transact;
typedef struct UserList UserList;
typedef UserList *Usernext;
typedef struct BlockChain BlockChain;
typedef BlockChain *Block;
struct Array BlockArray;

struct Array
{
    int Nonce;
    Block B;
};

struct UserList
{
    int UID;
    double balance;
    Transact T; //we can also store the transaction history in an array
    _time join_time;
    Usernext next;
};

struct Transaction
{
    int S_UID;
    int R_UID;
    double tr_amount;
    Transact next;
    _time time;
};


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

struct Hashkey{
    int hashval;
    int hashval_2;
};

void initBlockArray();
void updateBlockArray(Block *Bl);

Block emptyBlock(Transact T);
Block initBlock(int block_num, Transact T);

ElemType Hash(Block B,Transact T);

Block createBlock(Transact T, int block_num); //we will pass the header to the block, and that of the transaction list
int Attack();
bool Validate();

#endif
