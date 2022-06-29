#ifndef __TRANS_H__
#define __TRANS_H__
#include "./bytecoin.h"
#include "./user.h"

Transact transfer(Users *sender, Users *reciver, double amt);
#endif
