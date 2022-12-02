#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX 80

struct Info {
    char name[MAX];
    int age;
};

typedef struct node {
    struct Info data;
    struct node* nextNodePtr;
} Node;


void fgetsRemoveNewLine(char *str);
int strcmpIgnoreCase(char *s1, char *s2);
char validateYesNo(void);
void insertPet(Node** headPtr, struct Info *info);
void displayPets(Node* listPtr);
void writeToFile(Node* listPtr);
void removePet(Node** headPtr, struct Info *info);
void removeRemainingPets(Node** headPtr);

int main(int argc, const char * argv[]) {
    // Use a linked list to store the pet information in alphabetical order.
    Node* headNodePtr = NULL;
    char yesOrNo = ' ';

    displayPets(headNodePtr);

    // add pets to list
    do {
        struct Info info = {};
        
        puts("Enter name: ");
        fgetsRemoveNewLine(info.name);
        
        puts("Enter age: ");
        char temp[MAX]; // makes it so fgets can still be used for int
        fgetsRemoveNewLine(temp);
        char *ptr; // needed for strtod function
        info.age = strtod(temp, &ptr);

        insertPet(&headNodePtr, &info);

        displayPets(headNodePtr);
        printf("%s", "\nDo you want to add another pet? ");
        yesOrNo = validateYesNo();
        
    } while (yesOrNo == 'y');

    // write pets to a file
    writeToFile(headNodePtr);
    
    // remove pets from list
    do {
        struct Info info = {};
        
        puts("\nEnter pet in the list to remove:");
        fgetsRemoveNewLine(info.name);

        removePet(&headNodePtr, &info);

        displayPets(headNodePtr);

        printf("%s", "\nDo you want to remove another pet? ");
        yesOrNo = validateYesNo();

    } while ((yesOrNo == 'y') && (headNodePtr != NULL));

    displayPets(headNodePtr);
    removeRemainingPets(&headNodePtr);
    displayPets(headNodePtr);

    return 0;
}

// replicates the fgets function, and then runs strtok to remove the trailing new line character
void fgetsRemoveNewLine(char *str){
    fgets(str, MAX, stdin);
    strtok(str, "\n");
}

// function does string compare but ignores case
int strcmpIgnoreCase(char *s1, char *s2){
    // use temporary variables so the name of the pet is not actually changed
    char temp1[MAX];
    strcpy(temp1, s1);
    for(unsigned int i = 0; i < strlen(temp1); i++){
        temp1[i] = tolower(temp1[i]);
    }
    
    char temp2[MAX];
    strcpy(temp2, s2);
    for(unsigned int i = 0; i < strlen(temp2); i++){
        temp2[i] = tolower(temp2[i]);
    }
    
    return strcmp(temp1, temp2);
}

char validateYesNo(void) {
    char validYesNo;

    do {
        puts("Please enter (y)es or (n)o:");
        validYesNo = getchar();
        while (getchar() != '\n');

        validYesNo = tolower(validYesNo);

    } while (validYesNo != 'y' && validYesNo != 'n');

    return  validYesNo;
}

// function to insert pets
void insertPet(Node** headPtr, struct Info *info){
    
    Node* newNodePtr = malloc(sizeof(Node));
    if (newNodePtr != NULL) {
            
        newNodePtr->data = *info;
        newNodePtr->nextNodePtr = NULL;
        Node* previousPtr = NULL;
        Node* currentPtr = *headPtr;
        
        while (currentPtr != NULL && strcmpIgnoreCase(currentPtr->data.name, info->name) <= 0) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextNodePtr;
        }
            
        if (previousPtr == NULL) {
            *headPtr = newNodePtr;
        }
        else {
            previousPtr->nextNodePtr = newNodePtr;
        }
            
        newNodePtr->nextNodePtr = currentPtr;
    }
    else {
        printf("No memory to create node for %s\n", info->name);
    }
}

// Function to display list of pets
void displayPets(Node* listPtr){
    // Display the names and corresponding age
    if (listPtr != NULL) {
        puts("The names in alphabetical order: ");
        Node* currentPtr = listPtr;
        while (currentPtr != NULL) {
            // display and go to next node
            printf("%s is %d years old\n", currentPtr->data.name, currentPtr->data.age);
            currentPtr = currentPtr->nextNodePtr;
        }
    }
    else {
        puts("There aren’t any pets in the list");
    }
}

// Function to write the names and ages of the pets to a file if there are any pets
void writeToFile(Node* listPtr){
    FILE *fp;
    fp = fopen("file.txt", "w");
    
    if (listPtr != NULL) {
        puts("\nWriting pets to a file...");
        Node* currentPtr = listPtr;
        while (currentPtr != NULL) {
            // write to file and go to next node
            fprintf(fp, "%s is %d years old\n", currentPtr->data.name, currentPtr->data.age);
            currentPtr = currentPtr->nextNodePtr;
        }
    }
    else {
        puts("There aren’t any pets in the list");
    }
}

// function to remove pet
void removePet(Node** headPtr, struct Info *info){
 
    Node* previousPtr = NULL;
    Node* currentPtr = *headPtr;

    if (*headPtr != NULL) {
        if (strcmpIgnoreCase((*headPtr)->data.name, info->name) == 0) {
            *headPtr = (*headPtr)->nextNodePtr;
            free(currentPtr);
            currentPtr = NULL;
        }
        else {
            while (currentPtr != NULL && strcmpIgnoreCase(currentPtr->data.name, info->name) != 0) {
                previousPtr = currentPtr;
                currentPtr = currentPtr->nextNodePtr;
            }

            if (currentPtr != NULL) {
                previousPtr->nextNodePtr = currentPtr->nextNodePtr;
                free(currentPtr);
                currentPtr = NULL;
            }
            else {
                puts("Pet to remove not found");
            }
        }
    }
    else {
        puts("There aren't any pets in the list");
    }
}

void removeRemainingPets(Node** headPtr) {
    puts("Remove all animals from memory before exiting program");
    
    Node* currentPtr = *headPtr;
    Node* nextNodePtr = NULL;

    while (currentPtr != NULL) {
        nextNodePtr = currentPtr->nextNodePtr;
        free(currentPtr);
        currentPtr = nextNodePtr;
    }

    *headPtr = NULL;
}
