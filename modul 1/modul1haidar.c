#include <stdio.h>
#include <string.h>

// Struct untuk menyimpan informasi obat
struct Medicine {
    int no;
    char code[7];
    char name[50];
    char disease[50];
    int stock;
    int price;
};



// Fungsi untuk menambahkan stok obat
void addStock(struct Medicine medicineList[], int size) {
    char code[7];
    int quantity;
    int found = 0;
    printf("\nEnter medicine code: ");
    scanf("%s", code);
    for (int i = 0; i < size; i++) {
        if (strcmp(medicineList[i].code, code) == 0) {
            found = 1;
            printf("\nEnter quantity (1-100): ");
            scanf("%d", &quantity);
            if (quantity < 1 || quantity > 100) {
                printf("\nInvalid quantity!\n");
                return;
            }
            medicineList[i].stock += quantity;
            printf("\nStock added successfully!\n");
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
            break;
        }
    }
    if (!found) {
        printf("\nMedicine Code Doesn't Exist!\n");
    }
}

// Fungsi untuk menjual obat
void sell(struct Medicine medicineList[], int size) {
    char code[7];
    int quantity;
    int found = 0;

    printf("\nEnter medicine code: ");
    scanf("%s", code);
    
    for (int i = 0; i < size; i++) {
        if (strcmp(medicineList[i].code, code) == 0) {
            found = 1;
            printf("\nEnter quantity (1-%d): ", medicineList[i].stock);
            scanf("%d", &quantity);
            
            if (quantity < 1 || quantity > medicineList[i].stock) {
                printf("\nInvalid quantity!\n");
                return;
            }
            
            int totalPrice = medicineList[i].price * quantity;
            
            printf("+----Total Price----+\n");
            printf(" Rp %d,-\n", medicineList[i].price);
            printf(" Quantity: %d\n", quantity);
            printf(" ------------------X\n");
            printf(" Total: Rp %d,-\n", totalPrice);
            printf("+-------------------+\n\n\n");

            medicineList[i].stock -= quantity;
            printf("  -- Thank You --.\n");
            break;
        }
    }
    if (!found) {
        printf("Medicine Code Doesn't Exist!\n");
    }
}

int main() {
    // Inisialisasi daftar obat
    struct Medicine medicineList[3] = {
        {1, "M001", "Paracetamol", "Fever", 50, 5000},
        {2, "M002", "Amoxicillin", "Infection", 30, 10000},
        {3, "M003", "Loratadine", "Allergy", 20, 8000}
    };
    int size = sizeof(medicineList) / sizeof(medicineList[0]);

    int choice;
    do {
        // Menampilkan menu
        printf("                     +------------------------------+\n");
        printf("                     |     APOTEK BERKAT 24 JAM     |\n");
        printf("                     +------------------------------+\n");
        printf("+------------------------------------------------------------------------+\n");
        printf("| No | Code | Medicine Name\t| Disease\t| Stock\t | Price\t |\n");
        printf("+------------------------------------------------------------------------+\n");
        for (int i = 0; i < size; i++) {
        printf("| %d  | %s | %s\t| %s \t| %d\t | Rp %d,-\t |\n", medicineList[i].no, medicineList[i].code, medicineList[i].name, medicineList[i].disease, medicineList[i].stock, medicineList[i].price);
        }
        printf("+------------------------------------------------------------------------+\n");
        printf("\n1. Add Stock\n");
        printf("2. Sell\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStock(medicineList, size);
                break;
            case 2:
                sell(medicineList, size);
                break;
            case 3:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
