#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./bitcoin.h"
#include "./user.h"

#define APP_NAME "temp name"
#define command_length 50
#define INIT_MAX_USERS 50

received
void printhelp(){
	printf("\n\t\t\t\tNAMASKAAR🙏\n\t\t\tWe are here to help you!\n\n\n");
	printf("Instructions: -\nUse the following commands to move ahead.\n");
	printf("1. Press 'register user' to register your details.\n");
	printf("2. Press 'attack' to see your situation with the equity (Attack).\n");
	printf("3. Press 'transfer' to fill your transaction details.\n");
	printf("4. Press 'validity' to check the validity of your Block Chain.\n");
	printf("5. Press 'help' to return to the set of instructions.\n");
	printf("6. Press 'exit' to exit from the page.\n");
	printf("\n\t\t\t\tHave a smooth Experience here. Stay Safe🌻\n");
}
	   
	       
int main()
{

	srand((unsigned) time(NULL));		//seeding randomizer for other functions

//	inits
	Users* userlist = (User*) malloc( func*sizeof(User) );	// array of ptrs of userslist struct
	for( int i=0; i<func; i++ )
	{
		userlist[i] = NULL;
	}
	int block_num = 0;
	initBlockArray();
	int Ntransactions = 0;
	
	double bit_value = 100;
	data net_data;
    net_data.old_usr = 0;
    net_data.new_usr = 0;
    net_data.old_trans = 0;
    net_data.new_trans = 0;
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
					if( x == -1 )
						printf("Attack failed :(\n");
					else
					{
						printf("Successful att4ck. Compromised block number: %d\n", x);
						bit_value = after_attack(bit_value);
					}

					break;
				}
				goto invalid_command;

			case 'b':
				if( strcmp( command, "balance" ) )
				{
					printf("Enter the user id: ");
					int uid;
					scanf("%d", &uid);
					User temp = find_user(userlist, uid);
					double bal = temp->balance;
					if( temp==NULL )
					{
						printf("Error: user id doesn't exist\n");
					}
					else
					{
						printf("Current balance: %lfBitcoin\n", bal);
					}
					break;
				}
				goto invalid_command;

			case 'c':
				if( strcmp( command, "check" ) )
				{
					bit_value = upd_val( &net_data, bit_value );
					printf("Current Value of bitcoin: %lf\n", bit_value);
					break;
				}
				goto invalid_command;

			case 'u':
				if( strcmp( command, "unregister" ) )
				{
					printf("Enter the user id: ");
					int uid;
					scanf("%d", &uid);
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
						printf("Returning balance: %lf\n", bal);
					}
					break;
				}
				goto invalid_command;

			case 'r':
				if( strcmp( command, "register" ) )
				{
					printf("Enter the initial amount to diposit: $\n");
					double x;
					scanf("%lf", &x);
					Users temp = register_usr(&userlist, x);
//					if( temp!=userlist )
//					{
//						free(userlist);
//						userlist = temp;
//					}
					printf("User added successfully\n");
					printf("User id: %d\n", temp.UID);
					net_data.new_usr++;
					break;
				}
				goto invalid_command;

			case 't':
				if( strcmp( command, "transfer" ) )
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
					
					Transact* current_transaction = transfer(s_uid, r_uid, amount);

					if( current_transaction == 0 )
						printf("Transaction failed.\n");
					else
					{
						if( blockchain == NULL )
						{
							emptyblock(current_transaction);
							Ntransactions = 1;
						}
						else if(Ntransactions >= 50)
						{
							createBlock(current_transaction, block_num);
							Ntransactions = 1;
						}
						else
						{
							current_transaction -> next = tail->T;
							tail->T = current_transaction;
							Ntransactions++;
						}
		/*temp for testing*/ assert(Ntransactions <= 50)

						net_data.new_trans++;
						printf("Transaction was successful.\n");
					}
					
					break;
				}
				goto invalid_command;

			case 'v':
				if( strcmp( command, "validity" ) )
				{
					bool = v;
					v = Validate();
					printf("--:Checking Validity:--\n");
					if(v == 0){
						printf("\nNO ERROR\n\t\t\tCheers!!\n");
					}
					else if(v = 1){
						printf("\nBlock Chain needs Fixing\n");
						printf("Resolving errors");
						for( int i=0; i<5; i++ )
						{
							delay(500);
							printf(".");
						}
						printf("\nAll the errors have been resolved.\n");
					}
					break;
				}
				goto invalid_command;

			case 'h':
				if( strcmp( command, "help" ) )
				{
					printhelp();
					break;
				}
				goto invalid_command;

			case 'e':
				if( strcmp( command, "exit" ) )
				{
					goto exit;
				}
				goto invalid_command;

			default:
				invalid_command:
				print("Commnd not recognized. Refer to help page:");
				printhelp();

		}
	}

exit:
	printf("Thank you for using %s\n\n", APP_NAME);

    return 0;
}
