#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

enum status{Active, Restricted, Closed};
enum type{Admin, Client};

typedef struct Bank_Account
{
    char full_name[50];
    char address[50];
    char national_Id[14];
    char bank_acc_id[15];
    char guardian_national_id[14];
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

void ListNode_VoidInit(Bank_Account * node)
{
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

int LinkedList_IntSize(LinkedList * list)
{
    return list->nNodes;
}

int main(){

    return 0;
}