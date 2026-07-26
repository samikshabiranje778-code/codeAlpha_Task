// Task : BANK MANAGEMENT SYSTEM
#include <stdio.h>
#include <stdlib.h>

struct Account {
    long long accNo;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;

    while (1) {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}

void createAccount() {
    FILE *fp = fopen("bank.dat", "ab");
    struct Account a;

    printf("Enter Account Number: ");
   scanf("%lld", &a.accNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Account Created Successfully.\n");
}

void deposit() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct Account a;
    int acc;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%lld", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);

            a.balance += amount;

            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("Deposit Successful.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found.\n");

    fclose(fp);
}

void withdraw() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct Account a;
    int acc;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%lld", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("Enter Withdraw Amount: ");
            scanf("%f", &amount);

            if (amount <= a.balance) {
                a.balance -= amount;

                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);

                printf("Withdrawal Successful.\n");
            } else {
                printf("Insufficient Balance.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found.\n");

    fclose(fp);
}

void balanceEnquiry() {
    FILE *fp = fopen("bank.dat", "rb");
    struct Account a;
    int acc;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%lld", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == acc) {
            printf("\nAccount Number : %d\n", a.accNo);
            printf("Name           : %s\n", a.name);
            printf("Balance        : %.2f\n", a.balance);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found.\n");

    fclose(fp);
}
