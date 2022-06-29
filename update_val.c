#include <stdio.h>
#include <stdlib.h>
#include "./update_val.h"

#define attack -2.00

double __abs(double x)
{
    if (x < 0)
        return x * -1.00;
    else
        return x;
}

double upd_val(data_ptr detail, double val)
{
    int usr_diff = detail->new_usr - detail->old_usr;
    int trans_diff = detail->new_trans - detail->old_trans;
    double usr_change = 0, trans_change = 0;

    double per_tc = ((double)trans_diff * 100.00) / (double)(detail->old_trans + 1.00);
    double per_uc = ((double)usr_diff * 100.00) / (double)(detail->old_usr + 1.00);

    /*///////////////////////////////////////////////////////////////////////////////////////
    *                                                                                       * 
    *   Value of bytecoin depends on two factors here                                        *
    *   1. If no of users increase ==> demand increase ==> increase value                    *   
    *   2. If more bigger transactions are there, it means people did'nt tend to keep       *   
    *      coin ==> value decreases                                                         *
    *   3. If no/less transactions ==> High demand people ==> val increase                  *
    *                                                                                       *
    */
    ///////////////////////////////////////////////////////////////////////////////////////

    if (__abs(usr_diff) >= 10 && __abs(per_uc) >= 10)
    {
        //increase or decrease is manages by the sign of change percentage
        if (__abs(per_uc) > 8000.00 / val)
            usr_change = (__abs(per_uc) / per_uc) * 20;
        else
            usr_change = (val * per_uc) / 400.00;
        detail->old_usr = detail->new_usr;
    }
    if (trans_diff >= 10 && per_tc >= 15)
    {
        // decrease val
        if (__abs(per_tc) > 5000.00 / val)
            trans_change = 10;
        else
            trans_change = (val * per_tc) / 500.00;
        detail->old_trans = detail->new_trans;
    }
    else if (trans_diff <= -20 && per_tc <= -20)
    {
        // increase val
        if (__abs(per_tc) > 5000.00 / val)
            trans_change = -10;
        else
            trans_change = (val * per_tc) / 500.00;
        detail->old_trans = detail->new_trans;
    }

    return val + trans_change + usr_change;
}

double after_attack(double val)
{
    // If successful attack then value drops

    double change = (val * attack) / 100.00;
    return val + change;
}
/* int main()
{
    printf("hello world\n");
} */
