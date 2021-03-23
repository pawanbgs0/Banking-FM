#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void account_create();   /*To create account*/
unsigned long int account_number_generator();       /*to generate the account number*/
void account_balance(unsigned long int);    /*to print the total amount avaliable in the account*/
void account_transaction(unsigned long int);
char* get_time(void);
double account_update(unsigned long int, double, int);
void account_details(unsigned long int);

char file_exnt[] = ".txt";       /*file Extension*/
FILE *list_aadhar;
FILE *list_account;
FILE *account_book;

struct details
{
    char fname[10];
    char lname[10];
    char add[50];
    char aadhar[15];
    double mobile;
    unsigned short age;

};    

struct tranx
{
    double tamount;
    double damount; 
    double wamount;
};


char* get_time(void)
{
    time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    // printf("Current Time : %s\n", time_str);

    return time_str;
}

void account_create()
{
    struct details det;
    struct tranx txn;
    char buffer, update;
    char id[15];
    FILE *fptr;
    FILE *acsum;
    FILE *temp;
    char acc_numc[15];
    char file_add[] = "/home/pawan/Documents/C/Project/Files/data/";   /* Local Address to store files */
    char file_add_ad[] = "/home/pawan/Documents/C/Project/Files/Account_details/";
    char file_cadd[100];
    unsigned long int acc_num = 0;

    printf("\nEnter First Name: ");
    scanf("%c", &buffer);
    fgets(det.fname, sizeof(det.fname), stdin);
    det.fname[strlen(det.fname) - 1] = '\0';

    printf("\nEnter Last Name: ");
    fgets(det.lname, sizeof(det.lname), stdin);
    det.lname[strlen(det.lname) - 1] = '\0';

    printf("\nEnter Address: ");
    fgets(det.add, sizeof(det.add), stdin);
    det.add[strlen(det.add) - 1] = '\0';

    printf("\nEnter Mobile Number: ");
    scanf("%lf", &det.mobile);

    printf("\nEnter Age: ");
    scanf("%hd", &det.age);

    scanf("%c", &update);

    printf("\nEnter Aadhar Number: ");
    fgets(det.aadhar, sizeof(det.aadhar), stdin);
    det.aadhar[strlen(det.aadhar) - 1] = '\0';

    snprintf(file_cadd, sizeof(file_cadd), "%s%s%s%s", file_add, det.fname, det.aadhar, file_exnt);   /*To store complete file address with file name is file_cadd*/
    
    fptr = fopen(file_cadd, "a");  /*to amend if file is available else create */
    fclose(fptr);
    
    fptr = fopen(file_cadd, "r");
    fread(&id, sizeof(char), 14, fptr);  /* To read the first 14 ch of file fptr*/
    id[12] = '\0';  /*restricting aadhar number to 12 */
    fclose(fptr);

    if (atoll(id) == atoll(det.aadhar))  /* atoll changing string to long long */
    {
        printf("\nAccount already exists with same Aadhar Number\n");
        printf("\nDo you want to update the details (Y/N): ");
        scanf("%c", &update);
        if (update == 'Y' || update == 'y')
        {
            fptr = fopen(file_cadd, "w");
            fprintf(fptr, "%s", det.aadhar);
            fprintf(fptr,"\nFirst Name - %s\nLast Name - %s", det.fname, det.lname);
            fprintf(fptr,"\nAddress - %s", det.add);
            fprintf(fptr,"\nAadhar Number  - %s\nMob - %.0lf\nAge - %hd", det.aadhar, det.mobile, det.age);
            fclose(fptr);
            printf("\nDetails are now updated\nThank You\n");
        }
        else
        {
            exit(1);
        }  
    }
    else
    {
        fptr = fopen(file_cadd, "w");
        fprintf(fptr, "%s", det.aadhar);
        fprintf(fptr,"\nFirst Name - %s\nLast Name - %s", det.fname, det.lname);
        fprintf(fptr,"\nAddress - %s", det.add);
        fprintf(fptr,"\nAadhar Number  - %s\nMob - %.0lf\nAge - %hd", det.aadhar, det.mobile, det.age);
        printf("\n\nYour account is now created.");
        acc_num = account_number_generator();    /*Account Number stored in acc_num*/
        printf("\n\nYour account number is %lu", acc_num);
        fprintf(fptr, "\nAccount Number - %lu", acc_num);
        fclose(fptr);

        temp = fopen("temp.txt", "w");  /*to convert decimal acc_num to string*/
        fprintf(temp, "%lu", acc_num);
        fclose(temp);
        temp = fopen("temp.txt", "r");
        fscanf(temp, "%s", acc_numc);
        fclose(temp);

        snprintf(file_cadd, sizeof(file_cadd), "%s%s%s", file_add_ad, acc_numc, file_exnt);   /*To store complete file address with file name is file_cadd*/
    
        acsum = fopen(file_cadd, "w");
    
        // fprintf(acsum, "%lu\n", acc_num); /*to print account number in a new file */
        fprintf(acsum, "%.2lf\n", txn.tamount);  /*to print total amount in a new file*/
        fclose(acsum);

        list_account = fopen("list_of_account.txt", "a");  /*to store all account number in a file */
        fprintf(list_account, "%lu\n", acc_num);
        fclose(list_account);

        account_balance(acc_num);


    }
}



