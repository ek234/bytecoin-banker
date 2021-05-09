#include "bitcoin.h"
#include "trans.h"
#include "update_val.h"

struct Hashkey hashkey;
//hash function
ElemType Hash(Block B)
{
    hashkey.hashval = B->Nonce;
    //taking the block nonce value
    hashkey.hashval_2 = (int)(B->T->S_UID + B->T->R_UID + B->T->tr_amount) % B->block_num;
    //Adding the block transaction Sender and recirver ids and the transaction amount
    //and considering the remainder when divided by the block number.
    if (hashkey.hashval_2 % 4  == 3 || hashkey.hashval_2 % 4  == 1)
    hashkey.hashval = hashkey.hashval << (hashkey.hashval_2 % 4);
    else
    hashkey.hashval = hashkey.hashval >> (hashkey.hashval_2 % 4);
    //taking the 2 values we got above and performing bit shifting on them
    B->hash_val = hashkey.hashval * (B->prev_block_hash + 1) + (B->block_num) * (B->block_num);
    //taking the above value and multiplying it to the prev-block hash . 
    //added 1 as the prev-block hash for the first block is 0 which would have 
    //resulted in making hasval*prev_block_hash = 0
    //then added square of blocknumber to it
    return B->hash_val;
    //returning the obtained hash value
}

