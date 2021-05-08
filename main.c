#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "./bitcoin.h"
#include "./user.h"
#include "./trans.h"
#include "./update_val.h"

#define APP_NAME "temp name"
#define command_length 50

void printhelp()
{
	// help page
	printf("\n\t\t\tWe are here to help you!\n\n");
	printf("Instructions: -\nUse the following commands to move ahead:\n");
	printf("1.\tPress 'register' to register your details.\n");
	printf("2.\tPress 'balance' to check the balance no. of bitcoins.\n");
	printf("3.\tPress 'check' to check the value of bitcoin with respect to $.\n");
	printf("4.\tPress 'mine' to mine bitcoins.\n");
	printf("5.\tPress 'transfer' to fill your transaction details.\n");
	printf("6.\tPress 'unregister' to remove your details from the list.\n");
	printf("7.\tPress 'attack' to see your situation with the equity (Attack).\n");
	printf("8.\tPress 'validity' to check the validity of your Block Chain.\n");
	printf("9.\tPress 'help' to return to the set of instructions.\n");
	printf("10.\tPress 'exit' to exit from the page.\n");
	printf("Note: in %s v0.5+, users can select only the first alphabet of the command.\n", APP_NAME);
	printf("\n%s v0.6.01\n", APP_NAME);
	printf("\n\t\t\tHave a smooth Experience here. Stay Safe🌻\n");
}
	   
	       
int main()
{

	//seeding randomizer for other functions
	srand((unsigned) time(NULL));

//	inits

	// max number of users that can be managed at the start of the program
	usr_no = 100000;
	// array of ptrs of userslist struct
	Users* userlist = (Users*) malloc( usr_no*sizeof(Users) );
	for( int i=0; i<(signed)usr_no; i++ )
	{
		userlist[i] = NULL;
	}

	// head and tail of the block chain
	head = tail = NULL;
	// number of blocks currently in the chain
	int block_num = 0;
	initBlockArray();
	// number of transactions in the current block
	int Ntransactions = 0;

	// the value of bitcoin wrt $
	double bit_value = 100;
	// struct containing overhead data about number of users and number of transactions
	data net_data;
    net_data.old_usr = 0;
    net_data.new_usr = 0;
    net_data.old_trans = 0;
    net_data.new_trans = 0;
//

	printf("\n\t\t\t\tNAMASKAAR🙏\n\n");
	printf("\n\t\t\tWelcome to %s\n\n", APP_NAME);
	printhelp();

	while(1)
	{
		printf("Please enter the command: ");
		char command[command_length];
		scanf("%s", command);

		//running switch-case on the first char of the command to reduce the number of comparisons
		switch( command[0] )
		{
			case 'a':
				// if command[1] is a null char, then the command was "a". this is accepted
				if( command[1]=='\0' || !strcmp( command, "attack" ) )
				{
					printf("Let's see who's taking the Majority Control!\n");
					printf("ATTACK!!!\n");

					int x = Attack();
					if( x == -1 )
						printf("Attack failed :(\n");
					else
					{
						printf("Successful att4ck. Compromised block number: %d\n", x);
						bit_value = after_attack(bit_value);
					}

					break;
				}
				// if command didn't enter the if block and therefore didn't break out,
				// then command was invalid.
				goto invalid_command;

			case 't':
				if( command[1]=='\0' || !strcmp( command, "transfer" ) )
				{
					int s_uid, r_uid;
					Users a, b;
					double amount;
					printf("Starting transaction\n");

					// taking senders UID until it's valid
					do{
						printf("Enter sender's id: ");
						scanf("%d", &s_uid);
						// finding sender
						a = find_user(userlist, s_uid);
					} while( a==NULL && printf("Invalid UID\n") );
					// taking reciever's UID until it's valid
					do{
						printf("Enter reciever's id: ");
						scanf("%d", &r_uid);
						// finding reciever
						b = find_user(userlist, r_uid);
					} while( b==NULL && printf("Invalid UID\n") );

					printf("Enter amount to transfer: ");
					scanf("%lf", &amount);
					if(amount < 0)
					{ 
						printf("Transaction failed.Negative values are not.\n");
						break;
					}
					
					Transact current_transaction = transfer( &a, &b, amount);

					if( current_transaction == NULL )
						printf("Transaction failed. Check if sender has enough balance.\n");
					else
					{
						if( tail == NULL )
						{//	if blockchain does not exist then start a new chain.
							emptyBlock(current_transaction);
							Ntransactions = 1;
						}
						else if(Ntransactions >= 50)
						{//	if the current block is full then make a new one.
							createBlock(current_transaction, block_num);
							Ntransactions = 1;
						}
						else
						{//	otherwise, add transaction to the block.
							current_transaction->next = tail->T;
							tail->T = current_transaction;
							Ntransactions++;
						}
/*temp for testing*/	assert(Ntransactions <= 50);

						net_data.new_trans++;
						printf("Transaction was successful.\n");
					}
					break;
				}
				goto invalid_command;

			case 'b':
				if( command[1]=='\0' || !strcmp( command, "balance" ) )
				{
					printf("Enter the user id: ");
					int uid;	scanf("%d", &uid);
					Users temp = find_user(userlist, uid);
					
					if( temp==NULL )
					{
						printf("Error: user id doesn't exist\n");
					}
					else
					{	
						double bal = temp->balance;
						printf("Current balance: %g Bitcoin\n", bal);
					}
					break;
				}
				goto invalid_command;

			case 'c':
				if( command[1]=='\0' || !strcmp( command, "check" ) )
				{
					bit_value = upd_val( &net_data, bit_value );
					printf("Current Value of bitcoin: %lf\n", bit_value);
					break;
				}
				goto invalid_command;

			case 'u':
				if( command[1]=='\0' || !strcmp( command, "unregister" ) )
				{
					printf("Enter the user id: ");
					int uid;	scanf("%d", &uid);

					bit_value = upd_val( &net_data, bit_value );
					double bal = delete_user(userlist, uid, bit_value);
					if( bal==-1 )
					{
						printf("Error: user id doesn't exist\n");
					}
					else
					{
						net_data.new_usr--;
						printf("Account successfully unregistered.\n");
						printf("Returning balance: $%lf\n", bal);
					}
					break;
				}
				goto invalid_command;

			case 'r':
				if( command[1]=='\0' || !strcmp( command, "register" ) )
				{
					// if the number of users are large enough then double the array
					if( 10*net_data.new_trans > 7*usr_no )
						double_user( userlist );

					printf("Enter the initial amount to deposit: $");
					double x;	scanf("%lf", &x);
					if(x < 0)
					{
						printf("Error : Negative values are not.\n");
						break;
					}
					Users temp = register_usr(userlist, x, bit_value);

					printf("User added successfully\n");
					printf("User id: %.7d\n", temp->UID);
					printf("Intial balance: %lf\n", temp->balance);
					printf("Joining time: %.2d:%.2d\n", temp->join_time.tm_hour,temp->join_time.tm_min);
					net_data.new_usr++;
					break;
				}
				goto invalid_command;

			case 'v':
				if( command[1]=='\0' || !strcmp( command, "validity" ) )
				{
					bool v;
					v = Validate();
					printf("--:Checking Validity:--\n");
					if(v == 0){
						printf("\nNO ERROR\n\t\t\tCheers!!\n");
					}
					else if(v == 1){
						printf("\nBlock Chain needs Fixing\n");
						printf("Resolving errors");
						for( int i=0; i<5; i++ )
						{
							//delay(500);
							printf(".");
						}
						printf("\nAll the errors have been resolved.\n");
					}
					break;
				}
				goto invalid_command;

			case 'h':
				if( command[1]=='\0' || !strcmp( command, "help" ) )
				{
					printhelp();
					break;
				}
				goto invalid_command;

			case 'e':
				if( command[1]=='\0' || !strcmp( command, "exit" ) )
				{
					goto exit;
				}
				goto invalid_command;

			default:
				invalid_command:
				printf("Commnd not recognized. Refer to help page:");
				printhelp();

		}
	}

	// freeing users
	for( int i=0; i<(signed)usr_no; i++ )
		if( userlist[i] != NULL )
			free( userlist[i] );

exit:
	printf("Thank you for using %s\n\n", APP_NAME);

    return 0;
}
