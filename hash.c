#include "bitcoin.h"
#include "trans.h"
#include "update_val.h"


ElemType Hash(Block B,Transact T){
    int hashval,hashval_2;
    hashval = ((B->Nonce)%B->block_num);
    hashval_2 = T->S_UID + T->R_UID + T->tr_amount;
    hashval = hashval << (hashval_2 % 2);
    B->hash_val = hashval+ B->prev_block_hash;
    return B->hash_val;
}

