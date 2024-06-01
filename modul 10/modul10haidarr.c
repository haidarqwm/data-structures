#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

int heap[MAX_SIZE];
int size = 0;

void insert(int data) {
    if (size >= MAX_SIZE) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    heap[size] = data;
    int current = size;
    int parent = (current - 1) / 2;

    while (current > 0 && heap[current] > heap[parent]) {
        int temp = heap[current];
        heap[current] = heap[parent];
        heap[parent] = temp;

        current = parent;
        parent = (current - 1) / 2;
    }

    size++;
    printf("Insert Success.\n");
}

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void printLevel(int level, int maxLevel) {
    int nodesInLevel = pow(2, level);
    int maxNodes = pow(2, maxLevel);
    int leadingSpaces = (maxNodes / nodesInLevel - 1) * 2;
    int inBetweenSpaces = (maxNodes / nodesInLevel - 1) * 4 - 2;

    if (level == maxLevel - 3) {
        leadingSpaces += 1;
        inBetweenSpaces += 1;
    } else if (level == maxLevel - 2) {
        leadingSpaces += 2;
        inBetweenSpaces += 2;
    } else if (level == maxLevel - 1) {
        leadingSpaces += 3;
        inBetweenSpaces += 3;
    } else if (level <= 2) {
        leadingSpaces -= 2;
    }

    printSpaces(leadingSpaces);

    int start = pow(2, level) - 1;
    int end = start + nodesInLevel;

    for (int i = start; i < end; i++) {
        if (i < size) {
            printf("%2d", heap[i]);
        } else {
            printf("NL");
        }
        if (i < end - 1) {
            printSpaces(inBetweenSpaces);
        }
    }

    printf("\n");
}

void view() {
    if (size == 0) {
        printf("Heap is empty.\n");
        for (int level = 0; level < 5; level++) {
            printLevel(level, 5);
        }
        return;
    }

    printf("Only 5 levels shown\n");

    int maxLevel = 5;

    for (int level = 0; level < maxLevel; level++) {
        printLevel(level, maxLevel);
    }
}

void pop() {
    if (size == 0) {
        printf("There is no data.\n");
        return;
    }

    int root = heap[0];
    heap[0] = heap[size - 1];
    size--;

    int current = 0;
    int leftChild = 2 * current + 1;
    int rightChild = 2 * current + 2;

    while ((leftChild < size && heap[current] < heap[leftChild]) ||
           (rightChild < size && heap[current] < heap[rightChild])) {
        int maxChild = (rightChild < size && heap[rightChild] > heap[leftChild]) ? rightChild : leftChild;

        int temp = heap[current];
        heap[current] = heap[maxChild];
        heap[maxChild] = temp;

        current = maxChild;
        leftChild = 2 * current + 1;
        rightChild = 2 * current + 2;
    }

    printf("Deleted root element: %d\n", root);
    printf("Delete success.\n");
}

void deleteHeap() {
    size = 0;
}

int main() {
    int choice, data;

    while (1) {
        printf("\nMAX HEAP TREE\n");
        printf("=============\n");
        printf("1. Insert\n");
        printf("2. View\n");
        printf("3. Pop\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number (1-100): ");
                scanf("%d", &data);
                if (data < 1 || data > 100) {
                    printf("Invalid input. Number must be between 1 and 100.\n");
                } else {
                    insert(data);
                }
                break;
            case 2:
                view();
                break;
            case 3:
                pop();
                break;
            case 4:
                deleteHeap();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}