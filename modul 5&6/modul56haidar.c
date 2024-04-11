#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

long long phoneToRemove;

struct Node {
    long long phone;
    int visits;
    char name[30];
    char email[30];
    struct Node *right;
    struct Node *left;
};

struct Node *root = NULL;

struct Node *newNode(long long phone, const char *name, const char *email, int visits) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->phone = phone;
    strcpy(temp->name, name);
    strcpy(temp->email, email);
    temp->visits = visits;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node *insert(struct Node *node, long long phone, const char *name, const char *email, int visits) {
    if (node == NULL) {
        return newNode(phone, name, email, visits);
    }
    if (phone < node->phone) {
        node->left = insert(node->left, phone, name, email, visits);
    }
    else if (phone > node->phone) {
        node->right = insert(node->right, phone, name, email, visits);
    }
    return node;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        if (root->phone != phoneToRemove) {
            printf("| %-10s\t| 0%-lld\t| %-27s\t| %-6d |\n", root->name, root->phone, root->email, root->visits-1);
        }
        inorder(root->right);
    }
}

bool validateEmail(const char *email) {
    if (strlen(email) < 10 || strlen(email) > 30) {
        return false;
    }

    const char *domain = strstr(email, "@");
    if (domain == NULL) {
        return false;
    }

    if (strcmp(domain, "@gmail.com") != 0 && strcmp(domain, "@gmail.co.id") != 0) {
        return false;
    }

    return true;
}

void processOrder() {
    long long phone;
    int option;
    char name[30], email[30];
    bool isMember = false;
    char medicine[5][30];
    int quantityArr[5];
    int priceArr[5];
    int total = 0;
    int numMedicine = 0;

    printf("Input phone number [10-13] [numeric]: ");
    scanf("%lld", &phone);

    struct Node *ptr = root;
    while (ptr != NULL) {
        if (ptr->phone == phone) {
            isMember = true;
            break;
        }
        else if (phone < ptr->phone) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }

    if (!isMember) {
        char choice;

        printf("Do you want to join membership? [y/n]: ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            printf("Input name [5-25] [Mr. | Mrs. ]: ");
            scanf(" %[^\n]", name);

            bool validEmail;
            do {
                validEmail = true;
                printf("Input email [10-30] [email format]: ");
                scanf(" %[^\n]", email);

                if (!validateEmail(email)) {
                    printf("Input Email Correctly!\n");
                    validEmail = false;
                }
            } while (!validEmail);

            root = insert(root, phone, name, email, 1);
            printf("Insert success!\n");
        }
        else {
            printf("---------------------------------\n");
            printf("| No.\t| Nama Obat\t| Harga\t|\n");
            printf("---------------------------------\n");
            printf("| 1.\t| Paracetamol\t| 5000\t|\n");
            printf("| 2.\t| Diapet\t| 7000\t|\n");
            printf("| 3.\t| Oralit\t| 3500\t|\n");
            printf("| 4.\t| Paratusin\t| 5500\t|\n");
            printf("| 5.\t| OB Herbal\t| 6000\t|\n");
            printf("---------------------------------\n");

            char answer;
            int price = 0;
            int quantity;

            do {
                printf("Input medicine [1-5]: ");
                scanf("%d", &option);

                if (option < 1 || option > 5) {
                    printf("Invalid medicine number!\n");
                    continue;
                }

                printf("Input quantity [>=1]: ");
                scanf("%d", &quantity);
                if (quantity < 1) {
                    printf("Invalid quantity!\n");
                    continue;
                }

                switch (option) {
                    case 1:
                        price = 5000;
                        strcpy(medicine[numMedicine], "Paracetamol");
                        break;
                    case 2:
                        price = 7000;
                        strcpy(medicine[numMedicine], "Diapet");
                        break;
                    case 3:
                        price = 3500;
                        strcpy(medicine[numMedicine], "Oralit");
                        break;
                    case 4:
                        price = 5500;
                        strcpy(medicine[numMedicine], "Paratusin");
                        break;
                    case 5:
                        price = 6000;
                        strcpy(medicine[numMedicine], "OB Herbal");
                        break;
                    default:
                        printf("Invalid medicine number!\n");
                        continue;
                }

                quantityArr[numMedicine] = quantity;
                priceArr[numMedicine] = price;
                total += price * quantity;
               
                       numMedicine++;

                printf("Do you want to buy other medicine? [y/n]: ");
                scanf(" %c", &answer);
            } while (answer == 'y' || answer == 'Y');

            printf("\nOrder summary:\n");
            for (int i = 0; i < numMedicine; i++) {
                printf("%s\t\t\t\t- %dx = %d\n", medicine[i], quantityArr[i], priceArr[i] * quantityArr[i]);
            }
            printf("Total: %d\n", total);
        }
    }
    else {
        ptr->visits++;
        
        printf("Number of visits: %d\n", ptr->visits - 1);
        printf("---------------------------------\n");
        printf("| No.\t| Nama Obat\t| Harga\t|\n");
        printf("---------------------------------\n");
        printf("| 1.\t| Paracetamol\t| 5000\t|\n");
        printf("| 2.\t| Diapet\t| 7000\t|\n");
        printf("| 3.\t| Oralit\t| 3500\t|\n");
        printf("| 4.\t| Paratusin\t| 5500\t|\n");
        printf("| 5.\t| OB Herbal\t| 6000\t|\n");
        printf("---------------------------------\n");

        char answer;
        int price = 0;
        int quantity;
        int numMedicine = 0;

        do {
            printf("Input medicine [1-5]: ");
            scanf("%d", &option);

            if (option < 1 || option > 5) {
                printf("Invalid medicine number!\n");
                continue;
            }

            printf("Input quantity [>=1]: ");
            scanf("%d", &quantity);
            if (quantity < 1) {
                printf("Invalid quantity!\n");
                continue;
            }

            switch (option) {
                case 1:
                    price = 5000;
                    strcpy(medicine[numMedicine], "Paracetamol");
                    break;
                case 2:
                    price = 7000;
                    strcpy(medicine[numMedicine], "Diapet");
                    break;
                case 3:
                    price = 3500;
                    strcpy(medicine[numMedicine], "Oralit");
                    break;
                case 4:
                    price = 5500;
                    strcpy(medicine[numMedicine], "Paratusin");
                    break;
                case 5:
                    price = 6000;
                    strcpy(medicine[numMedicine], "OB Herbal");
                    break;
                default:
                    printf("Invalid medicine number!\n");
                    continue;
            }

            quantityArr[numMedicine] = quantity;
            priceArr[numMedicine] = price;
            total += price * quantity;
            numMedicine++;

            printf("Do you want to buy other medicine? [y/n]: ");
            scanf(" %c", &answer);
        } while (answer == 'y' || answer == 'Y');

        printf("\nOrder summary:\n");
        for (int i = 0; i < numMedicine; i++) {
            printf("%s\t\t\t\t- %dx = %d\n", medicine[i], quantityArr[i], priceArr[i] * quantityArr[i]);
        }
        printf("Total: %d\n", total);
    }
}