unsigned long int account_number_generator()
{
    FILE *fileptr;
    int fixed_num = 110320210;
    unsigned long int account_num = 0;
    unsigned long int num;

    fileptr = fopen("/home/pawan/Documents/C/Project/Files/Account_details/no_of_account.txt", "r");
    fscanf(fileptr, "%lu", &num);
    fclose(fileptr);

    fileptr = fopen("/home/pawan/Documents/C/Project/Files/Account_details/no_of_account.txt", "w");
    fprintf(fileptr, "%lu", num + 1);
    fclose(fileptr);

    account_num = fixed_num + num;

    return account_num;
}


void account_balance(unsigned long int acc_num)
{

    FILE *acsum;
    FILE *temp;
    struct tranx txn;
    char file_add[] = "/home/pawan/Documents/C/Project/Files/Account_details/";   /* Local Address to store files */
    char file_exnt[] = ".txt";       /*file Extension*/
    char account_book_add[] = "/home/pawan/Documents/C/Project/Files/Account_Book/";
    char file_cadd[100];
    char acc_numc[15];

    temp = fopen("temp.txt", "w");  /*to convert decimal acc_num to string*/
    fprintf(temp, "%lu", acc_num);
    fclose(temp);
    temp = fopen("temp.txt", "r");
    fscanf(temp, "%s", acc_numc);
    fclose(temp);


    snprintf(file_cadd, sizeof(file_cadd), "%s%s%s", account_book_add, acc_numc, file_exnt);  /*To create account_book layout*/
    account_book = fopen(file_cadd, "w");
    fprintf(account_book, "Date & Time                      Amount Deposited        Amount Withdrawn        Total Amount\n");
    fclose(account_book);
}

void account_transaction(unsigned long int given_num)
{
    struct tranx txn;
    unsigned long temp;
    char account_book_add[] = "/home/pawan/Documents/C/Project/Files/Account_Book/";
    char file_add[] = "/home/pawan/Documents/C/Project/Files/Account_details/";   /* Local Address to store files */
    char file_exnt[] = ".txt";       /*file Extension*/
    char file_cadd[100];
    char tempc[15];
    char ch, acc_numc[15];
    int choice, i;
    FILE *actxn;
    FILE *check;
    FILE *tempf;
    int flag = 0, upflag;

    tempf = fopen("temp.txt", "w");  /*to convert decimal given_num to string*/
    fprintf(tempf, "%lu", given_num);
    fclose(tempf);
    tempf = fopen("temp.txt", "r");
    fscanf(tempf, "%s", acc_numc);
    fclose(tempf);

    printf("1. Deposite\n2. Withdraw");
    printf("\nPlease Enter your choice: ");
    here:
    scanf("%d", &choice);
    
    list_account = fopen("list_of_account.txt", "r");

    do      /*to check if account exist*/
    {
        ch = fgetc(list_account);
        fscanf(list_account, "%lu", &temp);
        if (given_num == temp)
        {
            flag = 1;
            break;
        }
    }while (ch != EOF);
    
    fclose(list_account);

    if (flag == 1)
    {
        switch (choice)
        {
            case 1:
                    printf("\nEnter the amount to be deposited: ");
                    scanf("%lf", &txn.damount);
                    printf("\n%.2lf deposited", txn.damount);

                    /*to update account book */
                    upflag = 0;


                    txn.tamount = account_update(temp, txn.damount ,upflag);
                    printf("\nTotal balance is %.2lf\n", txn.tamount);

                    break;

            case 2:
                    printf("\nEnter the amount to be withdrawn: ");
                    scanf("%lf", &txn.wamount);

                    /*to update account book */

                    upflag = 1;
                    account_update(temp, txn.wamount ,upflag);

                    break;
            default:
                    printf("\nPlease enter a valid choice: ");
                    goto here;
    }
    }
    else
    {
        printf("\nAccount does not exist\n");
    }
    
}

