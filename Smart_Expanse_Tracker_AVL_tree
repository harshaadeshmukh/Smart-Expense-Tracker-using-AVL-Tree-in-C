#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_DATE_LENGTH 11 // For storing dates in the format DD-MM-YYYY
#define MAX_DESCRIPTION_LENGTH 100		//For description of expanses
#define MAX_ID 9999 // Maximum ID value

struct AVLNode {
    int id;
    char date[MAX_DATE_LENGTH];
    float amount;
    char description[MAX_DESCRIPTION_LENGTH];
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

int generateUniqueID(bool usedIDs[]) {
    int id;
    do {
        id = rand() % (MAX_ID - 1000 + 1) + 1000; // Generate random ID between 1000 and 9999
    } while (usedIDs[id]); // Repeat if ID is already used
    usedIDs[id] = true; // Mark the ID as used
    return id;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

struct AVLNode *newNode(int id, char *date, float amount, char *description) {
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->id = id;
    strcpy(node->date, date);
    node->amount = amount;
    strcpy(node->description, description);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct AVLNode *rightRotate(struct AVLNode *y) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct AVLNode *leftRotate(struct AVLNode *x) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct AVLNode *insertNode(struct AVLNode *node, bool usedIDs[], char *date, float amount, char *description) {
    if (node == NULL)
        return newNode(generateUniqueID(usedIDs), date, amount, description);

    if (strcmp(date, node->date) < 0)
        node->left = insertNode(node->left, usedIDs, date, amount, description);
    else if (strcmp(date, node->date) > 0)
        node->right = insertNode(node->right, usedIDs, date, amount, description);
    else {
        // If the dates are the same, insert on the right subtree
        node->right = insertNode(node->right, usedIDs, date, amount, description);
    }

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

struct AVLNode *minValueNode(struct AVLNode *node) {
    struct AVLNode *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct AVLNode *deleteNode(struct AVLNode *root, bool usedIDs[], int idToDelete) {
	
	 if (root == NULL) {   
        return root;
}

    if (idToDelete < root->id)
        root->left = deleteNode(root->left, usedIDs, idToDelete);
    else if (idToDelete > root->id)
        root->right = deleteNode(root->right, usedIDs, idToDelete);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct AVLNode *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            struct AVLNode *temp = minValueNode(root->right);
            root->id = temp->id;
            strcpy(root->date, temp->date);
            root->amount = temp->amount;
            strcpy(root->description, temp->description);
            root->right = deleteNode(root->right, usedIDs, temp->id);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void printExpenses(struct AVLNode *root) {
    if (root != NULL) {
        printExpenses(root->left);
        printf("%d\t\t%s\t\t%.2f\t\t%s\n", root->id, root->date, root->amount, root->description);
        printExpenses(root->right);
    }
}

void freeAVLTree(struct AVLNode *root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}

struct AVLNode *loadExpensesFromFile(FILE *fp, int *idCounter) {
    struct AVLNode *root = NULL;
    bool usedIDs[MAX_ID + 1] = {false}; // Fixed variable name and type
    int id; // Changed variable name
    char date[MAX_DATE_LENGTH];
    float amount;
    char description[MAX_DESCRIPTION_LENGTH];
    while (fscanf(fp, "%d %s %f %[^\n]", &id, date, &amount, description) != EOF) {
        root = insertNode(root, usedIDs, date, amount, description);
        // Update idCounter if necessary
        if (id >= *idCounter) {
            *idCounter = id + 1;
        }
    }

    return root;
}

void saveExpensesToFile(struct AVLNode *root, FILE *fp) {
    if (root != NULL) {
        saveExpensesToFile(root->left, fp);
        fprintf(fp, "%d %s %.2f %s\n", root->id, root->date, root->amount, root->description);
        saveExpensesToFile(root->right, fp);
    }
}

void searchAndPrintExpenses(struct AVLNode *root, char *date) {
    if (root != NULL) {
        searchAndPrintExpenses(root->left, date);
        if (strcmp(root->date, date) == 0) {
            printf("%d\t\t%s\t\t%.2f\t\t%s\n", root->id, root->date, root->amount, root->description);
        }
        searchAndPrintExpenses(root->right, date);
    }
}

struct AVLNode *searchExpenseByDate(struct AVLNode *root, char *date) {
    if (root == NULL || strcmp(root->date, date) == 0)
        return root;

    if (strcmp(root->date, date) < 0)
        return searchExpenseByDate(root->right, date);

    return searchExpenseByDate(root->left, date);
}

struct AVLNode *searchExpenseById(struct AVLNode *root, int id) {
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return searchExpenseById(root->left, id);
    else
        return searchExpenseById(root->right, id);
}

int main() {
    struct AVLNode *root = NULL;
    int idCounter = 0; // Starting ID counter at 0
    int choice;
    int op;
    char date[MAX_DATE_LENGTH];
    float amount;
    char description[MAX_DESCRIPTION_LENGTH];
    int idToDelete;

    bool usedIDs[MAX_ID + 1] = {false};
    FILE *fp;

    // Load expenses from file if it exists
    fp = fopen("expenses.txt", "r");
    if (fp != NULL) {
        root = loadExpensesFromFile(fp, &idCounter);
        fclose(fp);
    }

    printf("*********Smart Expense Tracker using AVL tree*********\n");

    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Delete Expense\n");
        printf("4. Save Expenses\n");
        printf("5. Search Expanses\n");
        printf("6. Exit\n");
       
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter expense date (DD-MM-YYYY): ");
                scanf("%s", date);
                printf("Enter expense amount: ");
                scanf("%f", &amount);
                printf("Enter expense description: ");
                getchar(); // Consume newline
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; // Remove trailing newline
                root = insertNode(root, usedIDs, date, amount, description);
                break;
            case 2:
                printf("Expenses:\n");
                printf("ID\t\tDate\t\t\tAmount\t\tDescription\n");
                printExpenses(root);
                break;
            
			case 3:
				printf("Enter expense ID to delete: ");
				scanf("%d", &idToDelete);

				// Check if the expense with the given ID exists before attempting deletion
				struct AVLNode *deletedNode = searchExpenseById(root, idToDelete);
				if (deletedNode == NULL) {
    			printf("No expense found with ID %d.\n", idToDelete);
				} else {
    				root = deleteNode(root, usedIDs, idToDelete);
    				printf("Expense with ID %d deleted successfully.\n", idToDelete);
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
           	printf("Select 1 option to search exapnses by 1.(date) or 2.(ID) : ");
           	scanf("%d",&op);
           	switch(op)
           	{
           		case 1:
           			printf("Enter expense date to search (DD-MM-YYYY): ");
                	scanf("%s", date);
                	printf("ID\t\tDate\t\t\tAmount\t\tDescription\n");	
                	searchAndPrintExpenses(root, date);
                	break;
                
                case 2:
                	printf("Enter expense ID to search: ");
                	scanf("%d", &idToDelete);
                	printf("ID\t\tDate\t\t\tAmount\t\tDescription\n");
                	struct AVLNode *result = searchExpenseById(root, idToDelete);
                	if (result != NULL) {
                		printf("Expense found:\n");
                    	printf("%d\t\t%s\t\t%.2f\t\t%s\n", result->id, result->date, result->amount, result->description);
                	} else {
                    	printf("Expense not found for the given ID.\n");
                	}
               		break;			   	
			}
			break;                
                
             case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    freeAVLTree(root);
    return 0;
}
