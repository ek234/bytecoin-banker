#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "./bytecoin.h"

#define NONCE_SIZE 500
#define BLOCK_SIZE 50


//Array containing nonce and pointer to block corresponding to the index.
//Blocks accesible in O(1) time
Array PtrBlock[51];

//intialising PtrBlock[]
//called in main
void initBlockArray()
{
    for (int i = 0; i < 51; i++)
    {
        PtrBlock[i].Nonce = -1;
        PtrBlock[i].B = NULL; //pointer initialised to NULL
    }
}

//updating PtrBlock[] whenever a new block is added to the chain
//called by initBlock()
void updateBlockArray(Block *Bl) //pointer to pointer to blockchain
{
    Block B = *Bl; //now we have access to the block via the pointer

    int num = B->block_num;

    PtrBlock[num].Nonce = B->Nonce;
    PtrBlock[num].B = B;
}

//called in main as soon as we make the first transaction
//creates the first block in the blockchain
//accepts the header to the transaction linked list
//returb pointer to the block
Block emptyBlock(Transact T, Block tail, Block head)
{
    Block B = (Block)malloc(sizeof(BlockChain)); //allocating memory for block
    assert(B != NULL);

    int x = rand() % (NONCE_SIZE) + 1; //randomly calculating a nonce

    B->block_num = 1;      //first block in the blockchain
    B->prev_block_hash = 0;
    B->T = T; //header of transaction linked list
    B->Nonce = x;
    B->next = NULL;
    B->prev = NULL;
    B->hash_val = Hash(B); //calculating hash val od the first block

    head = B; //updating gloabal variable head
    tail = head;    //updating global variable tail

    updateBlockArray(&B); //updating PtrBlock[]

    return B;
}

//called by createBlock() to update the blockchain
//takes block num ans header to transaction linked list as parameters
//returns the pointer to the current block
Block initBlock(int block_num, Transact T, Block tail) //will be called by initBlock during the update process of the blockchain->
{
    Block B = (Block)malloc(sizeof(BlockChain)); //allocating memory for the block
    assert(B != NULL);

    int x = rand() % NONCE_SIZE + 1; //randomly generating a nonce

    //writing all necessary details in the block
    B->block_num = block_num;
    B->prev_block_hash = tail->hash_val;
    B->T = T;
    B->Nonce = x;
    B->next = NULL;
    B->prev = tail;
    B->hash_val = Hash(B); //calculating hash value using hash function

    tail->next = B; //insert at rear of the blockchain
    tail = B;

    updateBlockArray(&B);

    return B;
}

//called in main when we reach greater than 50 transactions
//header to the transaction linked list and the block number is passed
//calls initBlock() to update the blockchain
//returns pointer to current block (tail of the blockchain)
Block createBlock(Transact T, int block_num, Block tail)
{
    Block current = initBlock(block_num, T, tail); //calling initBlock()

 //   current->T = T; //adding header of transaction linked list to the block

    return current; //returning the current block of the blockchain
}

//For attacking the blockchain
//randomly generates a number; if a block with that block num exists, we modify it's nonce
//this means that the hash val becoomes incorrect( value of nonce changes) and hence the blockchain becomes invalid
//we can access the block in O(1) time because of PtrBlock()
int Attack( Block tail, Block head )
{
    if(head == NULL)
        return -1;
    int x = rand() % BLOCK_SIZE; //randomly checing if a block exists in the blockchain
	// if the chosen block exists and is not the current block
    if (PtrBlock[x].B!=NULL && PtrBlock[x].B!=tail)
    {
		int r;
		do{
			r = rand() % (NONCE_SIZE - 1);
			r++;	//Now, r is a random int from 1 to NONCE_SIZE-1 inclusive
		} while( PtrBlock[x].Nonce + r == NONCE_SIZE );
		// the do-while loop ensures that Nonce is never 0

		//  This ensures that Nonce can not remain the same
		PtrBlock[x].Nonce = (PtrBlock[x].Nonce + r) % NONCE_SIZE;

        //	This ensures that Nonce can not remain the same
        PtrBlock[x].Nonce = (PtrBlock[x].Nonce + r) % NONCE_SIZE;
        PtrBlock[x].B->Nonce = PtrBlock[x].Nonce;

        return x; //num of block attacked
    }

    return -1; //no block was attacked
}

bool Validate( Block tail )
{
    bool flag_invalid_chain = 0;
    
    if (tail == NULL)
        return 0;   //chain doesen't exist so it is valid

    Block current = tail;
    while (current->prev != NULL)
    {
        if (current->prev_block_hash != Hash(current->prev)) //block has been attacked->
        {
            flag_invalid_chain = 1; //blockchain is invalid

            //adjusting value of nonce of prev block
            for (current->prev->Nonce = 1; current->prev->Nonce < NONCE_SIZE; current->prev->Nonce += 1) //looping for all possible values of nonce
            {
                if (current->prev_block_hash == Hash(current->prev)) //if the hash value matches for a particular value of nonce
                {
                    current->prev->hash_val = Hash(current->prev);                   //updating hash val of prev block
                    PtrBlock[current->prev->block_num].Nonce = current->prev->Nonce; //updating val of nonce in PtrBlock[]
                    break;
                }
            }
        }

        current = current->prev;
    }

    return flag_invalid_chain; //returns 0 to show no errors in the block chain
}
