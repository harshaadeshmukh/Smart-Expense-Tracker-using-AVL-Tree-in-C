#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>

// Constants used repeatatively in program 
#define MAX_DATE_LENGTH 11
#define MAX_DESCRIPTION_LENGTH 100
#define MAX_CATEGORY_LENGTH 50
#define MAX_ID 9999

// Prototypes declaration
struct AVLNode;
struct AVLNode *rightRotate(struct AVLNode *y);
struct AVLNode *leftRotate(struct AVLNode *x);
int getBalance(struct AVLNode *node);
int height(struct AVLNode *node);
struct AVLNode *newNode(int id, char *date, char *category, float amount, char *description);
void getCurrentDate(char *date);
struct AVLNode *insertNode(struct AVLNode *node, bool usedIDs[], char *date, char *category, float amount, char *description);
void printExpenses(struct AVLNode *root);
void searchAndPrintExpenses(struct AVLNode   *root, char *date, char *category);
int generateUniqueID(bool usedIDs[]);
struct AVLNode *searchExpenseById(struct AVLNode *root, int id);
struct AVLNode *deleteNode(struct AVLNode *root, bool usedIDs[], int idToDelete);
struct AVLNode *minValueNode(struct AVLNode *node);
struct AVLNode *loadExpensesFromFile(FILE *fp, int *idCounter);
void saveExpensesToFile(struct AVLNode *root, FILE *fp);
void freeAVLTree(struct AVLNode *root);

