#ifndef __TRANS_H__
#define __TRANS_H__
#include "./bitcoin.h"
#include "./user.h"

Transact transfer(Users *sender, Users *reciver, double amt);
#endif