double account_update(unsigned long int acc_num, double amount, int upflag)
{
    char file_cadd[100];
    char account_book_add[] = "/home/pawan/Documents/C/Project/Files/Account_Book/";
    char file_add[] = "/home/pawan/Documents/C/Project/Files/Account_details/";
    FILE *tempf;
    FILE *to_update;
    FILE *actxn;
    double total_amount = 0;
    char acc_numc[20];
    struct tranx txn;
    double temp_amount;
    
    tempf = fopen("temp.txt", "w");  /*to convert decimal given_num to string*/
    fprintf(tempf, "%lu", acc_num);
    fclose(tempf);
    tempf = fopen("temp.txt", "r");
    fscanf(tempf, "%s", acc_numc);
    fclose(tempf);

    snprintf(file_cadd, sizeof(file_cadd), "%s%s%s", file_add, acc_numc, file_exnt);
    to_update = fopen(file_cadd, "r");
    fscanf(to_update,"%lf", &temp_amount);
    fclose(to_update);


    if (upflag == 0)
    {
        total_amount = temp_amount + amount;

        snprintf(file_cadd, sizeof(file_cadd), "%s%s%s", account_book_add, acc_numc, file_exnt);
        account_book = fopen(file_cadd, "a");
        fprintf(account_book, "%s               %.2lf                   %.2lf               %.2lf\n", get_time(), amount, txn.wamount, total_amount);
        fclose(account_book);

        snprintf(file_cadd, sizeof(file_cadd), "%s%s%s", file_add, acc_numc, file_exnt);
        actxn = fopen(file_cadd, "w");
        fprintf(actxn, "%.2lf", total_amount); /*to store total amount in a file*/
        fclose(actxn);

        return total_amount;

    }
    else
    {
        if (amount < temp_amount)
        {
            total_amount = temp_amount - amount;

            snprintf(file_cadd, sizeof(file_cadd), "%s%s%s", account_book_add, acc_numc, file_exnt);
            account_book = fopen(file_cadd, "a");
            fprintf(account_book, "%s               %.2lf                   %.2lf               %.2lf\n", get_time(), txn.damount, amount, total_amount);
            fclose(account_book);

            snprintf(file_cadd, sizeof(file_cadd), "%s%s%s", file_add, acc_numc, file_exnt);
            actxn = fopen(file_cadd, "w");
            fprintf(actxn, "%.2lf", total_amount); /*to store total amount in a file*/
            fclose(actxn);

            printf("\nTotal Available Amount is %.2lf", total_amount);
            return total_amount;
        }
        else
        {
            printf("\nInvalid Amount\n");
            printf("\nTotal Available Amount is %.2lf\n", temp_amount);
            return temp_amount;
        }
    }

}

void account_details(unsigned long int given_num)
{
    FILE *list_account;
    FILE *tempf;
    unsigned long int temp;
    char account_book_add[] = "/home/pawan/Documents/C/Project/Files/Account_Book/";
    char ch;
    char given_numc[15];
    char file_cadd[100];
    int flag = 0;

    list_account = fopen("list_of_account.txt", "r");

    do      /*to check if account exist*/
    {
        ch = fgetc(list_account);
        fscanf(list_account, "%lu", &temp);
        if (given_num == temp)
        {
            flag = 1;
            break;
        }
    }while (ch != EOF);
    
    fclose(list_account);

    if (flag == 1)
    {
        tempf = fopen("temp.txt", "w");  /*to convert decimal given_num to string*/
        fprintf(tempf, "%lu", given_num);
        fclose(tempf);
        tempf = fopen("temp.txt", "r");
        fscanf(tempf, "%s", given_numc);
        fclose(tempf);

        snprintf(file_cadd, sizeof(file_cadd), "%s%s%s", account_book_add, given_numc, file_exnt);
        account_book = fopen(file_cadd, "r");

        do      /*to print account book*/
        {
            ch = fgetc(account_book);
            putchar(ch);
        }while (ch != EOF);
    
        fclose(account_book);
        }
        else
        {
            printf("\nAccount does not exist\n");
        }
}