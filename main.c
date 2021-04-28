#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./bitcoin.h"
#include "./user.h"

#define APP_NAME "temp name"
#define command_length 50
#define INIT_MAX_USERS 50

int main()
{

	srand((unsigned) time(NULL));		//seeding randomizer for other functions

//	inits
	Users* userlist = (Users*) malloc( INIT_MAX_USERS * sizeof(Users) );	//array of users
//

	printf("Welcome to %s\n\n", APP_NAME);
	printhelp();

	while(1)
	{
		printf("Please enter the command:");
		char command[command_length];
		scanf("%s", command);

		switch( command[0] )
		{
			case 'a':
				if( strcmp( command, "attack" ) )
				{
					printf("Let's see who's taking the Majority Control!\n");
					printf("ATTACK!!!\n");

					int x = Attack();
					if( x==-1 )
						printf("Attack failed:(\n");
					else
						printf("Successful att4ck. Compromised block number: %d\n", x);

					break;
				}
//				goto invalid_command;
				goto default;

			case 'r':
				if( strcmp( command, "register user" ) )
				{
					printf("Enter the initial amount to diposit: $");
					double x;
					scanf("%lf", &x);
					userlist = register_usr(userlist, x);
					break;
				}
//				goto invalid_command;
				goto default;

			case 't':
				if( strcmp( command, "transact" ) )
				{
					int s_uid, r_uid;
					double amount;
					printf("Starting transaction\n");
					printf("Enter sender's id: ");
					scanf("%d", &s_uid);
					printf("Enter reciever's id: ");
					scanf("%d", &r_uid);
					printf("Enter amount to transfer: ");
					scanf("%d", &amount);

					Transact* current_transaction = Transaction(s_uid, r_uid, amount);
					if( current_transaction==0 )
						printf("Transaction failed.\n");
					else
					{
						printf("Transaction successful.");
					}
					
					break;
				}
//				goto invalid_command;
				goto default;

/*
			case 'c':
				if( strcmp( command, "create block" ) )
				{
					printf("New Block: ");
					createBlock(prev, T, block_num);
					break;
				}
//				goto invalid_command;
				goto default;
*/

			case 'v':
				if( strcmp( command, "validity check" ) )
				{
					printf("--:Checking Validity:--");
					Validate(B);
					break;
				}
//				goto invalid_command;
				goto default;

			case 'h':
				if( strcmp( command, "help" ) )
				{
					printhelp();
					break;
				}
//				goto invalid_command;
				goto default;

			case 'e':
				if( strcmp( command, "exit" ) )
				{
					goto exit;
				}

			default:
//				invalid_command:
				print("Commnd not recognized. Refer to help page:");
				printhelp();

		}
	}

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
