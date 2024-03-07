#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 25
#define MAX_ID_LENGTH 5
#define MAX_DESC_LENGTH 50

struct Patient {
    char name[MAX_NAME_LENGTH];
    char id[MAX_ID_LENGTH];
    int age;
    char description[MAX_DESC_LENGTH];
    char code[10];
    struct Patient* next;
};

struct PriorityQueue {
    struct Patient* front;
};

void initializeQueue(struct PriorityQueue* pq);
void insertPatient(struct PriorityQueue* pq);
void viewList(struct PriorityQueue* pq);
void nextQueue(struct PriorityQueue* pq);
bool validateID(struct PriorityQueue* pq, char id[]);
bool validateCode(char code[]);
bool validateName(char name[]);
bool validateAge(int age);
bool validateDescription(char desc[]);

struct Patient* lastDisplayedPatient = NULL;

int main() {
    struct PriorityQueue pq;
    initializeQueue(&pq);

    lastDisplayedPatient = NULL;

    int choice;
    while (1) {
        printf("Sunib Patient Entry\n");
        printf("===================\n");
        printf("Menu:\n");
        printf("1. Insert Patient\n");
        printf("2. View List\n");
        printf("3. Next Queue\n");
        printf("4. Exit\n");
        printf(">>> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertPatient(&pq);
                break;
            case 2:
                viewList(&pq);
                break;
            case 3:
                nextQueue(&pq);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                printf("\n");
        }
    }

    return 0;
}

void initializeQueue(struct PriorityQueue* pq) {
    pq->front = NULL;
}

void insertPatient(struct PriorityQueue* pq) {
    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    if (newPatient == NULL) {
        printf("Memory allocation failed. Unable to insert patient.\n");
        return;
    }

    printf("Input patient name [4-25]: ");
    scanf(" %[^\n]", newPatient->name);
    while (!validateName(newPatient->name)) {
        printf("Input patient name [4-25]: ");
        scanf(" %[^\n]", newPatient->name);
    }

    printf("Input patient age [>= 0]: ");
    scanf("%d", &newPatient->age);
    while (!validateAge(newPatient->age)) {
        printf("Input patient age [>= 0]: ");
        scanf("%d", &newPatient->age);
    }

    printf("Input patient ID [5]: ");
    scanf("%s", newPatient->id);
    while (!validateID(pq, newPatient->id)) {
        printf("Input patient ID [5]: ");
        scanf("%s", newPatient->id);
    }

    printf("Input patient description [>= 6 characters]: ");
    scanf(" %[^\n]", newPatient->description);
    while (!validateDescription(newPatient->description)) {
        printf("Input patient description [>= 6 characters]: ");
        scanf("%s", newPatient->description);
    }

    printf("Input patient code [Red | Yellow | Green]: ");
    scanf("%s", newPatient->code);
    while (!validateCode(newPatient->code)) {
        printf("Input patient code [Red | Yellow | Green]: ");
        scanf("%s", newPatient->code);
    }

    newPatient->next = pq->front;
    pq->front = newPatient;

    printf("Insert success!\n");
    printf("\n");
}

bool validateID(struct PriorityQueue* pq, char id[]) {
    struct Patient* temp = pq->front;
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0)
            return false;
        temp = temp->next;
    }
    return (strlen(id) == MAX_ID_LENGTH);
}

bool validateCode(char code[]) {
    return (strcmp(code, "Red") == 0 || strcmp(code, "Yellow") == 0 || strcmp(code, "Green") == 0);
}

bool validateName(char name[]) {
    int len = strlen(name);
    return (len >= 4 && len <= MAX_NAME_LENGTH);
}

bool validateAge(int age) {
    return (age >= 0);
}

bool validateDescription(char desc[]) {
    return (strlen(desc) >= 6);
}

void viewList(struct PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("There is no queue yet!\n");
        printf("\n");
        return;
    }

    struct Patient* temp = pq->front;
    int count = 1;

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("| No | Name                | ID        | Age   | Description                                  | Code    |\n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    while (temp != NULL) {
        if (strcmp(temp->code, "Red") == 0) {
            printf("| %d  | %-16s    | %-5s     | %-4d  | %-36s         | %-6s  |\n", count++, temp->name, temp->id, temp->age, temp->description, temp->code);
            printf("---------------------------------------------------------------------------------------------------------\n");
        }
        temp = temp->next;
    }

    temp = pq->front;
    while (temp != NULL) {
        if (strcmp(temp->code, "Yellow") == 0 && strcmp(temp->code, "Red") != 0) {
            printf("| %d  | %-16s    | %-5s     | %-4d  | %-36s         | %-6s  |\n", count++, temp->name, temp->id, temp->age, temp->description, temp->code);
            printf("---------------------------------------------------------------------------------------------------------\n");
        }
        temp = temp->next;
    }

    temp = pq->front;
    while (temp != NULL) {
        if (strcmp(temp->code, "Green") == 0 && strcmp(temp->code, "Red") != 0 && strcmp(temp->code, "Yellow") != 0) {
            printf("| %d  | %-16s    | %-5s     | %-4d  | %-36s         | %-6s  |\n", count++, temp->name, temp->id, temp->age, temp->description, temp->code);
            printf("---------------------------------------------------------------------------------------------------------\n");
        }
        temp = temp->next;
    }
}

void nextQueue(struct PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("There is no queue yet!\n");
        printf("\n");
        return;
    }

    struct Patient* temp = (lastDisplayedPatient == NULL) ? pq->front : lastDisplayedPatient->next;
    struct Patient* prev = NULL;
    struct Patient* nextPatient = NULL;
    int highestPriority = 0;

    while (temp != NULL) {
        int priority;
        if (strcmp(temp->code, "Red") == 0)
            priority = 3;
        else if (strcmp(temp->code, "Yellow") == 0)
            priority = 2;
        else
            priority = 1;

        if (priority > highestPriority) {
            highestPriority = priority;
            nextPatient = temp;
        }

        prev = temp;
        temp = temp->next;
    }

    if (nextPatient == NULL) {
        printf("No more patients in the queue.\n");
        printf("\n");
        lastDisplayedPatient = NULL;
        return;
    }

    printf("\n\nThe next patient is:\n");
    printf("Name        : %s\nAge         : %d\nID          : %s\nDescription : %s\nCode        : %s\n", nextPatient->name, nextPatient->age, nextPatient->id, nextPatient->description, nextPatient->code);

    lastDisplayedPatient = nextPatient;

    if (prev == NULL)
        pq->front = nextPatient->next;
    else
        prev->next = nextPatient->next;
}