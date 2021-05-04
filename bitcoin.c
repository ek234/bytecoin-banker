#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "bitcoin.h"

//delete_user
//loan
//withdrawal

time_t time;
srand((unsigned)time(&time));

#define NONCE_SIZE 500
#define BLOCK_SIZE 50

struct Array *PtrBlock = (struct Array *)malloc(BLOCK_SIZE * sizeof(BlockArray));

void initBlockArray() //array of pointers to access the blocks in O(1)time. Need to initialise in main()
{
    for (int i = 0; i <= 50; i++)
    {
        PtrBlock[i].Nonce = -1;
        PtrBlock[i].B = NULL
    }
}

void updateBlockArray(Block *Bl) //updating the block array whenever a new block is added to the chain.
{
    Block B = *Bl;

    int num = B->block_num;

    PtrBlock[num].Nonce = B->Nonce;
    PtrBlock[num].B = B;
}

Block emptyBlock(Transact T) //inistialise in main(). For the first block in the chain.
{
    Block B = (Block)malloc(sizeof(BlockChain);
    assert(B != NULL);

    int x = rand() % (NONCE_SIZE);

    B->block_num = 1;
    B->hash_val = Hash();
    B->prev_block_hash = 0;
    B->T = T;
    B->Nonce = x;
    B->next = NULL;
    B->prev = NULL;

    head = B;
    tail = head;

    updateBlockArray(&B);

    return B;
}

Block initBlock(int block_num) //will be called by initBlock during the update process of the blockchain.
{
    Block B = (Block)malloc(sizeof(BlockChain));
    assert(B != NULL);

    int x = rand() % NONCE_SIZE;

    B->block_num = block_num;
    B->hash_val = Hash();
    B->prev_block_hash = prev->hash_val;
    B->T = NULL;
    B->Nonce = x;
    B->next = NULL;
    B->prev = tail;

    tail->next = B;
    tail = B;

    updateBlockArray(&B);

    return B;
}

Block createBlock(Transact T, int block_num) //we will pass the header to the block, and that of the transaction list. Call in main().
{
    Block current = initBlock(block_num);

    current->T = T;

    return current;
}

int Attack()
{
    int x = rand() % BLOCK_SIZE;

	if ( PtrBlock[x].B != NULL )
	{
		int r = rand() % (NONCE_SIZE - 1);
		r++;	//Now, r is a random int from 1 to NONCE_SIZE-1 inclusive
		//	This ensures that Nonce can not remain the same
		PtrBlock[x].Nonce = ( PtrBlock[x].Nonce + r ) % NONCE_SIZE;
		PtrBlock[x].B->Nonce = PtrBlock[x].Nonce;
		return x;					//num of block attacked
	}

    return -1;							//no block was attacked
}

//incomplete. will finish after hash function has been written
bool Validate() //pass the tail pointer
{
    bool flag_invalid_chain = 0;

	Block it = tail;
    while (it->prev != NULL)
    {
        if (it->prev_block_hash != hash(it->prev))			//block has been attacked.
        {
			flag_invalid_chain = 1;
			//adjusting value of nonce of prev block
			for(it->prev->nonce = 1; it->prev->nonce < NONCE_MAX; it->prev->nonce += 1 )
			{
				if(it->prev_block_hash == hash(it->prev))
					goto nonce_fixed;
			}
        }

		nonce_fixed:;
		it = it->prev;
    }

    return flag_invalid_chain;		//returns 0 to show no errors in the block chain
}
