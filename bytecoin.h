#ifndef __BYTECOIN_H
#define __BYTECOIN_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

//typedefs
typedef struct tm _time;
typedef int ElemType;
typedef struct Transaction *Transact;
typedef struct UserList *Usernext;
typedef struct BlockChain *Block;

typedef struct Array
{
    int Nonce;
    Block B;
} Array;

typedef struct UserList
{
    int UID;//the randomly assigned user id
    double balance;
    Transact T; //we can also store the transaction history in an array
    _time join_time;//the time when the user joined
    
} UserList;

typedef struct Transaction
{
    int S_UID;//the sender's user id
    int R_UID;//the reciever's user id
    double tr_amount;//the amount of transaction
    Transact next;
    _time time;//the time at which the transaction took place
} Transaction;

extern Block tail;
extern Block head;
//the blockchain is a doubly linked list

typedef struct BlockChain
{
    ElemType hash_val;
    ElemType prev_block_hash;
    int block_num;
    int Nonce;
    Transact T;
    Block next;
    Block prev;
} BlockChain;

typedef struct Hashkey{
    int hashval;
    int hashval_2;
} Hashkey;

//initializing the blockarray
void initBlockArray();

//updating the blockarray whenever a new block is added to the chain
void updateBlockArray(Block *Bl);

//creates the first block in the blockchain
Block emptyBlock(Transact T, Block tail, Block head);

//updates the blockchain, takes block num ans header to transaction linked list as parameters and returns the pointer to the current block.
Block initBlock(int block_num, Transact T, Block tail);

//The Hash Function designed using the block variables and returns the hash_value
ElemType Hash(Block B);

//we will pass the header to the block, and that of the transaction list
Block createBlock(Transact T, int block_num, Block tail); 

//For attacking the blockchain
int Attack(Block tail, Block head);

//Check if Block-chain is valid.
bool Validate(Block tail);

#endif
