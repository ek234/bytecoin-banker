#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./bitcoin.h"
#include "./user.h"

#define APP_NAME "temp name"

int main()
{

	printf("Welcome to %s\n\n", APP_NAME);
	printhelp();

//___loop starts
	printf("Please enter the command");
	char command[50];
	scanf("%s", command);

	switch( command[0] )
	{
		case 'a':
			if( strcmp( command, "add user" ) )
			{
				printf("Your generated unique ID is: ");
				AddUser();
				break;
			}
			if( strcmp( command, "attack" ) )
			{
				printf("Let's see who's taking the Majority Control!\n");
				printf("ATTACK!!!\n");
				Attack(B1);
				break;
			}
//			goto invalid_command;
			goto default;

		case 'r':
			if( strcmp( command, "register user" ) )
			{
				printf("Enter the user details:- \n Your unique ID: \n Initial Balance: \n");
				register_usr(user_list[], name[], bal);
				break;
			}
//			goto invalid_command;
			goto default;

		case 't':
			if( strcmp( command, "transact" ) )
			{
				printf("The transaction details: "); //Sender UID, Receiver UID, Amount Transferred
				Transaction(S_uid, R_uid,  amount);
				break;
			}
//			goto invalid_command;
			goto default;

		case 'c':
			if( strcmp( command, "create block" ) )
			{
				printf("New Block: ");
				createBlock(prev, T, block_num);
				break;
			}
//			goto invalid_command;
			goto default;

		case 'v':
			if( strcmp( command, "validity check" ) )
			{
				printf("--:Checking Validity:--");
				Validate(B);
				break;
			}
//			goto invalid_command;
			goto default;

		case 'e':
			if( strcmp( command, "exit" ) )
			{
				goto exit;
			}

		default:
//			invalid_command:
			print("Commnd not recognized. Refer to help page:");
			printhelp();

	}
//___loop ends



exit:
	printf("Thank you for using %s\n\n", APP_NAME);


/*
    	initBlockArray();
    	updateBlockArray(Block* B1);
    	emptyBlock(Transact T);
    n	initBlock(ElemType prev_block_hash, int block_num);
    ?	initTransaction();
    ?	initUsers();
    ?	Hash();

    d	AddUser();
    d	Transaction(int S_uid, int R_uid, double amount);
    d	createBlock(Block prev, Transact T, int block_num);
    d	Attack(Block* B1);
    d	Validate(Block B);

    d	register_usr(ptr_user user_list[], char name[], unsigned long int bal);
    	__find_id(char name[], char id[]);
    	__check(ptr_usr user_list[], int hash_key, char id[]);
*/

    return 0;
}
