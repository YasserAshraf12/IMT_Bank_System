/*******************************************************/

/*   Description: Bank System Based On Linked_List     */

/*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <ctype.h>

/* User Account details */

enum status{Active, Restricted, Closed};
enum type{Admin, Client};

/* Bank Account */

typedef struct Bank_Account
{
    char full_name[50];
    char address[50];
    char national_Id[15];
    // how about make it integar and increase every new account
    char bank_acc_id[11];
    char username[31];
    char password[31];
    int Account_Id;
    int age;
    int balance;
    boolean guardian;
    char guardian_national_id[15];
    enum status account_status;
    enum type account_type;

    struct Bank_Account * next;
}Bank_Account;

/* Linked List */

typedef struct LinkedList
{
    Bank_Account * head;
    Bank_Account * tail;
    int nNodes;
}LinkedList;


// initialize the default data of a client*/

void Bank_Account_VoidInit(Bank_Account * node)
{
    strcpy(node->full_name, "");
    strcpy(node->address, "");
    strcpy(node->national_Id, "");
    strcpy(node->username, "");
    strcpy(node->password, "");
    strcpy(node->guardian_national_id, "");
    strcpy(node->bank_acc_id, "");
    node->Account_Id = 999999999;
    node->age = 0;
    node->balance = 0;
    node->guardian = 0;
    node->account_status = Active;
    node->account_type = Client;
    node->next = NULL;
}


//Initialization Function For The Accounts List

void LinkedList_VoidInit(LinkedList * list)
{
    list->head = NULL;
    list->tail = NULL;
    list->nNodes = 0;
}



//// Test If The Inputs That The User Provided Are Valid  //////

boolean validateInputs(char fullname[50], char nid[15], char gNid[15])
{
    /// check if the name is alphabet
    int space_count = 0;
    boolean check_fname = 0;
    for(int i = 0; fullname[i] != '\0'; ++i) {
        //isalpha(fullname[i])!=0
        if (fullname[i] ==' '){
            space_count++;
        }
        if(space_count >= 4)
        {
            check_fname = 1;
            break;
        }
    }

    //test if the nid >14
    boolean check_nid = 0;
    for(int i = 0; nid[i] != '\0'; ++i) {

        if (!isdigit(nid[i])){
            check_nid = 1;
            break;
        }
    }

    //test if the age is less than 21
    boolean check_gNid = 0;
    for(int i = 0; gNid[i] != '\0'; ++i) {

        if (!isdigit(gNid[i])){
            check_gNid = 1;
            break;
        }
    }

    if (check_fname || check_gNid || check_nid)
        return 0;

    return 1;
}



/////// Check if the User Name is Used In The Clients Accounts Before ///////


boolean checkExistingUser(LinkedList * list, char usernm[31])
{
        if(list->head == NULL)
        {
            return 1;
        }
        Bank_Account * temp = (Bank_Account*)malloc(sizeof(Bank_Account));
        Bank_Account_VoidInit(temp);

        temp = list->head;
        while(temp)
        {
            if(temp->username == usernm)
            {
                return 0;
            }
            temp = temp->next;
        }
        return 1;
}


//////////////////////// random Password ////////////////////////////////

void rand_str(char *dest, size_t length) {
    char charset[] = "0123456789"
                    "abcdefghijklmnopqrstuvwxyz"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}


//////////// Create New Account ////////////////////
// only admin user can use this function

