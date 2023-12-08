#include "header.h"
#include "stdbool.h"

const char *RECORDS = "./data/records.txt";
char Username[50];

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %s %d/%d/%d %s %s %s %s",
                  &r->id,
                  &r->userId,
                  r->name,
                  r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  r->phone,
                  r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %s %02d/%02d/%d %s %s %s %s\n\n",
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
    do
    {
        int boole = 1;
        printf("\nEnter today's date(mm/dd/yyyy):");
        if (scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year) == 3)
        {
            if (!CheckDate(r))
            {
                printf("✖ Date is not valid\n\n");
            }
        }
        else
        {
            while (getchar() != '\n')
            {
                boole = 0;
            }
            if (boole == 0)
            {
                printf("Enter the date in the correct format!\n");
            }
        }
    } while (!CheckDate(r));

    int boole = 0;
    do
    {
        FILE *f = fopen(RECORDS, "r");
        printf("\nEnter the account number:");
        scanf("%s", r.accountNbr);
        printf("%d\n", IntVerify(r.accountNbr));
        while (getAccountFromFile(f, userName, &cr))

        {
            printf("%s\n", cr.accountNbr);
            if (strcmp(cr.accountNbr, r.accountNbr) == 0)
            {
                boole = 0;
                break;
            }
            else
            {
                if ((IntVerify(r.accountNbr)))
                {
                    boole = 1;
                }
            }
        }
        if (boole == 0)
        {
            printf("✖ This Account already exists for this user\n\n");
        }
        fclose(f);

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
        if (!IntVerify(r.phone))
        {
            printf("✖ Phone number is not valid\n\n");
        }
    } while (!IntVerify(r.phone));

    do
    {
        printf("\nEnter amount to deposit: $");
        scanf("%s", r.amount);
        if (!IntVerify(r.amount))
        {
            printf("✖ Amount is not valid\n\n");
        }
    } while (!IntVerify(r.amount));
    do
    {
        printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
        scanf("%s", r.accountType);
        if (!CheckSaving(r.accountType))
        {
            printf("✖ Account type is not valid\n\n");
        }
    } while (!CheckSaving(r.accountType));

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
            printf("\nAccount number:%s\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%s \nType Of Account:%s\n",
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

void Modify(struct Record cr, int choice)
{
    FILE *pf = fopen(RECORDS, "r");
    // FILE *oldFILE = fopen("data/records.txt", "r");
    FILE *newFILE = fopen("data/backup.txt", "w");
    struct Record r;
    struct User u;
    struct Record cr;
    char username[50];
    while (getAccountFromFile(pf, username, &r))
    {
        u.id = r.userId;
        strcpy(u.name, r.name);
        // u.name -> r.name;
        printf("sender%s\tfichier:%s", r.accountNbr, cr.accountNbr);
        if (strcmp(r.accountNbr, cr.accountNbr) == 0 && strcmp(u.name,cr.name))
        {
            switch (choice)
            {
            case 1:
                printf("Enter the new phone number:");
                scanf("%s", r.phone);
                if (!IntVerify(r.phone))
                {
                    printf("✖ Phone number is not valid\n\n");
                }
                saveAccountToFile(newFILE, u, r);
                break;
            case 2:
                do
                {
                    printf("Enter the Country: ");
                    scanf("%s", r.country);
                    if (StrVerify(r.country))
                    {
                        printf("✖ Country name is not valid\n\n");
                    }
                } while (StrVerify(r.country));
                saveAccountToFile(newFILE, u, r);
                break;
            }
        }
        else
        {

            saveAccountToFile(newFILE, u, r);
        }
    }
    fclose(pf);
    fclose(newFILE);
    remove(RECORDS);
    rename("data/backup.txt", "data/records.txt");
    success(u);
}

void UpdateAccount(struct User u)
{
    system("clear");
    char userName[100];
    struct Record cr;
    struct Record r;
    int boole = 0;
    do
    {
        FILE *pf = fopen(RECORDS, "r");
        printf("\n\t\t-->> Enter your Account number\n");
        if (scanf("%s", r.accountNbr) == 1)
        {
            while (getAccountFromFile(pf, userName, &cr))
            {
                if ((strcmp(r.accountNbr, cr.accountNbr) == 0) && strcmp(u.name, cr.name) == 0)
                {
                    boole = 1;
                    int choice = 0;
                    printf("[1]- Phone Number\n");
                    printf("[2]- Country\n");
                    if (scanf("%d", &choice) == 1)
                    {
                        switch (choice)
                        {
                        case 1:
                            Modify(r, choice);
                            break;
                        case 2:
                            Modify(r, choice);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            if (boole == 0)
            {
                printf("this number account does not match your account number\n");
            }
            printf("%d\n", boole);
            fclose(pf);
        }
    } while (boole == 0);
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
    while (fscanf(fp, "%d %d %s %s %d/%d/%d %s %s %s %s", &inf.id, &inf.userId, inf.name, inf.accountNbr, &inf.deposit.month, &inf.deposit.day, &inf.deposit.year, inf.country, inf.phone, inf.amount, inf.accountType) != EOF)
    {
        if (inf.id > ID)
        {
            ID = inf.id;
        }
    }
    fclose(fp);
    return ID;
}

void CheckAccount(struct User u)
{
    system("clear");
    char userName[100];
    struct Record cr;
    struct Record r;
    int boole = 0;
    do
    {
        FILE *pf = fopen(RECORDS, "r");
        printf("\n\t\t-->> Enter your Account number\n");
        if (scanf("%s", r.accountNbr) == 1)
        {
            while (getAccountFromFile(pf, userName, &cr))
            {
                if ((strcmp(r.accountNbr, cr.accountNbr) == 0) && strcmp(u.name, cr.name) == 0)
                {
                    boole = 1;
                    printf("Account Number : %s\nDeposit Date: %d/%d/%d\n Country : %s\n Phone Number : %s\n Amount Deposited %s \n Type of Account: %s",
                           r.accountNbr, r.deposit.month, r.deposit.day, r.deposit.year, r.country, r.phone, r.amount, r.accountType);
                }
            }
        }
        fclose(pf);
    } while (boole == 0);
    success(u);
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
            return 0;
        }
    }
    return 1;
}

bool CheckSaving(char str[])
{
    if (strcmp(str, "saving") == 0 || strcmp(str, "current") == 0 || strcmp(str, "fixed01") == 0 || strcmp(str, "fixed02") == 0 || strcmp(str, "fixed03") == 0)
    {
        return true;
    }
    return false;
}

bool CheckDate(struct Record r)
{
    int jour = r.deposit.day;
    int mois = r.deposit.month;
    int année = r.deposit.year;

    if (!(mois < 1 || mois > 12 || jour < 1 || jour > 31 || année < 1960 || année > 2023))
    {
        if ((mois == 2 && jour > 28 && !CheckYear(année)) || (mois == 2 && jour > 29 && CheckYear(année)))
        {
            return false;
        }
        if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30)
        {
            return false;
        }
        return true;
    }
    return false;
}

bool CheckYear(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
