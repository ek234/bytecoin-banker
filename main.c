#include "./main.h"

int main()
{

	//seeding randomizer for other functions
	srand((unsigned) time(NULL));

//	inits

	// max number of users that can be managed at the start of the program
	usr_no = 100000;
	// array of ptrs of userslist struct
	Users* userlist = (Users*) malloc( usr_no*sizeof(Users) );
	for( unsigned int i=0; i<usr_no; i++ )
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

					int x = Attack();
					if( x == -1 ){
						red();
						printf("Attack failed :(\n");
						reset();
					}
					else{
						green();
						printf("Successful att4ck. Compromised block number: %d\n", x);
						reset();
						bit_value = after_attack(bit_value);
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
						a = find_user(userlist, s_uid);
					} while( a == NULL && printf("Invalid UID\n") );
					// taking reciever's UID until it's valid
					do{
						printf("Enter receiver's ID: ");
						scanf("%d", &r_uid);
						while(getchar() != '\n');
						// finding reciever
						b = find_user(userlist, r_uid);
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
								emptyBlock(head_trans);
								block_num = 1;
							}
							else
								createBlock(head_trans, block_num++);
							head_trans->next = NULL;
							Ntransactions = 1;
						}
						
/*temp for testing*/	assert(Ntransactions <= trans_per_block);

						
						green();
						printf("Transaction was successful.\n");
						bit_value = upd_val(&net_data,bit_value);
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
					Users temp = find_user(userlist, uid);
					
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
						printf("Current balance: %g Bitcoin\n", bal);
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
					Users temp_user = find_user(userlist, uid);
					
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
							printf("Congratulations!! You successfully mined bitcoins.\n");
							reset();
							double bal = temp_user -> balance;
							printf("Current balance in your account: %g Bitcoin\n", bal);
						}
						else if( mined==-1 ){
							red();
							printf("Sorry. Not enough bitcoins left.\n");
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
					bit_value = upd_val( &net_data, bit_value );
					printf("Current Value of bitcoin: $%g\n", bit_value);
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

					bit_value = upd_val( &net_data, bit_value );
					double bal = delete_user(userlist, uid, bit_value);
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
						double_user( userlist );

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
					Users temp = register_usr(userlist, x, bit_value);

					if( temp==NULL ){
						red();
						printf("Sorry. Not enough bitcoins left.\n");
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
						bit_value = upd_val(&net_data,bit_value);
					}

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
					Users user = find_user(userlist, uid);
					
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
