#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r->id,
                  &r->userId,
                  r->name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);

    int boole = 1;
    do
    {
        printf("\nEnter the account number:");
        scanf("%d", &r.accountNbr);
        while (getAccountFromFile(pf, userName, &cr))

        {
            if (cr.accountNbr == r.accountNbr)
            {
                boole = 0;
                break;
            }
            else
            {
                boole = 1;
            }
        }
        if (boole == 0)
        {
            printf("✖ This Account already exists for this user\n\n");
        }

        /* code */
    } while (boole == 0);
    do
    {
        printf("\nEnter the country:");
        scanf("%s", r.country);
        if (StrVerify(r.country))
        {
            printf("✖ Country is not valid\n\n");
        }
    } while (StrVerify(r.country));

    do
    {
        printf("\nEnter the phone number:");
        scanf("%s", r.phone);
        if (IntVerify(r.phone))
        {
            printf("✖ Phone number is not valid\n\n");
        }
    } while (IntVerify(r.phone));

    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
    r.id = getID() + 1;

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

int getID()
{
    FILE *fp;
    struct Record inf;
    fp = fopen("data/records.txt", "r");
    if (fp == NULL)
    {
        printf("File not found!\n");
        exit(1);
    }
    int ID = 0;
    while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s", &inf.id, &inf.userId, inf.name, &inf.accountNbr, &inf.deposit.month, &inf.deposit.day, &inf.deposit.year, inf.country, inf.phone, &inf.amount, inf.accountType) != EOF)
    {
        if (inf.id > ID)
        {
            ID = inf.id;
        }
    }
    fclose(fp);
    return ID;
}

int StrVerify(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
        {
            return 1;
        }
    }
    return 0;
}

int IntVerify(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!(str[i] >= 48 && str[i] <= 57))
        {
            return 1;
        }
        return 0;
    }
}