void viewAllCustomer(struct Node *root) {
    if (root == NULL) {
        printf("There is no data!\n");
        getchar();
        return;
    }
    printf("--------------------------------------------------------------------------\n");
    printf("| Name\t\t| Phone\t\t| Email\t\t\t\t| Visits |\n");
    printf("--------------------------------------------------------------------------\n");
    inorder(root);
    printf("--------------------------------------------------------------------------\n");
}

struct Node *findMinimum(struct Node *node) {
    struct Node *current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct Node *deleteNode(struct Node *root, int phone) {
    if (root == NULL) {
        printf("Data invalid!\n");
        return root;
    }
    if (phone < root->phone) {
        root->left = deleteNode(root->left, phone);
    }
    else if (phone > root->phone) {
        root->right = deleteNode(root->right, phone);
    }
    else {
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = findMinimum(root->right);
        root->phone = temp->phone;
        root->right = deleteNode(root->right, temp->phone);
    }
    return root;
}

void Remove(struct Node **cek, long long nomer)
{
    if ((*cek) == NULL)
    {
        printf("Phone not found\n");
    }
    else if (nomer < (*cek)->phone)
    {
        Remove(&((*cek)->left), nomer);
    }
    else if (nomer > (*cek)->phone)
    {
        Remove(&((*cek)->right), nomer);
    }
    else
    {
        struct Node *temp;
        if ((*cek)->left == NULL)
        {
            temp = (*cek)->right;
            free(*cek);
            *cek = temp;
        }
        else if ((*cek)->right == NULL)
        {
            temp = (*cek)->left;
            free(*cek);
            *cek = temp;
        }
        else
        {
            temp = findMinimum((*cek)->right);
            (*cek)->phone = temp->phone;
            Remove(&((*cek)->right), temp->phone);
        }
    }
}

int main() {
    int choice;

    do {
        printf("\nSUNIB's Pharmacy\n");
        printf("=====================\n");
        printf("1. Process Order\n");
        printf("2. View All Customer\n");
        printf("3. Remove Customer\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                processOrder();
                break;
            case 2:
                viewAllCustomer(root);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 3:
                printf("Input phone number [10-13] [numeric]: ");
                scanf("%lld", &phoneToRemove);

                if (root == NULL) {
                    printf("No customer data found!\n");
                    break;
                }

                Remove(&root, phoneToRemove);
                printf("Customer with phone number 0%lld has been successfully removed.\n", phoneToRemove);
                break;
            case 4:
                printf("Thanks for using this program!\n");
                break;
            default:
                printf("Invalid input!\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