boolean create_account(LinkedList * list,
    char fullname[50], char addr[50], char nid[15],
    char guardian_nid[15], char usrname[31],
    char passw[31], boolean guardian_status,
    int agee, int balancee){

    Bank_Account * temp = (Bank_Account*)malloc(sizeof(Bank_Account));
    Bank_Account_VoidInit(temp);

    if(validateInputs(fullname, nid, guardian_nid) && checkExistingUser(list, usrname))
    {
        // to add on account id
        list->nNodes++;
        // Generate Account _ID
        strcpy(temp->full_name, fullname);
        strcpy(temp->address, addr);
        strcpy(temp->national_Id, nid);
        strcpy(temp->username, usrname);
        //here use the random initialize the password

        //rand_str(pass,32)

        strcpy(temp->password, passw);
        strcpy(temp->guardian_national_id, guardian_nid);
        temp->age = agee;
        temp->balance = balancee;
        temp->guardian = guardian_status;
        temp->Account_Id += list->nNodes;
        temp->next = NULL;

        if(list->head == NULL)
        {
            list->head = list->tail = temp;
        }
        else{
            temp->next = list->head;
            list->head = temp;
        }

    }
    else
        return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////

/////// Function To Initialize The The Admin Data And Some Initial Users ///////////////////////////
LinkedList Start_Bank_System()
{
    LinkedList bank;
    LinkedList_VoidInit(&bank);

   /* LinkedList * list,
    char fullname[100], char addr[100], char nid[14],
    char guardian_nid[14], char usrname[31],
    char passw[31], boolean guardian_status,
    int agee, int balancee

   */
    char fullname[50]="Mariam Maged Shaker Londey";
    char addr[50]="dddd";
    char nid[15]="21345678912345";
    char guardian_nid[15]="21345678912345";
    char usrname[31]="Mariam_Maged";
    char passw[31]="123456" ;
    boolean guardian_status=0;
    int agee=22;
    int balancee=200;

    boolean ad1=create_account(&bank,fullname,addr,nid,guardian_nid,usrname,passw,guardian_status,agee,balancee);

    char fullname_1[50]="maged shaker lll hgg";
    char addr_1[50]="dddsssssddd";
    char nid_1[15]="21322278912345";
    char guardian_nid_1[15]="11145678912345";
    char usrname_1[31]="Mar_Maged";
    char passw_1[31]="12345" ;
    boolean guardian_status_1=0;
    int agee_1=22;
    int balancee_1=450;

    boolean use=create_account(&bank,fullname_1,addr_1,nid_1,guardian_nid_1,usrname_1,passw_1,guardian_status_1,agee_1,balancee_1);
    if (use && ad1)
        printf("Started The System Successfully...\n");

    return bank;
}




///////////////////////////////////////////////////////////////////////////////////////////

///////////// LOG In User Account ////////////////////////

/////// using Account ID and Password

Bank_Account* login(LinkedList * list, char usrname[31], char passw[31])
{
    if(list->head == NULL)
    {
        return NULL;
    }

    Bank_Account * temp = (Bank_Account*)malloc(sizeof(Bank_Account));
    Bank_Account_VoidInit(temp);

    temp = list->head;
    while(temp)
    {
        if(temp->username == usrname)
        {
            if (temp->password == passw)
                return temp;
            else
                return NULL;
        }
        temp = temp->next;
    }
    return NULL;
}


///////// The Number Of Users /////////////

int LinkedList_IntSize(LinkedList * list)
{
    return list->nNodes;
}


//////////// Show The Informations Of All Users //////////////////////

void print_allAccounts(LinkedList * list)
{
    if(list->head == NULL)
    {
        return;
    }

    Bank_Account * temp = (Bank_Account*)malloc(sizeof(Bank_Account));
    Bank_Account_VoidInit(temp);

    temp = list->head;
    while(temp)
    {
        printf("%s\t", temp->full_name);
        printf("%s\t", temp->national_Id);
        printf("%d\t", temp->balance);
        printf("%d\t", temp->Account_Id);
        printf("%s", "\n");
        temp = temp->next;
    }
    printf("%s", "\n");

}

void print_account(LinkedList * list, char bank_id[11])
{
    if(list->head == NULL)
    {
        printf("%s", "No Such Account...");
        return;
    }

    Bank_Account * temp = (Bank_Account*)malloc(sizeof(Bank_Account));
    Bank_Account_VoidInit(temp);

    temp = list->head;
    while(temp)
    {
        if(temp->bank_acc_id == bank_id){
            printf("%s\t", temp->full_name);
            printf("%s\t", temp->national_Id);
            printf("%d\t", temp->balance);
            printf("%d\t", temp->Account_Id);
            printf("%s", "\n");
            break;
        }
        temp = temp->next;
    }
    printf("%s", "\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////


////////////// Enter Valid Account ID ////////////////

int Enter_Valid_Input()
{
    int account_id;
    printf("Please Enter The Account ID Of The Client:  ");
    int continue_flag = 1;
    scanf("%d",&account_id);
    while((continue_flag==1) && (account_id<1000000000))
    {
        printf("* The Account ID You entered is invalid it must contains 10 digit...\n");
        printf("-If you Wanted To Continue Press One (1)\n -If You Wanted To Exit Press Zero (0)\nYour Choice:  ");
        scanf("%d",&continue_flag);
        if(continue_flag==0)
        {
            return 0 ;
        }
        else
        {
            printf("\nPlease Enter The Valid Account ID OF The Client:  ");
            scanf("%d",&account_id);
        }


    }
    return account_id;

}


///////////// check the account_ID of user if it existed or not //////////////////
Bank_Account * check_Existing_Accounnt_Id(LinkedList * bank , int id)
{
    Bank_Account * account = (Bank_Account*)malloc(sizeof(Bank_Account));
    Bank_Account_VoidInit(account);

    int check_exist=0;
    account=bank->head;
    while(account)
    {
        if(account->Account_Id == id)
        {
            check_exist=1;
            return account;
        }
        account = account->next;
    }

    return NULL;
}

//////// Open The Account //////////////

////// Choose The Service //////////////

 Bank_Account * Open_Existing_Account(LinkedList* bank)
{
    int account_id=Enter_Valid_Input();
    if(account_id==0)
    {
        printf("Back To Main Menu...");
        return NULL ;
    }
    int service_num=10;
    Bank_Account * account_u = (Bank_Account*)malloc(sizeof(Bank_Account));
    //Bank_Account_VoidInit(account_u);
    account_u=check_Existing_Accounnt_Id(bank ,account_id);
    if(account_u == NULL)
    {
        printf("This Account Is Not Found... \n");
        printf("go back to main menu");
    }
    else
    {
        printf("Choose The Service You Want:\n");
        printf("* Make Transaction --> Press (1)\n");
        printf("* Get Cash --> Press (2)\n");
        printf("* Deposit in Account --> Press (3)\n");
        printf("* Change Account Status --> Press (4)\n");
        printf("* Return to main menu --> Press (5)\n");
        printf("* Exit the System --> Press (0)");
        printf("\n Your Choice:  ");
        scanf("%d",&service_num);

    }

    return account_u;

}


//////////////////////  Make Transaction ///////////////////

Bank_Account* Get_Reciever_Account(LinkedList * bank)
{
    printf("Enter The Reciever Account ID :  ");
    int reciever_id=Enter_Valid_Input();
    if(reciever_id == 0)
    {
        printf("Back To Main Menu...");
        return NULL;
    }

    Bank_Account * recieve_account = (Bank_Account*)malloc(sizeof(Bank_Account));
    recieve_account=check_Existing_Accounnt_Id(bank, reciever_id);

    return recieve_account;
}

int enter_Valid_Balance_ToBe_Transacte(Bank_Account * sender)
{
    int balance=0;
    printf("Please Enter The Balance:  ");
    scanf("%d",&balance);
    int continue_transaction=1;

    while(balance > sender->balance)
    {
        if(balance > sender->balance)
            printf("the value of balance you entered is greater than the client balance...\n");
        printf("if you want to continue press (1)\n");
        printf("If You Want To Exit Press (0)\n");
        printf("Your Answer:  ");
        scanf("%d",&continue_transaction);
        if(continue_transaction==0)
            return 0;

        printf("Please Enter the balance in digit:  ");
        scanf("%d",&balance);

    }

    return balance;
}



void Make_Transaction(LinkedList * bank, Bank_Account * sender)
{
    Bank_Account * receiver = (Bank_Account*)malloc(sizeof(Bank_Account));
    receiver=Get_Reciever_Account(bank);

    if(receiver == NULL)
    {
        printf("This Account Is Not In The System......\n");
        printf("Back To The Main Menu...\n");
        return;
    }
    int balance=enter_Valid_Balance_ToBe_Transacte(sender);

    if (balance == 0)
    {
        printf("Back To The Main Menu...\n");
        return;
    }

    sender->balance -=balance;
    receiver->balance += balance;

    printf("Make Transaction Is Done.......\n");

}

////////////////////////// Get Cash //////////////////////////

int Get_Cash(Bank_Account * client)
{
    int balance=enter_Valid_Balance_ToBe_Transacte(client);

    if (balance == 0)
    {
        printf("Back To The Main Menu...\n");
    }
    else
    {
        client->balance -=balance;
        printf("Getting Cash Is Done.......\n");
    }
    return balance;
}


////////////////////////// Deposit in Account /////////////////
void Deposit_in_Account(Bank_Account * client)
{

    int balance;
    printf("Please Enter the balance in digit:  ");
    scanf("%d",&balance);

    if (balance >= 0)
    {
        client->balance +=balance;
        printf("Deposit Cash Is Done.......\n");

    }
    else
    {
        printf("Back To The Main Menu...\n");
    }

}


int main(){

    LinkedList system;
    LinkedList_VoidInit(&system);

    system=Start_Bank_System();

    Bank_Account * sender = (Bank_Account*)malloc(sizeof(Bank_Account));
    sender=Open_Existing_Account(&system);
    Make_Transaction(&system,sender);
    print_allAccounts(&system);

    return 0;

}









