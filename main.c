#include "./main.h"

void printhelp()
{
	// help page
	Bcyan();
	printf("\n\t\tWe are here to help you!\n");
	reset();
	cyan();
	printf("\nInstructions: -\nUse the following commands to move ahead:\n");
	reset();
	printf("1.\tPress 'attack' to see your situation with the equity (Attack).\n");
	printf("2.\tPress 'balance' to check the balance no. of bytecoins.\n");
	printf("3.\tPress 'check' to check the value of 1 bytecoin with respect to $.\n");
	printf("4.\tPress 'help' to return to the set of instructions.\n");
	printf("5.\tPress 'past' to display upto the last 5 transaction of a user\n");
	printf("6.\tPress 'mine' to mine bytecoins.\n");
	printf("7.\tPress 'register' to register your details.\n");
	printf("8.\tPress 'transfer' to fill your transaction details.\n");
	printf("9.\tPress 'unregister' to remove your details from the list.\n");
	printf("10.\tPress 'validity' to check the validity of your Block Chain.\n");
	printf("11.\tPress 'exit' to exit from the page.\n");
	printf("Note: in %s v0.5+, users can select only the first alphabet of the command.\n", APP_NAME);
	printf("\n%s v0.7.0\n", APP_NAME);
	cyan();
	printf("\n\t  Have a smooth Experience here. Stay Safe🌻\n");
	reset();
}

