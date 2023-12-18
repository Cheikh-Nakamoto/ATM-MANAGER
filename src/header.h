#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    char phone[15];
    char accountType[10];
    char  accountNbr[10];
    char amount[256];
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// Authentification user
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);
int getID();
int IntVerify(char s[]);
int StrVerify(char s[]);
bool CheckSaving(char str[]);
bool CheckDate(struct Record r);
bool CheckYear(int year);
void Modify(struct User u,struct Record cr, int choice);
void CheckAccount(struct User u);


// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void UpdateAccount();
