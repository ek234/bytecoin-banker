# Bytecoin

## This is a group project made during DSA course at IIIT-H.  
<img src="./bytecoin.jpg" alt="drawing" width="200px;">  

- There will be a total of *10 billion* bytecoins of which can be bought by users.   
- Value of ***Bytecoins*** keeps changing with the flow of trading.  
- To have a smooth and full experience of this programe we recommend you to make these changes to your terminal 
    - Make background color to black (R = 30; G = 30; B = 30).
    - Maximize your terminal window. 
- To Start Programme enter this command in your Terminal. This bash file has all the  
commands necessary to compile and execute the programme   

~~~
$./run.sh 
~~~
- List of functions this programme can execute are: 
    1. **Register User** : Takes an initial deposit amount.  
        **Syntax** `register` alias `r`
    2. **Transaction** : Takes Sender ID, Reciver's ID and number of bytecoins to be transferred.   
        **Syntax** `transfer` alias `t`
    3.  **Balance** : Checks Your balance. Takes your ID.  
        **Syntax** `balance` alias `b`
    4. **Attack** : Randomly Changes *Nonce* of a block From **BlockChain**.    
        **Syntax** `attack` alias `a`
    5. **Validate** : Validates **BlockChain** and if any block's *Nonce* was changed correct it.  
        **Syntax** `validate` alias `v`
    6. **Help** : Shows a list of all the commands.  
        **Syntax** `help` alias `h`
    7. **Check Value of bytecoins** : Current value of 1 bytecoin in $.  
        **Syntax**  `check` alias `c`
    8. **Mine Bytecoins** : Gives you some bytecoins if you answer our Question correctly.  
        **Syntax** `mine` alias `m` 
    9. **Transaction History** : Shows last 5 transaction of a user.Takes a valid user id as input.  
        **Syntax** `past` alias `p` 
    10. **Unregister** : To delete your ID and Withdraw all the bytecoins from your account.  
        **Syntax** `unregister` alias `u`
    11. **Exit Programe** : Terminates the programme.  
        **Syntax** `exit` alias `e`

