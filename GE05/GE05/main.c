#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 80

struct Info {
    char name[MAX];
    int age;
};

void fgetsRemoveNewLine(char *str);
int strcmpIgnoreCase(char *s1, char *s2);
void insertPet(void);
void displayPets(void);
void writeToFile(void);
void removePet(void);

int main(int argc, const char * argv[]) {
    // Use a linked list to store the pet information in alphabetical order.
    char str1[MAX];
       char str2[MAX];
       int ret;


       strcpy(str1, "abcdef");
       strcpy(str2, "ABCDEF");

       ret = strcmpIgnoreCase(str1, str2);

       if(ret < 0) {
          printf("str1 is less than str2");
       } else if(ret > 0) {
          printf("str2 is less than str1");
       } else {
          printf("str1 is equal to str2");
       }
    
    printf("\n%s  %s\n", str1, str2);
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

// Function to insert pets:
void insertPet(void){
    // Program will ask the user to enter the name and age of the pet. Ask if they want to add another  pet (y)es or (n)o until the user enters (n)o.
    // You do not need to do any validation when the user enters the age. Assume only valid integer values will be entered.
    // Allocate memory for the pet
    // Insert the names and ages in the linked list in alphabetical order. You do not need to do anything if a duplicate name is entered.
}

// Function to display list of pets
void displayPets(void){
    // Display the names and corresponding age
    // Report if there aren’t any pets in the list
}

// Function to write the names and ages of the pets to a file if there are any pets
void writeToFile(void){
    
}

// Function to remove pet
void removePet(void){
    // Ask if they want to remove a pet (y)es or (n)o until the user enters n(o). Repeat this question until they answer no or when there are no more pets in the list.
    // Ask for the name to be deleted
    // Report if name not in the list
    // Delete if matches name in the list (deallocate memory)
    // If there are no more pets in the list after the deletion display a message and do not ask if they want to remove a pet.
    // Display pets in the list
}
