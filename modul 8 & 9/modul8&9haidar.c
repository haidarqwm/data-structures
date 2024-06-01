#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



struct Game {
    char title[26];
    char genre[20];
    int stock;
    struct Game *left;
    struct Game *right;
    int height;
};


int height(struct Game *N) {
    if (N == NULL)
        return 0;
    return N->height;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}


struct Game *newGame(char title[], char genre[], int stock) {
    struct Game *game = (struct Game *)malloc(sizeof(struct Game));
    strcpy(game->title, title);
    strcpy(game->genre, genre);
    game->stock = stock;
    game->left = NULL;
    game->right = NULL;
    game->height = 1; \
    return (game);
}


struct Game *rightRotate(struct Game *y) {
    struct Game *x = y->left;
    struct Game *T2 = x->right;


    x->right = y;
    y->left = T2;


    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;


    return x;
}


struct Game *leftRotate(struct Game *x) {
    struct Game *y = x->right;
    struct Game *T2 = y->left;


    y->left = x;
    x->right = T2;


    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;


    return y;
}


int getBalance(struct Game *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


struct Game *insertGame(struct Game *node, char title[], char genre[], int stock) {

    if (node == NULL)
        return (newGame(title, genre, stock));

    if (strcmp(title, node->title) < 0)
        node->left = insertGame(node->left, title, genre, stock);
    else if (strcmp(title, node->title) > 0)
        node->right = insertGame(node->right, title, genre, stock);
    else
        return node;

   
    node->height = 1 + max(height(node->left), height(node->right));

   
    int balance = getBalance(node);

   

   //ll
    if (balance > 1 && strcmp(title, node->left->title) < 0)
        return rightRotate(node);

    //rr
    if (balance < -1 && strcmp(title, node->right->title) > 0)
        return leftRotate(node);

    //lr
    if (balance > 1 && strcmp(title, node->left->title) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //rl
    if (balance < -1 && strcmp(title, node->right->title) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

   
    
    return node;
}


void inOrder(struct Game *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("| %-24s | %-12s | %-10d |\n", root->title, root->genre, root->stock);
        printf("--------------------------------------------------------\n");
        inOrder(root->right);
    }
}


struct Game *searchGame(struct Game *root, char title[]) {
    if (root == NULL || strcmp(root->title, title) == 0)
        return root;

    if (strcmp(root->title, title) < 0)
        return searchGame(root->right, title);

    return searchGame(root->left, title);
}


struct Game *minValueNode(struct Game *node) {
    struct Game *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}



struct Game *deleteAllGamesWithTitle(struct Game *root, char title[]) {
    if (root == NULL)
        return root;

    if (strcmp(root->title, title) < 0)
        root->left = deleteAllGamesWithTitle(root->left, title);
    else if (strcmp(root->title, title) > 0)
        root->right = deleteAllGamesWithTitle(root->right, title);
    else {
        root->left = deleteAllGamesWithTitle(root->left, title);
        root->right = deleteAllGamesWithTitle(root->right, title);
        free(root);
        root = NULL;
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);



    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


struct Game *deleteGame(struct Game *root, char title[], char genre[]) {
    if (root == NULL)
        return root;

    
    if (strcmp(title, root->title) < 0)
        root->left = deleteGame(root->left, title, genre);
    
    else if (strcmp(title, root->title) > 0)
        root->right = deleteGame(root->right, title, genre);
    
    else {
        
        if (strcmp(genre, root->genre) != 0)
            root = deleteAllGamesWithTitle(root, title);
        
        else {
            
            if (root->left == NULL) {
                struct Game *temp = root->right;
                free(root);
                return temp;
            } else if (root->right == NULL) {
                struct Game *temp = root->left;
                free(root);
                return temp;
            }

          
            struct Game *temp = minValueNode(root->right);

  
            strcpy(root->title, temp->title);
            strcpy(root->genre, temp->genre);
            root->stock = temp->stock;

         
            root->right = deleteGame(root->right, temp->title, temp->genre);
        }
    }

   
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

  

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}






// Function to update stock
void updateStock(struct Game *root, char title[], char updateType[]) {
    struct Game *game = searchGame(root, title);
    int quantity;
    if (game == NULL) {
        printf("Data not found!\n");
        return;
    }

    if (strcmp(updateType, "add") == 0) {
    	printf("Enter quantity: ");
    	scanf("%d", &quantity);
    	while(quantity < 1){
    		printf("Enter quantity: ");
    		scanf("%d", &quantity);
		}
        game->stock += quantity;
        printf("Data updated successfully!\n");
        
    } else if (strcmp(updateType, "remove") == 0) {
    	
    	printf("Enter quantity[1-%d]: ", game->stock);
        scanf("%d", &quantity);
        while(quantity < 0 || quantity > game->stock){
        	printf("Enter quantity[1-%d]: ", game->stock);
        	scanf("%d", &quantity);
		}
        if (quantity <= game->stock) {
            game->stock -= quantity;
            if (game->stock == 0) {
            	printf("Data updated successfully!\n");
            	printf("%s is removed from the warehouse !\n", game->title);
                root = deleteGame(root, game->title, game->genre);
            } else {
                printf("Data updated successfully!\n");
            }
        } else {
            printf("Invalid quantity for removal!\n");
        }
    } else {
        printf("Invalid update type!\n");
    }
}

int main() {
    struct Game *root = NULL;
    int choice;
    char title[26], genre[20], updateType[10];
    int stock, quantity;

    do {
    	system("cls");
        printf("Bluejack GShop\n");
        printf("==============\n");
        printf("1. Insert Game\n");
        printf("2. View Game\n");
        printf("3. Update Stock\n");
        printf("4. Exit\n");
        printf(">> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
    			system("cls");
    			do {
        			printf("Enter Game Title[5-25][unique]: ");
        			scanf(" %[^\n]", title);
        			while (strlen(title) < 5 || strlen(title) > 25) {
            			printf("Enter Game Title[5-25][unique]: ");
            			scanf(" %[^\n]", title);
        			}

      
        			struct Game *existingGame = searchGame(root, title);
        			if (existingGame != NULL) {
            			printf("Game title already exists. Please enter a unique title.\n");
            			continue; 
        			}

      
        			printf("Enter Game Type[Action|RPG|Adventure|Card Game]: ");
		    	    scanf(" %[^\n]", genre);
			        while (strcmp(genre, "Action") != 0 && strcmp(genre, "RPG") != 0 &&
               		strcmp(genre, "Adventure") != 0 && strcmp(genre, "Card Game") != 0) {
            			printf("Enter Game Type[Action|RPG|Adventure|Card Game]: ");
            			scanf(" %[^\n]", genre);
        			}

        			printf("Enter Game Stock[>=1]: ");
        			scanf("%d", &stock);
        			while (stock < 1) {
            			printf("Enter Game Stock[>=1]: ");
            			scanf("%d", &stock);
        			}

        			root = insertGame(root, title, genre, stock);
        			printf("Insert Success!!\n");
        			printf("Press enter to continue...");
        			getchar();
        			getchar();
        			break; 
    			} while (1);
    			break;


            case 2:
            	system("cls");
                if (root == NULL) {
                    printf("Warehouse is empty !\n");
                    printf("Press enter to continue...\n");
                    getchar();	
                    getchar();
                } else {
                	printf("--------------------------------------------------------\n");
                    printf("| Title                    | Game Genre   | Game Stock |\n");
                    printf("--------------------------------------------------------\n");
                    inOrder(root);
                    printf("Press enter to continue...");
    				getchar();
    				getchar();
                }
                break;

            case 3:
            	system("cls");
                printf("Enter Game Title to update stock: ");
                scanf(" %[^\n]", title);
                struct Game *game = searchGame(root, title);
                if (game == NULL) {
                    printf("Data not found!\n");
                    printf("Press enter to continue...");
    				getchar();
    				getchar();
                    break;
                }

                printf("Input update type[add|remove][case insensitive]: ");
                scanf("%s", updateType);
				
                updateStock(root, title, updateType);
                
                
                
                printf("Press enter to continue...");
    			getchar();
    			getchar();
                
                break;

            case 4:
            	system("cls");
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}

