#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define ACCOUNT_DETAILS "accounts.csv"

typedef struct {
    int accountNo, balance, pin;
    char name[20], branch[20];
} Account;

// Prototypes
void options();
int readAccountsFromFile(Account accounts[]);
void writeAccountsToFile(Account accounts[], int count);
int findAccountIndex(Account accounts[], int count, int accountNo, int pin);
void deposit();
void transferFunds();

void options(){
    printf("1. Create account\n");
    printf("2. Check balance\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. Transfer funds\n");
    printf("6. Exit\n");
}

void storeAccountDetails(Account newAccount) {
    FILE *file = fopen(ACCOUNT_DETAILS, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%d,%d\n", newAccount.accountNo, newAccount.name, newAccount.branch, newAccount.pin, newAccount.balance);
    fclose(file);
}

int readAccountsFromFile(Account accounts[]) {
    FILE *file = fopen(ACCOUNT_DETAILS, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    int i = 0;
    while(fscanf(file, "%d,%[^,],%[^,],%d,%d\n", &accounts[i].accountNo, accounts[i].name, accounts[i].branch, &accounts[i].pin, &accounts[i].balance) == 5) {
        i++;
        if (i >= MAX_ACCOUNTS) break;
    }
    fclose(file);
    return i; // Return the number of accounts read
}

void writeAccountsToFile(Account accounts[], int count) {
    FILE *file = fopen(ACCOUNT_DETAILS, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%d,%d\n", accounts[i].accountNo, accounts[i].name, accounts[i].branch, accounts[i].pin, accounts[i].balance);
    }
    fclose(file);
}

int findAccountIndex(Account accounts[], int count, int accountNo, int pin) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].accountNo == accountNo && accounts[i].pin == pin) {
            return i; // Account found
        }
    }
    return -1; // Account not found
}

void createaccount(){
Account newAccount;
                printf("Create account\n");
  printf("Enter your name: ");
  scanf("%s", newAccount.name);
  printf("Enter Account number: ");
  scanf("%d", &newAccount.accountNo);
  printf("Enter Branch name: ");
  scanf("%s", newAccount.branch);
  printf("Create your PIN: ");
  scanf("%d", &newAccount.pin);
  printf("Enter initial balance: ");
  scanf("%d", &newAccount.balance);
  storeAccountDetails(newAccount);  
  printf("Account created succesfully\n");           
}

void checkBalance() {
    Account accounts[MAX_ACCOUNTS];
    int count = readAccountsFromFile(accounts);
    int accountNo, pin, index;

    printf("Check balance\n");
    printf("Enter your account number: ");
    scanf("%d", &accountNo);
    printf("Enter your PIN: ");
    scanf("%d", &pin);

    index = findAccountIndex(accounts, count, accountNo, pin);
    if (index != -1) {
        printf("Your balance is: %d\n", accounts[index].balance);
    } else {
        printf("Account not found or incorrect PIN.\n");
    }
}

void deposit() {
    Account accounts[MAX_ACCOUNTS];
    int count = readAccountsFromFile(accounts);
    int accountNo, pin, amount, index;

    printf("Deposit\n");
    printf("Enter your account number: ");
    scanf("%d", &accountNo);
    printf("Enter your PIN: ");
    scanf("%d", &pin);
    printf("Enter amount to deposit: ");
    scanf("%d", &amount);

    index = findAccountIndex(accounts, count, accountNo, pin);
    if (index != -1) {
        accounts[index].balance += amount;
        printf("Deposit successful. New balance: %d\n", accounts[index].balance);
        writeAccountsToFile(accounts, count);
    } else {
        printf("Account not found or incorrect PIN.\n");
    }
}

void withdraw() {
    Account accounts[MAX_ACCOUNTS];
    int count = readAccountsFromFile(accounts);
    int accountNo, pin, amount, index;

    printf("Withdraw\n");
    printf("Enter your account number: ");
    scanf("%d", &accountNo);
    printf("Enter your PIN: ");
    scanf("%d", &pin);
    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);

    index = findAccountIndex(accounts, count, accountNo, pin);
    if (index != -1) {
        if(accounts[index].balance >= amount) {
            accounts[index].balance -= amount;
            printf("Withdrawal successful. New balance: %d\n", accounts[index].balance);
            writeAccountsToFile(accounts, count);
        } else {
            printf("Insufficient funds.\n");
        }
    } else {
        printf("Account not found or incorrect PIN.\n");
    }
}

void transferFunds() {
    Account accounts[MAX_ACCOUNTS];
    int count = readAccountsFromFile(accounts);
    int senderAccountNo, receiverAccountNo, pin, amount, senderIndex, receiverIndex;

    printf("Transfer funds\n");
    printf("Enter your account number: ");
    scanf("%d", &senderAccountNo);
    printf("Enter your PIN: ");
    scanf("%d", &pin);
    printf("Enter receiver's account number: ");
    scanf("%d", &receiverAccountNo);
    printf("Enter amount to transfer: ");
    scanf("%d", &amount);

    senderIndex = findAccountIndex(accounts, count, senderAccountNo, pin);
    receiverIndex = findAccountIndex(accounts, count, receiverAccountNo, -1); // No pin required for receiver

    if (senderIndex != -1 && receiverIndex != -1) {
        if (accounts[senderIndex].balance >= amount) {
            accounts[senderIndex].balance -= amount;
            accounts[receiverIndex].balance += amount;
            printf("Transfer successful.\n");
            writeAccountsToFile(accounts, count);
        } else {
            printf("Insufficient funds.\n");
        }
    } else {
        printf("Sender or receiver account not found or incorrect PIN.\n");
    }
}

int main(void) {
     printf("\nWELCOME TO HUDUMA BANK\n");
    int choice;
    do {
       
        printf("\nPlease choose an option:\n");
        options();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createaccount();
                break;
        
            case 2:
                checkBalance();
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                transferFunds();
                break;
            case 6:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
