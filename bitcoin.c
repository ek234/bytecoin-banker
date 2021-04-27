#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "bitcoin.h"

time_t time;
srand((unsigned)time(&time));

#define NONCE_SIZE 500
#define BLOCK_SIZE 50

void initBlockArray()
{
    for (int i = 0; i < 51; i++)
    {
        BlockArray[i].Nonce = -1;
        BlockArray[i].B = NULL
    }
}

void updateBlockArray(Block *Bl)
{
    Block B = *Bl;

    int num = B->block_num;

    BlockArray[num].Nonce = B->Nonce;
    BlockArray[num].B = B;
}

Block emptyBlock(Transact T)
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

Block initBlock(Block prev, int block_num)
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
    B->prev = prev;

    tail->next = B;
    tail = B;

    updateBlockArray(&B);

    return B;
}

Block createBlock(Block prev, Transact T, int block_num) //we will pass the header to the block, and that of the transaction list
{
    Block current = initBlock(prev, block_num);

    current->T = T;

    return current;
}

int Attack()
{
    int x = rand() % BLOCK_SIZE;

	if (BlockArray[x]!=NULL)
	{
		int r = rand() % (NONCE_SIZE - 1);
		r++;	//Now, r is a random int from 1 to NONCE_SIZE-1 inclusive
		//	This ensures that Nonce can not remain the same
		BlockArray[i].Nonce = ( BlockArray[i].Nonce + r ) % NONCE_SIZE;
		return x;					//num of block attacked
	}

    return -1;							//no block was attacked
}

//incomplete. will finish after hash function has been written                            
int Validate(Block B) //pass the tail pointer
{
    int flag = 1;

    while (B->prev->hash_val != 0)
    {
        if (B->prev_block_hash == B->prev->hash_val)
        {
            B = B->prev;
            continue;
        }
        else
        {
            flag = 0; //block has been attacked.
            //adjusting value of nonce of prev block
        }
    }

    return flag;
}
