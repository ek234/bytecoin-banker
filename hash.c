#include "bitcoin.h"
#include "trans.h"
#include "update_val.h"

struct Hashkey hashkey;
ElemType Hash(Block B,Transact T){
    hashkey.hashval = B->Nonce;
    hashkey.hashval_2 = (T->S_UID + T->R_UID + T->tr_amount)%B->block_num;
    hashkey.hashval = hashkey.hashval << (hashkey.hashval_2 % 2);
    B->hash_val = hashkey.hashval+ B->prev_block_hash;
    return B->hash_val;
}

