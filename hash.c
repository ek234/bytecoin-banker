#include "bitcoin.h"
#include "trans.h"
#include "update_val.h"

struct Hashkey hashkey;

ElemType Hash(Block B)
{
    hashkey.hashval = B->Nonce;
    hashkey.hashval_2 = (B->T->next->S_UID + B->T->next->R_UID + B->T->next->tr_amount) % B->block_num; //error
    hashkey.hashval = hashkey.hashval << (hashkey.hashval_2 % 2);
    B->hash_val = hashkey.hashval + B->prev_block_hash;
    return B->hash_val;
}