// Node structure of AVL tree
struct AVLNode {
    int id;
    char date[MAX_DATE_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    float amount;
    char description[MAX_DESCRIPTION_LENGTH];
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

// function for laoding animation
void load(){
    system("cls");
    SetConsoleTitle(" Smart Expense Tracker ");//setting console title to Village Governance System
    system("Color 04");//setting color of text to red
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t LOADING....\n\n");
    printf("\t\t\t\t");
    char x = 219;// A Special character printing sequence
    int i;
    for( i=0;i<35;i++)
     {
      printf("%c",x);
      if(i<10)
        Sleep(300);// Stops execution of the system for 300 ms
      if(i>=10&&i<20)
        Sleep(150);
      if(i>=10)
        Sleep(25);
     }
    system("cls");// For clearing console
    printf("\n\n\n\n");
    system("Color 02");// Setting text color to green after loading happens
    printf("\t\t\t\t------ Smart Expense Tracker ------- \n\n\n");
    Sleep(1000);
}

int main() {

	load();
	system("cls");
	system("Color 00");
    struct AVLNode *root = NULL;
    int idCounter = 0;
    int choice;
    char date[MAX_DATE_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    float amount;
    char description[MAX_DESCRIPTION_LENGTH];
    int idToDelete;

    bool usedIDs[MAX_ID + 1] = {false};
    FILE *fp;
    
    fp = fopen("expenses.txt", "r");
    if (fp != NULL) {
        root = loadExpensesFromFile(fp, &idCounter);
        fclose(fp);
    }

    printf("********* Smart Expense Tracker using AVL tree *********\n");

    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Delete Expense\n");
        printf("4. Save Expenses\n");
        printf("5. Search Expenses\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter expense category: ");
                scanf("%s", category);
                printf("Enter expense amount: ");
                scanf("%f", &amount);
                printf("Enter expense description: ");
                getchar();
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0';
			
                int dateChoice;
                printf("Do you want to enter the current date (1) or a specific date (2)? ");
                scanf("%d", &dateChoice);
                if (dateChoice == 1) {
                    getCurrentDate(date);
                } else if (dateChoice == 2) {
                    printf("Enter expense date (DD-MM-YYYY): ");
                    scanf("%s", date);
                } else {
                    printf("Invalid choice. Current date will be used.\n");
                    getCurrentDate(date);
                }
                root = insertNode(root, usedIDs, date, category, amount, description);
                fp = fopen("expenses.txt", "w");
                if (fp != NULL) {
                    saveExpensesToFile(root, fp);
                    fclose(fp);
                    printf("Expenses saved to file.\n");
                } else {
                    printf("Error: Unable to save expenses to file.\n");
                }
                break;
            case 2:
                printf("Expenses:\n");
                printf("ID\t\tDate\t\t\tCategory\t\tAmount\t\tDescription\n");
                printf("\n");
                printExpenses(root);
                break;
            case 3:
                printf("Enter expense ID to delete: ");
                scanf("%d", &idToDelete);
                struct AVLNode *deletedNode = searchExpenseById(root, idToDelete);
                if (deletedNode == NULL) {
                    printf("No expense found with ID %d.\n", idToDelete);
                } else {
                    root = deleteNode(root, usedIDs, idToDelete);
                    printf("Expense with ID %d deleted successfully.\n", idToDelete);
                }
                fp = fopen("expenses.txt", "w");
                if (fp != NULL) {
                    saveExpensesToFile(root, fp);
                    fclose(fp);
                    printf("Expenses saved to file.\n");
                } else {
                    printf("Error: Unable to save expenses to file.\n");
                }
                break;
            case 4:
                fp = fopen("expenses.txt", "w");
                if (fp != NULL) {
                    saveExpensesToFile(root, fp);
                    fclose(fp);
                    printf("Expenses saved to file.\n");
                } else {
                    printf("Error: Unable to save expenses to file.\n");
                }
                break;
            case 5:
                printf("Enter expense date (DD-MM-YYYY): ");
                scanf("%s", date);
                printf("Enter expense category: ");
                scanf("%s", category);
                printf("ID\t\tDate\t\t\tCategory\tAmount\t\tDescription\n");
            
                searchAndPrintExpenses(root, date, category);
                break;
            case 6:
            	system("cls");
                fp = fopen("expenses.txt", "w");
                if (fp != NULL) {
                    saveExpensesToFile(root, fp);
                    fclose(fp);
                    printf("Expenses saved to file.\n");
                } else {
                    printf("Error: Unable to save expenses to file.\n");
                }
                printf("\n\n\n\n\n\n\n");
                printf("\t\t\t\tPreparing for Exiting The System ...\n\n\n");
                system("Color 04");//Again setting color of text to red
                Sleep(1000);
                printf("\t\t\t\t EXITING : ");
                int i;
                for(i =0;i<5;i++)
                {
                    printf(" *_* ");
                    Sleep(1000);
                }
                printf("\n\n\n\n\n");
                system("cls");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

	// freeing memory resources
    printf("Before freeing AVL tree\n");
    freeAVLTree(root);
    printf("Press Enter to exit...\n");
    getchar();
    return 0;
}

// Right rotate tree
struct AVLNode *rightRotate(struct AVLNode *y) {
    if (y == NULL)
        return y;
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// Left rotate tree
struct AVLNode *leftRotate(struct AVLNode *x) {
    if (x == NULL)
        return x;
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// Calculating balance factor 
int getBalance(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// finding height of the tree
int height(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// function for creating the new AVL tree node
struct AVLNode *newNode(int id, char *date, char *category, float amount, char *description) {
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->id = id;
    strcpy(node->date, date);
    strcpy(node->category, category);
    node->amount = amount;
    strcpy(node->description, description);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Finding the current date 
void getCurrentDate(char *date) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    sprintf(date, "%02d-%02d-%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
}

// Inserting node into new node
struct AVLNode *insertNode(struct AVLNode *node, bool usedIDs[], char *date, char *category, float amount, char *description) {
    if (node == NULL)
        return newNode(generateUniqueID(usedIDs), date, category, amount, description);
    int cmp = strcmp(date, node->date);
    if (cmp < 0)
        node->left = insertNode(node->left, usedIDs, date, category, amount, description);
    else if (cmp > 0)
        node->right = insertNode(node->right, usedIDs, date, category, amount, description);
    else
        node->right = insertNode(node->right, usedIDs, date, category, amount, description);

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && strcmp(date, node->left->date) < 0)
        return rightRotate(node);
    if (balance < -1 && strcmp(date, node->right->date) > 0)
        return leftRotate(node);
    if (balance > 1 && strcmp(date, node->left->date) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && strcmp(date, node->right->date) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// extracting the expenses and displaying  by inorder
void printExpenses(struct AVLNode *root) {
    if (root != NULL) {
        printExpenses(root->left);  
        printf("%d\t\t%s\t\t%s\t\t\t%.2f\t\t%s\n", root->id, root->date, root->category, root->amount, root->description);
        printExpenses(root->right);
    }
}

// Search and print expenses
void searchAndPrintExpenses(struct AVLNode *root, char *date, char *category) {
    if (root != NULL) {
        searchAndPrintExpenses(root->left, date, category);
        // Convert both the input category and category in AVL tree to lowercase
        char lowerInputCategory[MAX_CATEGORY_LENGTH];
        char lowerTreeCategory[MAX_CATEGORY_LENGTH];
        strcpy(lowerInputCategory, category);
        int i;
        strcpy(lowerTreeCategory, root->category);
        for ( i = 0; lowerInputCategory[i]; i++) {
            lowerInputCategory[i] = tolower(lowerInputCategory[i]);
        }
        for ( i = 0; lowerTreeCategory[i]; i++) {
            lowerTreeCategory[i] = tolower(lowerTreeCategory[i]);
        }
        if (strcmp(root->date, date) == 0 && strcmp(lowerTreeCategory, lowerInputCategory) == 0) {
            printf("%d\t\t%s\t\t%s\t\t%.2f\t\t%s\n", root->id, root->date, root->category, root->amount, root->description);
        }
        searchAndPrintExpenses(root->right, date, category);
    }
}

// random id generator
int generateUniqueID(bool usedIDs[]) {
    int id;
    do {
        id = rand() % (MAX_ID - 1000 + 1) + 1000;
    } while (usedIDs[id]);
    usedIDs[id] = true;
    return id;
}

struct AVLNode *searchExpenseById(struct AVLNode *root, int id) {
    if (root == NULL) {
        return NULL; // Expense not found
    }
    
    if (id == root->id) {
        return root; // Found expense with matching ID
    }
    
    // If ID is smaller, search in the left subtree
    if (id < root->id) {
        return searchExpenseById(root->left, id);
    }
    // If ID is larger, search in the right subtree
    else {
        return searchExpenseById(root->right, id);
    }
}



struct AVLNode *deleteNode(struct AVLNode *root, bool usedIDs[], int idToDelete) {
    if (root == NULL)
        return root;

    if (idToDelete < root->id)
        root->left = deleteNode(root->left, usedIDs, idToDelete);
    else if (idToDelete > root->id)
        root->right = deleteNode(root->right, usedIDs, idToDelete);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct AVLNode *temp = root->left ? root->left : root->right;
            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp;
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct AVLNode *temp = minValueNode(root->right);
            // Copy the inorder successor's data to this node
            root->id = temp->id;
            strcpy(root->date, temp->date);
            strcpy(root->category, temp->category);
            root->amount = temp->amount;
            strcpy(root->description, temp->description);
            // Delete the inorder successor
            root->right = deleteNode(root->right, usedIDs, temp->id);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are four cases

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



struct AVLNode *minValueNode(struct AVLNode *node) {
    struct AVLNode *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct AVLNode *loadExpensesFromFile(FILE *fp, int *idCounter) {
    struct AVLNode *root = NULL;
    bool usedIDs[MAX_ID + 1] = {false};
    int id;
    char date[MAX_DATE_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    float amount;
    char description[MAX_DESCRIPTION_LENGTH];
    
    // Check if file is open
    if (fp == NULL) {
        printf("Error: Unable to open file for reading\n");
        return NULL;
    }

    while (fscanf(fp, "%d %s %s %f %[^\n]", &id, date, category, &amount, description) == 5) {
      //  printf("Read: ID=%d, Date=%s, Category=%s, Amount=%.2f, Description=%s\n", id, date, category, amount, description);
        root = insertNode(root, usedIDs, date, category, amount, description);
        if (id >= *idCounter) {
            *idCounter = id + 1;
        }
    }

    return root;
}
void saveExpensesToFile(struct AVLNode *root, FILE *fp) {
    if (root != NULL) {
        saveExpensesToFile(root->left, fp);
        fprintf(fp, "%d %s %s %.2f %s\n", root->id, root->date, root->category, root->amount, root->description);
        saveExpensesToFile(root->right, fp);
    }
}

void freeAVLTree(struct AVLNode *root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}
