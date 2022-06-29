#include "bytecoin.h"
#include "trans.h"
#include "update_val.h"
#include <stdlib.h>
Hashkey hashkey;
//hash function
//will be calculated after completing 50 transactions
ElemType Hash(Block B)
{
    hashkey.hashval = B->Nonce;
    //taking the block nonce value
    Transact temp = (Transact)malloc(sizeof(Transaction));//dynamic allocation of memory to a temporary variable
    temp = B->T->next;
    while(temp != NULL)
    {
        hashkey.hashval_2 += (int)(temp->S_UID + temp->R_UID + temp->tr_amount) % B->block_num;
        temp = temp->next;
    } 
    //Adding the block transaction Sender and recirver ids and the transaction amount
    //and considering the remainder when divided by the block number.
    if (hashkey.hashval_2 % 4  == 3 || hashkey.hashval_2 % 4  == 1)
    {
        hashkey.hashval = hashkey.hashval << (hashkey.hashval_2 % 4);
    }
    else
    {
        hashkey.hashval = hashkey.hashval >> (hashkey.hashval_2 % 4);
    }
    //taking the 2 values we got above and performing bit shifting on them
    
    B->hash_val = hashkey.hashval * (B->prev_block_hash + 1) + (B->block_num) * (B->block_num);
    //taking the above value and multiplying it to the prev-block hash . 
    //added 1 as the prev-block hash for the first block is 0 which would have 
    //resulted in making hasval*prev_block_hash = 0
    //then added square of blocknumber to it
    
    free(temp);//freeing the dynamic errory
    return B->hash_val;
    //returning the obtained hash value
}