int main()
{

	//seeding randomizer for other functions
	srand((unsigned) time(NULL));

//	inits

	// max number of users that can be managed at the start of the program
	unsigned int usr_no = 100000;
	// array of ptrs of userslist struct
	Users* userlist = (Users*) malloc( usr_no*sizeof(Users) );
	for( unsigned int i=0; i<usr_no; i++ )
	{
		userlist[i] = NULL;
	}

	// head and tail of the block chain
	Block head = NULL;
	Block tail = NULL;
	// number of blocks currently in the chain
	int block_num = 0;
	initBlockArray();
	// number of transactions in the current block
	int Ntransactions = 0;

	// the value of bytecoin wrt $
	double byte_value = 100;
	// struct containing overhead data about number of users and number of transactions
	data net_data;
	net_data.old_usr = 0;
	net_data.new_usr = 0;
	net_data.old_trans = 0;
	net_data.new_trans = 0;
	Transact head_trans = (Transact)malloc(sizeof(Transaction));
	head_trans->next = NULL;

//
	cyan();
	printf("\n\t\t     🙏NAMASKAAR🙏\n");
	printf("\n\t\t Welcome to %s\n", APP_NAME);
	reset();
	printhelp();

	while(1)
	{
		blue();
		printf("\nPlease enter the command: ");
		char command[command_length];
		scanf("%s", command);
		while(getchar() != '\n');
		reset();

		//running switch-case on the first char of the command to reduce the number of comparisons
		switch( command[0] )
		{
			case 'a':
				// if command[1] is a null char, then the command was "a". this is accepted
				if( command[1] == '\0' || !strcmp( command, "attack" ) )
				{
					printf("Let's see who's taking the Majority Control!\n");
					red();
					printf("\t\t\tATTACK!!!\n");
					reset();

					int x = Attack(tail, head);
					if( x == -1 ){
						red();
						printf("Attack failed :(\n");
						reset();
					}
					else{
						green();
						printf("Successful att4ck. Compromised block number: %d\n", x);
						reset();
						byte_value = after_attack(byte_value);
					}

					break;
				}
				// if command didn't enter the if block and therefore didn't break out,
				// then command was invalid.
				goto invalid_command;

			case 't':
				if( command[1] == '\0' || !strcmp( command, "transfer" ) )
				{
					int s_uid, r_uid;
					Users a, b;
					double amount;
					printf("Starting transaction\n");

					// taking senders UID until it's valid
					do{
						printf("Enter sender's ID: ");
						scanf("%d", &s_uid);
						while(getchar() != '\n');
						// finding sender
						a = find_user(userlist, s_uid, usr_no);
					} while( a == NULL && printf("Invalid UID\n") );
					// taking reciever's UID until it's valid
					do{
						printf("Enter receiver's ID: ");
						scanf("%d", &r_uid);
						while(getchar() != '\n');
						// finding reciever
						b = find_user(userlist, r_uid, usr_no);
					} while( (b == NULL || r_uid == s_uid) && printf("Invalid UID\n") );
					printf("Enter coin to transfer: ");
					
					if(!scanf("%lf", &amount) || amount < 0 )
					{ 
						red();
						printf("Transaction failed. Negative values are not allowed.\n");
						reset();
						break;
					}
					while(getchar() != '\n');
					
					Transact current_transaction = transfer( &a, &b, amount);
					if(amount > 50)
						net_data.new_trans++;
					amount =0;
					s_uid =0;
					r_uid = 0;
					if( current_transaction == NULL ){
						red();
						printf("Oops! Transaction failed.\n");
						reset();
						printf("Check if sender has enough balance.\n");
					}
					
					else
					{
						if( Ntransactions < trans_per_block )
						{ //Add transactions in a link list until 50 transactions aren't completed.
							current_transaction->next = head_trans->next;
							head_trans->next = current_transaction;
							Ntransactions += 1;
						}
						else 
						{//	if the 50 transactions are comopleted tehn make a new block.
							if(tail == NULL )
							{
								emptyBlock(head_trans, tail, head);
								block_num = 1;
							}
							else
								createBlock(head_trans, block_num++, tail);
							head_trans->next = NULL;
							Ntransactions = 1;
						}
						
/*temp for testing*/	assert(Ntransactions <= trans_per_block);

						
						green();
						printf("Transaction was successful.\n");
						byte_value = upd_val(&net_data,byte_value);
						reset();
					}
					break;
				}
				goto invalid_command;

			case 'b':
				if( command[1] == '\0' || !strcmp( command, "balance" ) )
				{
					printf("Enter the user ID: ");
					int uid;	
					if(!scanf("%d", &uid) && uid < 0)
					{
						red();
						printf("Error: user ID doesn't exist\n");
						reset();
					}

					while(getchar() != '\n');
					Users temp = find_user(userlist, uid, usr_no);
					
					if( temp == NULL )
					{
						red();
						printf("Error: user ID doesn't exist\n");
						reset();
					}
					else
					{	
						double bal = temp -> balance;
						white();
						printf("Current balance: %g Bytecoin\n", bal);
						reset();
					}
					break;
				}
				goto invalid_command;

			case 'm':
				if( command[1]=='\0' || !strcmp( command, "mine" ) )
				{
					printf("Enter the user ID: ");
					int uid;	
					if(!scanf("%d", &uid) && uid < 0)
					{
						red();
						printf("Error: user ID doesn't exist\n");
						reset();
					}
					while(getchar() != '\n');
					Users temp_user = find_user(userlist, uid, usr_no);
					
					if( temp_user == NULL )
					{
						red();
						printf("Error: user ID doesn't exist\n");
						reset();
					}
					else
					{	
						int mined = mine( temp_user );

						if( mined == 1 )
						{
							//yellow();
							green();
							printf("Congratulations!! You successfully mined bytecoins.\n");
							reset();
							double bal = temp_user -> balance;
							printf("Current balance in your account: %g bytecoin\n", bal);
						}
						else if( mined==-1 ){
							red();
							printf("Sorry. Not enough bytecoins left.\n");
							reset();
						}
						else{
							red();
							printf("Sorry. Mine unsuccessful.\n");
							reset();
						}
					}
					break;
				}
				goto invalid_command;

			case 'c':
				if( command[1] == '\0' || !strcmp( command, "check" ) )
				{
					byte_value = upd_val( &net_data, byte_value );
					printf("Current Value of bytecoin: $%g\n", byte_value);
					break;
				}
				goto invalid_command;

			case 'u':
				if( command[1] == '\0' || !strcmp( command, "unregister" ) )
				{
					printf("Enter the user ID: ");
					int uid;	
					if(!scanf("%d", &uid) && uid < 0)
					{
						red();
						printf("Error: user ID doesn't exist\n");
						reset();
					}
					while(getchar() != '\n');

					byte_value = upd_val( &net_data, byte_value );
					double bal = delete_user(userlist, uid, byte_value, usr_no);
					if( bal==-1.0 )
					{
						red();
						printf("Error: user ID doesn't exist\n");
						reset();
					}
					else
					{
						net_data.new_usr--;
						green();
						printf("Account successfully unregistered.\n");
						reset();
						printf("Returning balance: $%g\n", bal);
					}
					break;
				}
				goto invalid_command;

			case 'r':
				if( command[1]=='\0' || !strcmp( command, "register" ) )
				{
					// if the number of users are large enough then double the array
					if( 10*net_data.new_trans > 7*usr_no )
						double_user( userlist, &usr_no );

					printf("Enter the initial amount to deposit: $");
					double x;	
					scanf("%lf", &x);
					while(getchar() != '\n');
					if(x < 0)
					{
						red();
						printf("Error: Negative values not allowed.\n");
						reset();
						break;
					}
					Users temp = register_usr(userlist, x, byte_value, usr_no);

					if( temp==NULL ){
						red();
						printf("Sorry. Not enough bytecoins left.\n");
						reset();
					}
					else
					{
						green();
						printf("User added successfully\n");
						reset();
						printf("User id: %.7d\n", temp -> UID);
						printf("Intial balance: %g\n", temp -> balance);
						printf("Joining time: %.2d:%.2d\n", temp->join_time.tm_hour, temp->join_time.tm_min);
						net_data.new_usr++;
						byte_value = upd_val(&net_data,byte_value);
					}

					break;
				}
				goto invalid_command;

			case 'v':
				if( command[1]=='\0' || !strcmp( command, "validity" ) )
				{
					bool v;
					v = Validate(tail);
					printf("--:Checking Validity:--\n");
					if(v == 0){
						green();
						printf("\nNO ERROR\n\t\t\tCheers!!\n");
						reset();
					}
					else if(v == 1){
						blue();
						printf("\nBlock Chain needs Fixing\n");
						printf("Resolving errors");
						for( int i=0; i<5; i++ )
						{
							//delay(500);
							printf(".");
						}
						printf("\nAll the errors have been resolved.\n");
						reset();
					}
					break;
				}
				goto invalid_command;

			case 'p':
				if( command[1] == '\0' || !strcmp( command, "past" ) )
				{
					printf("Enter the user ID: ");
					int uid;	
					if(!scanf("%d", &uid) && uid < 0)
					{
						red();
						printf("Error: user ID doesn't exist\n");
						reset();
					}
					while(getchar() != '\n');
					Users user = find_user(userlist, uid, usr_no);
					
					if( user == NULL )
					{
						red();
						printf("Error: user ID doesn't exist\n");
						reset();
						break;
					}

					Transact temp = user->T;
					if (temp == NULL)
					{
						red();
						printf("Transaction History not found!!\n");
						reset();
						break;
					}

					int i = 0;
					while (temp != NULL && i < 5)
					{
						white();
						printf("%d.\n", i + 1);
						printf("Sender ID : %.7d\n", temp->S_UID);
						printf("Reciver ID : %.7d\n", temp->R_UID);
						printf("Amount Transfered : %g\n", temp->tr_amount);
						printf("Time of transaction : %.2d:%.2d\n", temp->time.tm_hour, temp->time.tm_min);
						temp = temp->next;
						++i;
					}
					reset();
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
				red();
				printf("Command not recognized. Refer to help page:");
				reset();
				printhelp();

		}
	}

exit:;

	// freeing users
	for( unsigned int i = 0; i < usr_no; i++ )
		if( userlist[i] != NULL )
		{
			Transact t = userlist[i]->T;
			while( t!=NULL )
			{
				Transact tmp = t;
				t = t->next;
				free( tmp );
			}
			free( userlist[i] );
		}
	free( userlist );

	while( head_trans != NULL )
	{
		Transact tmp = head_trans;
		head_trans = head_trans->next;
		free( tmp );
	}
		
	cyan();

	printf("Thank you for using %s\n\n", APP_NAME);

    return 0;
}
