#include <stdio.h>
#include "./update_val.h"
#define attack -2.00

double __abs(double x)
{
    if (x < 0)
        return x * -1.00;
    else
        return x;
}

double upd_val(data_ptr det, double val)
{
    int usr_diff = det->new_usr - det->old_usr;
    int trans_diff = det->new_trans - det->old_trans;
    double usr_change, trans_change;

    double per_tc = ((double)trans_diff * 100.00) / (double)det->old_trans;
    double per_uc = ((double)usr_diff * 100.00) / (double)det->old_usr;

    /*///////////////////////////////////////////////////////////////////////////////////////
    *                                                                                       * 
    *   Value of bitcoin depends on two factors here                                        *
    *   1. If no of users increase ==> deman increase ==> increase value                    *   
    *   2. If more bigger transactions are there, it means people did'nt tend to keep       *   
    *      coin ==> value decreases                                                         *
    *   3. If no/less transactions ==> High demand people ==> val increase                  *
    *                                                                                       *
    *////////////////////////////////////////////////////////////////////////////////////////

    if (__abs(usr_diff) >= 10 && __abs(per_uc) >= 10)
    {
        //increase or decrease is manages by the sign of change percentage
        usr_change = (val * per_uc) / 400.00;
    }
    if (trans_diff >= 10 && per_tc >= 15)
    {
        // decrease val
        trans_change = (val * per_tc) / 500.00;
    }
    else if (trans_diff <= -20 && per_tc <= -20)
    {
        // increase val
        trans_change = (val * per_tc) / 500.00;
    }

    //updates number of user adn transactions
    det->new_usr = det->old_usr;
    det->new_trans = det->old_trans;
    return val + trans_change + usr_change;
}

double after_attack(double val)
{
    // If successful attack then value drops

    double change = (val * attack) / 100.00;
    return val + change;
}