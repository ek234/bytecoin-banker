#ifndef __BITCOIN_H
#define __BITCOIN_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

//typedefs
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
    int UID;//the randomly assigned user id
    double balance;
    Transact T; //we can also store the transaction history in an array
    _time join_time;//the time when the user joined
    
};

struct Transaction
{
    int S_UID;//the sender's user id
    int R_UID;//the reciever's user id
    double tr_amount;//the amount of transaction
    Transact next;
    _time time;//the time at which the transaction took place
};

Block tail;
Block head;
//the blockchain is a doubly linked list

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

//initializing the blockarray
void initBlockArray();
//updating the blockarray whenever a new block is added to the chain
void updateBlockArray(Block *Bl);

//creates the first block in the blockchain
Block emptyBlock(Transact T);


Block initBlock(int block_num, Transact T);

//The Hash Function designed using the block variables and returns the hash_value
ElemType Hash(Block B);

//we will pass the header to the block, and that of the transaction list
Block createBlock(Transact T, int block_num); 

//For attacking the blockchain
int Attack();


bool Validate();

#endif
