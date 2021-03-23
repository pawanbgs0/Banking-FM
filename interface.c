#include <stdio.h>
#include "header.h"

/*Before running it create a file named "no_of_account" at "/home/pawan/Documents/C/Project/Files/Account_details/" */

int main()
{
    int choice;
    unsigned long given_num;
    printf("Hello Manager! What can I do for you? \n");
    printf("\n1. Create / Update an account.\n2. Deposite / Withdraw Amount.\n3. Show Account Details");
    printf("\n\nPlease Enter your choice: ");
    again:
    scanf("%d", &choice);

    switch(choice)
    {
        case 1: 
                account_create();
                break;
        case 2:
                printf("\nEnter Account Number: ");
                scanf("%lu", &given_num);
                account_transaction(given_num);
                break;
        case 3:
                printf("\nEnter Account Number: ");
                scanf("%lu", &given_num);
                account_details(given_num);
                break;
        case 4:
                /*function*/
                break;
        case 5:
                /*function*/
                break;
        default:
                printf("\nPlease Enter a valide choice: ");
                goto again;
    }
    return 0;
}