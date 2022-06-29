#ifndef __UPDT_VAL_H__
#define __UPDT_VAL_H__
#define total_coins 100000000
#define init_val 100
typedef struct data *data_ptr;
typedef struct data
{
    int old_usr;
    int new_usr;
    int old_trans;
    int new_trans;
} data;
double upd_val(data_ptr detail, double val);
double after_attack(double val);

#endif
