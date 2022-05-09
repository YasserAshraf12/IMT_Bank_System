#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <ctype.h>

enum status{Active, Restricted, Closed};
enum type{Admin, Client};

typedef struct Bank_Account
{
    char full_name[50];
    char address[50];
    char national_Id[15];
    char bank_acc_id[15];
    char guardian_national_id[15];
    char username[31];
    char password[31];
    int age;
    int balance;
    boolean guardian;
    enum status account_status;
    enum type account_type;
    Bank_Account * next;
}Bank_Account;

typedef struct LinkedList
{
    Bank_Account * head;
    Bank_Account * tail;
    int nNodes;
}LinkedList;

void Bank_Account_VoidInit(Bank_Account * node)
{
    strcpy(node->full_name, "");
    strcpy(node->address, "");
    strcpy(node->national_Id, "");
    strcpy(node->username, "");
    strcpy(node->password, "");
    strcpy(node->guardian_national_id, "");
    strcpy(node->bank_acc_id, "");
    node->age = 0;
    node->balance = 0;
    node->guardian = 0;
    node->account_status = Active;
    node->account_type = Client;
    node->next = NULL;
};

void LinkedList_VoidInit(LinkedList * list)
{
    list->head = NULL;
    list->tail = NULL;
    list->nNodes = 0;
};

boolean create_account(LinkedList * list,
    char fullname[50], char addr[50], char nid[15],
    char guardian_nid[15], char usrname[31],
    char passw[31], boolean guardian_status,
    int agee, int balancee,
    enum status accountStatus, enum type accountType){

    Bank_Account * temp = (Bank_Account*)malloc(sizeof(Bank_Account));
    Bank_Account_VoidInit(temp);
    
    if(validateInputs(fullname, nid, guardian_nid) && checkExistingUser(list, usrname))
    {
        strcpy(temp->full_name, fullname);
        strcpy(temp->address, addr);
        strcpy(temp->national_Id, nid);
        strcpy(temp->username, usrname);
        strcpy(temp->password, passw);
        strcpy(temp->guardian_national_id, guardian_nid);
        temp->age = agee;
        temp->balance = balancee;
        temp->guardian = guardian_status;
        temp->account_status = accountStatus;
        temp->account_type = accountType;
        temp->next = NULL;

        if(list->head == NULL)
        {
            list->head = list->tail = temp;
        }
        else{
            temp->next = list->head;
            list->head = temp;
        }
        list->nNodes++;
    }
    else
        return 0;
};

boolean login(LinkedList * list, char usrname[31], char passw[31])
{
    if(list->head == NULL)
    {
        return 0;
    }

    Bank_Account * temp = (Bank_Account*)malloc(sizeof(Bank_Account));
    Bank_Account_VoidInit(temp);

    temp = list->head;
    while(temp)
    {
        if(temp->username == usrname)
        {
            if (temp->password == passw)
                return 1;
            else
                return 0;
        }
        temp = temp->next;
    }
    return 0;
};

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
        printf("%s", temp->full_name);
        printf("%s", temp->national_Id);
        printf("%d", temp->balance);
        printf("%s", "\n");
        temp = temp->next;
    }
    printf("%s", "\n");
    
}

boolean validateInputs(char fullname[50], char nid[15], char gNid[15])
{
    int space_count = 0;
    boolean check_fname = 0;
    for(int i = 0; fullname[i] != '\0'; ++i) {
        if (fullname[i] ==' '){
            space_count++;
        }
        if(space_count >= 4)
        {
            check_fname = 1;
            break;
        }
    }

    boolean check_nid = 0;
    for(int i = 0; nid[i] != '\0'; ++i) {

        if (!isdigit(nid[i])){
            check_nid = 1;
            break;
        }
    }

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
};

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
};


int LinkedList_IntSize(LinkedList * list)
{
    return list->nNodes;
};

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


int main(){

    LinkedList ls;
    LinkedList_VoidInit(&ls);

    Bank_Account ba;
    Bank_Account_VoidInit(&ba);
    strcpy(ba.full_name, "Yasser Ashraf Salah El Din Mohamed");
    strcpy(ba.address, "Street 9, Maadi");
    strcpy(ba.national_Id, "");


    return 0;
}