#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct Node{
	char nama_obat[101];
	struct Node *next;
}Node;

Node *head = NULL;

void push(char input[]){ 
	Node *node_baru = (Node*)malloc(sizeof(Node));
	strcpy(node_baru->nama_obat, input);
	node_baru->next = head;
	head = node_baru;
}

void tampil(){
	int count = 1;
	if(head == NULL){
		printf("Stack is empty\n");
		return;
	}
	Node *temp = head;
	while (temp != NULL){
		printf("Take Medicine #%d : %s\n", count, temp->nama_obat);
		temp = temp->next;
		count++;
	}
}

int compare_insensitive_case(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower(*s1) != tolower(*s2))
            return 0;
        s1++;
        s2++;
    }
    return (*s1 == '\0' && *s2 == '\0');
}

int main(){
	printf("Sunib Hospital\n");
	printf("==============\n\n\n");
	char input[101];
	int hitung_obat = 0;
	
	while (1){
		printf("Enter the medicine name [minimum 5 medicines] ('done' to finish): ");
        scanf(" %[^\n]", input);
        
        if (strcmp(input, "done") == 0) {
            printf("\n");
            break;
        }
        
        printf("Medicine %s added to the prescription.\n", input);
        push(input); 
        hitung_obat++;
	}
		
	if (hitung_obat < 5) {
        printf("Prescription should have at least 5 medicines. Exiting...\n");
        return 1;
    }
    
    printf("Medicine Prescription:\n");
    tampil();
    char pilihan[10];
    printf("Do you want to continue? (yes/no): ");
    scanf(" %[^\n]", pilihan);

    if (compare_insensitive_case(pilihan, "yes")) {
        main();
    } else if (compare_insensitive_case(pilihan, "no")) {
        printf("Exiting program...\n");
    } else {
        printf("Invalid input. Exiting program...\n");
    }
    return 0;
}
