#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "./bitcoin.h"
#include "./user.h"
#include "./trans.h"
#include "./update_val.h"
#include "./color.h"

#define APP_NAME "iiitcoin"
#define command_length 50
#define trans_per_block 50

void printhelp()
{
	// help page
	Bcyan();
	printf("\n\t\t\tWe are here to help you!\n");
	reset();
	cyan();
	printf("\nInstructions: -\nUse the following commands to move ahead:\n");
	reset();
	printf("1.\tPress 'attack' to see your situation with the equity (Attack).\n");
	printf("2.\tPress 'balance' to check the balance no. of bitcoins.\n");
	printf("3.\tPress 'check' to check the value of bitcoin with respect to $.\n");
	printf("4.\tPress 'help' to return to the set of instructions.\n");
	printf("5.\tPress 'past' to display upto the last 5 transaction of a user\n");
	printf("6.\tPress 'mine' to mine bitcoins.\n");
	printf("7.\tPress 'register' to register your details.\n");
	printf("8.\tPress 'transfer' to fill your transaction details.\n");
	printf("9.\tPress 'unregister' to remove your details from the list.\n");
	printf("10.\tPress 'validity' to check the validity of your Block Chain.\n");
	printf("11.\tPress 'exit' to exit from the page.\n");
	printf("Note: in %s v0.5+, users can select only the first alphabet of the command.\n", APP_NAME);
	printf("\n%s v0.6.01\n", APP_NAME);
	cyan();
	printf("\n\t\t\tHave a smooth Experience here. Stay Safe🌻\n");
	reset();
}

#endif
