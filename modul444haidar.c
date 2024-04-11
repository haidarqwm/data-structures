#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

#define TABLE_SIZE 1007

struct obat{
    char medid[50];
    char nama[26];
    char manufac[200];
    char regid[11];
    int batchnum;
    struct obat *next;
};

struct obat *head = NULL; 
struct obat *hash_table[TABLE_SIZE] = {NULL};
unsigned int hash_function(char* medid);
void insert();
void view();
void remove_obat(char* medid);

unsigned int hash_function(char *medid) {
    unsigned int sum = 0;
    while (*medid) {
        sum += *medid;
        medid++;
    }
    return sum % TABLE_SIZE;
}

void insert() {
    struct obat *newobat;
    struct obat *current;
    int unique = 1;

    do {
        newobat = (struct obat*)malloc(sizeof(struct obat));
        printf("Input Medicine Name[5-50][Unique]: ");
        scanf(" %[^\n]", newobat->nama);

        if (strlen(newobat->nama) < 5 || strlen(newobat->nama) > 50) {
            free(newobat);
        }

        struct obat *current = head;
        while (current != NULL) {
            if (strcmp(current->nama, newobat->nama) == 0) {
                break;
            }
            current = current->next;
        }

        if (current == NULL && strlen(newobat->nama) >= 5 && strlen(newobat->nama) <= 50) {
            break;
        }
    } while (1);

    do {
        printf("Input Manufacturer Name[3-25][end with Ltd.]: ");
        scanf(" %[^\n]", newobat->manufac);

        if (strlen(newobat->manufac) < 3 || strlen(newobat->manufac) > 25 || strcmp(newobat->manufac + strlen(newobat->manufac) - 4, "Ltd.") != 0) {
        }
    
    } while (strlen(newobat->manufac) < 3 || strlen(newobat->manufac) > 25 || strcmp(newobat->manufac + strlen(newobat->manufac) - 4, "Ltd.") != 0);

    int panjang;

    do {
        printf("Input Registration No.[10 digits][numeric]: ");
        scanf("%s", newobat->regid);

        int length = strlen(newobat->regid);
        if (length != 10) {
            continue;
        }
        
        int i;
        for (i = 0; i < length; i++) {
            if (newobat->regid[i] < '0' || newobat->regid[i] > '9') {
                break;
            }
        }
        	
        if (i == length) {
            break;
        }
    } while (1);

    do {
        printf("Input Batch/Lot[>=16]: ");
        if (scanf("%d", &newobat->batchnum) != 1) {
            while (getchar() != '\n');
        } else {
            if (newobat->batchnum >= 16) {
                break;
            } else {
                while(getchar() != '\n');
            }
        }
    } while (1);

    static int counter = 1;

    sprintf(newobat->medid, "M%05d-%s-%c%c", counter, newobat->regid, toupper(newobat->manufac[0]), toupper(newobat->nama[0]));
    printf("Medicine ID: %s\n", newobat->medid);

    counter++;

    int key = hash_function(newobat->medid);

    newobat->next = hash_table[key];
    hash_table[key] = newobat;

    printf("Index: %d\n", key);

    newobat->next = head;
    head = newobat;

    printf("Insert Success!\n");
    printf("Press any key to continue. . . ");
    getch();
    system("cls");
}

void view() {
    if (head == NULL) {
        printf("There is no data yet!\n");
        printf("Press any key to continue. . . ");
        getch();

        system("cls");
        return;
    }

    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| Medicine ID\t\t| Medicine Name\t\t\t\t| Manufacturer\t\t| Registration No.\t| Batch Number\t|\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");

    struct obat *current = head;
    int counter = 1;

    while (current != NULL) {
        printf("| %s\t| %-30s\t| %-20s\t| %-16s\t| %-13d\t|\n", current->medid, current->nama, current->manufac, current->regid, current->batchnum);
        printf("---------------------------------------------------------------------------------------------------------------------------------\n");
        counter++;
        current = current->next;
    }

    printf("Press any key to continue. . . ");
    getch();
    system("cls");
}

void remove_obat(char* medid) {
    int key = hash_function(medid);

    struct obat* current = head;
    struct obat* prev = NULL;

    while (current != NULL && strcmp(current->medid, medid) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Medicine with ID %s not found.\n", medid);
        printf("Press any key to continue . . . ");
        getch();
        system("cls");
        return;

    }

    printf("Medicine Information:\n");
    printf("Medicine ID: %s\n", current->medid);
    printf("Medicine Name: %s\n", current->nama);
    printf("Manufacturer: %s\n", current->manufac);
    printf("Registration No.: %s\n", current->regid);
    printf("Batch Number: %d\n", current->batchnum);

    printf("Do you want to remove this medicine? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        struct obat* hash_current = hash_table[key];
        struct obat* hash_prev = NULL;

        while (hash_current != NULL && strcmp(hash_current->medid, medid) != 0) {
            hash_prev = hash_current;
            hash_current = hash_current->next;
        }

        if (hash_prev == NULL) {
            hash_table[key] = hash_current->next;
        } else {
            hash_prev->next = hash_current->next;
        }

        free(current);

        printf("Medicine with ID %s removed successfully.\n", medid);
        printf("Press any key to continue . . . ");
        getch();
        system("cls");
    } else {
        printf("Removal canceled.\n");
    }
}

int main() {
    int pilih;

    do {
        printf("Sunib Hospital\n");
        printf("==============\n");
        printf("[1] View Medicine\n");
        printf("[2] Insert Medicine\n");
        printf("[3] Remove Medicine\n");
        printf("[4] Exit\n");
        printf(">>> ");
        scanf("%d", &pilih);
        system("cls");
        switch (pilih) {
            case 1:
                view();
                break;
            case 2:
                insert();
                break;
            case 3:
                printf("Enter Medicine ID to remove: ");
                char medid_to_remove[50];
                scanf(" %s", medid_to_remove);
                remove_obat(medid_to_remove);
                break;
            case 4:
                while (head != NULL) {
                    struct obat *temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (1);

    return 0;
}