#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// global constants
#define BUFF 80
#define DISTANCE_MAX 200    // race distance max
#define DISTANCE_MIN 1      // race distance min
#define COST_MAX 200        // race cost max
#define COST_MIN 50         // race cost min
#define JERSEY_MAX 150      // jersey cost max
#define JERSEY_MIN 50       // jersey cost min
#define CHARITY_MAX 30      // charty percentage max
#define CHARITY_MIN 5       // charity percentage min
#define PIN "B!k34u"        // admin password
#define ATTEMPTS 3          // number of attempts for entering admin pin
#define FILE_PATH "/Users/carsonjenkins/Downloads/" // file path for saving summaries
const char *SIZES[4] = {"(s)mall", "(m)edium", "(l)arge", "(x)tra-large"};
const char *CHOICE[2] = {"(y)es", "(n)o"};

// hold information for an organization
struct Organization {
    char organizationName[BUFF];
    double raceDistance;
    double raceCost;
    double jerseyCost;
    double charityPercent;
    double totalCost;
    // counters for registrants and jersey purchases
    unsigned int registrants;
    unsigned int jerseys;
};

// linked list
typedef struct node {
    struct Organization data;
    struct node* next;
} Node;

// function prototypes
void adminSetUp(void);
void registration(Node** headPtr);
void insertOrganization(Node** headPtr, struct Organization *info);
void displayOrganizations(Node* headPtr);
void summaryAndFile(Node* headPtr);
unsigned int getValidPin(void);
void fgetsRemoveNewLine(char *str);
int strcmpIgnoreCase(char *s1, char *s2);
void getValidDouble(double *dbl, int min, int max);
char getValidChar(char prompt[], const char *str[], int size);
void deallocate(Node** headPtr);

int main(int argc, const char * argv[]) {
    adminSetUp();
    return 0;
}

// adminSetUp mode
void adminSetUp() {
    // run function getValidPin, returning the attempts counter
    if(getValidPin() <= ATTEMPTS) {
        Node* headPtr = NULL;
        
        // do-while prompts for organization info, then adds organization to linked list before prompting again
        do {
            struct Organization info = {};
            
            puts("\n-------------------\nOrganization set up \n-------------------\nEnter fundraising organizations name:");
            fgetsRemoveNewLine(info.organizationName);
            
            puts("\nEnter distance in miles for the bike course:");
            getValidDouble(&info.raceDistance, DISTANCE_MIN, DISTANCE_MAX);
            printf("The bike race distance is %.0lf miles\n", info.raceDistance);
            
            printf("\nEnter the registration cost of the bike ride for %s:\n", info.organizationName);
            getValidDouble(&info.raceCost, COST_MIN, COST_MAX);
            printf("The bike race cost is $%.2lf\n", info.raceCost);
            
            printf("\nEnter sales price of jersey for %s:\n", info.organizationName);
            getValidDouble(&info.jerseyCost, JERSEY_MIN, JERSEY_MAX);
            printf("The bike jersey cost is $%.2lf\n", info.jerseyCost);
            
            printf("\nEnter percentage of the bike race sales that will be donated to %s:\n", info.organizationName);
            getValidDouble(&info.charityPercent, CHARITY_MIN, CHARITY_MAX);
            printf("You entered %.0lf%% of the bike race to go to charity\n", info.charityPercent);
            
            insertOrganization(&headPtr, &info);

            puts("\nDo you want to set up another organization?");
        } while(getValidChar("Please enter y or n", CHOICE, 2) == 'y');
        
        // run registration for user
        registration(&headPtr);
    }
    else {
        puts("Exiting admin set-up");
    }
}

// registration mode
void registration(Node **headPtr) {
    char userName[BUFF];
    bool quit = false;
    
    // while loop will continue running until Quit is entered at the prompt for name
    while(!quit) {
        displayOrganizations(*headPtr);
        struct Organization info = {};
        bool exit = false;
        
        // for selecting an organization, exits once the given org matches the one in the linked list
        while(!exit) {
            puts("\nEnter organization to register for:");
            fgetsRemoveNewLine(info.organizationName);
            Node* previousPtr = NULL;
            Node* currentPtr = *headPtr;
            if (strcmpIgnoreCase((*headPtr)->data.organizationName, info.organizationName) == 0) {
                // sets info to the point in the linked list where the given name matches the organization
                info = (*headPtr)->data;
                exit = true;
            }
            else {
                // goes until the given name matches the organization in the linked list
                while (currentPtr != NULL && strcmpIgnoreCase(currentPtr->data.organizationName, info.organizationName) != 0) {
                    previousPtr = currentPtr;
                    currentPtr = currentPtr->next;
                }
                if (currentPtr != NULL) {
                    // sets info to the point in the linked list where the given name matches the organization
                    info = previousPtr->next->data;
                    exit = true;
                }
                else {
                    puts("Organization not found");
                }
            }
        }
        
        puts("\nEnter your first name and last name to register for the ride (or 'Quit' to end program):");
        fgetsRemoveNewLine(userName);
        
        if(strcmpIgnoreCase(userName, "Quit") == 0) {
            // run function pin validation, returning attempts counter
            if(getValidPin() <= ATTEMPTS) {
                // print summary and save into files
                puts("\n-------\nSummary\n-------");
                summaryAndFile(*headPtr);
                quit = true;
            }
        }
        else {
            info.registrants++;
            info.totalCost = info.totalCost + info.raceCost;
            double localTotal = info.raceCost; // for printing certain totals throughout
            printf("\nDo you want to purchase a jersey for $%.2lf?\n", info.jerseyCost);
            if(getValidChar("Please enter y or n", CHOICE, 2) == 'y') {
                info.jerseys++;
                puts("\nSelect your shirt size by entering the character in parenthesis - (s)mall (m)edium (l)arge (x)tra-large:");
                // get jersery size
                getValidChar("Please enter s, m, l or x", SIZES, 4);
                info.totalCost = info.totalCost + info.jerseyCost;
                localTotal = localTotal + info.jerseyCost;
            }
            
            // validate credit card for number XXXX-####-#####
            char creditCard[BUFF] = {};
            while(!(isdigit(creditCard[0]) && isdigit(creditCard[1]) && isdigit(creditCard[2]) && isdigit(creditCard[3]) && creditCard[4] == '-' && isalpha(creditCard[5]) && isalpha(creditCard[6]) && isalpha(creditCard[7]) && isalpha(creditCard[8]) && creditCard[9] == '-' && isalpha(creditCard[10]) && isalpha(creditCard[11]) && isalpha(creditCard[12]) && isalpha(creditCard[13]) && isalpha(creditCard[14]))){
                printf("\nYour total cost is $%.2lf. Enter your credit card (####-XXXX-XXXXX):\n", localTotal);
                fgetsRemoveNewLine(creditCard);
            }
            printf("\nThank you %s for your purchase. $%.2lf of the ticket sales will go to charity\n", userName, (info.charityPercent/100)*localTotal);
        
            puts("\nDo you want a receipt (y)es or (n)o?");
            if(getValidChar("Please enter y or n", CHOICE, 2) == 'y') {
                // prints receipt
                printf("\n-------\nReceipt\n-------\nRace\t$%.2lf\nJersey\t$%.2lf\n\nTotal Cost: $%.2lf\nDonation to Charity: $%.2lf\n", info.raceCost, info.jerseyCost, localTotal, (info.charityPercent/100)*localTotal);
            }
            
            // similar algorithm used for organization selection, this goes back and updates values in linked list for counters and total
            Node* previousPtr = NULL;
            Node* currentPtr = *headPtr;
            if (strcmpIgnoreCase((*headPtr)->data.organizationName, info.organizationName) == 0) {
                (*headPtr)->data = info;
            }
            else {
                while (currentPtr != NULL && strcmpIgnoreCase(currentPtr->data.organizationName, info.organizationName) != 0) {
                    previousPtr = currentPtr;
                    currentPtr = currentPtr->next;
                }
                previousPtr->next->data = info;
            }
        }
    } // while
    
    // deallocate memory for all the organizations
    deallocate(headPtr);
}

// function to insert organization into linked list
void insertOrganization(Node** headPtr, struct Organization *info){
    Node* newNodePtr = malloc(sizeof(Node));
    if (newNodePtr != NULL) {
        newNodePtr->data = *info;
        newNodePtr->next = NULL;
        Node* previousPtr = NULL;
        Node* currentPtr = *headPtr;
        // checks for alphabetical order using strcmpIgnoreCase
        while (currentPtr != NULL && strcmpIgnoreCase(currentPtr->data.organizationName, info->organizationName) <= 0) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        if (previousPtr == NULL) {
            *headPtr = newNodePtr;
        }
        else {
            previousPtr->next = newNodePtr;
        }
        newNodePtr->next = currentPtr;
    }
    else {
        printf("No memory to create node for %s\n", info->organizationName);
    }
}

void displayOrganizations(Node* headPtr) {
    puts("\n---------------\nAvailable races\n---------------\nOrganization\t\tDistance\t\tCost\t\tPercentage\n");
    Node *currentPtr = headPtr;
    while (currentPtr != NULL) {
        // display and go to next node
        printf("%s\t\t\t%.0lf miles\t\t$%.2lf\t\t%.0lf%%\n", currentPtr->data.organizationName, currentPtr->data.raceDistance, currentPtr->data.raceCost, currentPtr->data.charityPercent);
        currentPtr = currentPtr->next;
    }
}

void summaryAndFile(Node* headPtr) {
    Node *currentPtr = headPtr;
    unsigned int counter = 1;
    while (currentPtr != NULL) {
        char filePath[BUFF] = FILE_PATH;
        char fileName[BUFF];
        // sprintf function makes it so i can save a formatted string to a variable
        sprintf(fileName, "org%i.txt", counter);
        counter++;
        // strcat appends the file path (which is set to the constant), with the file name,
        strcat(filePath, fileName);
    
        // used sprintf again to save the summary into a variable, since its such a big string I had to set a large buffer size
        char summary[250];
        sprintf(summary, "Organization: %s\nDistance: %.0lf miles\nRace Cost: $%.2lf\nRegistrants: %i\nTotal Race Sales: $%.2lf\nJersey Cost: $%.2lf\nJerseys Sold: %i\nTotal Jersey Sales: $%.2lf\nTotal Sales: $%.2lf\nCharity Percent: %.0lf%%\nCharity Amount: $%.2lf\n\n", currentPtr->data.organizationName, currentPtr->data.raceDistance, currentPtr->data.raceCost, currentPtr->data.registrants, (currentPtr->data.registrants*currentPtr->data.raceCost), currentPtr->data.jerseyCost, currentPtr->data.jerseys, (currentPtr->data.jerseys*currentPtr->data.jerseyCost), currentPtr->data.totalCost, currentPtr->data.charityPercent, (currentPtr->data.charityPercent/100*currentPtr->data.totalCost));
        
        // prints the summary to the console
        printf("%s", summary);
        
        // prints summary to a file
        FILE *fp;
        fp = fopen(filePath, "w");
        fprintf(fp, "%s", summary);
        
        // close file
        fclose(fp);
        
        // move currentPtr over
        currentPtr = currentPtr->next;
    }
}

// prompts for admin pin and repeats until valid pin is entered (in 3 or less attempts)
unsigned int getValidPin() {
    unsigned int attempts = 0; // counter for password attempts
    char entry[BUFF]; // declaration for entry
    while (strcmp(entry, PIN) != 0 && attempts <= ATTEMPTS) {
        puts("Enter admin pin to continue:");
        fgetsRemoveNewLine(entry);
        // checks for valid password and ends while loop if entered
        if (strcmp(entry, PIN) != 0) {
            puts("Error: the password is incorrect\n");
            attempts++;
        }
    }
    return attempts;
}

// replicates the fgets function, and then runs strtok to remove the trailing new line character
void fgetsRemoveNewLine(char *str) {
    fgets(str, BUFF, stdin);
    strtok(str, "\n");
}

// function does string compare but ignores case
int strcmpIgnoreCase(char *s1, char *s2){
    // uses temporary variables so the name of the organization is not actually changed
    char temp1[BUFF];
    strcpy(temp1, s1);
    for(unsigned int i = 0; i < strlen(temp1); i++){
        temp1[i] = tolower(temp1[i]);
    }
    char temp2[BUFF];
    strcpy(temp2, s2);
    for(unsigned int i = 0; i < strlen(temp2); i++){
        temp2[i] = tolower(temp2[i]);
    }
    return strcmp(temp1, temp2);
}

void getValidDouble(double *dbl, int min, int max) {
    while(*dbl < min || max < *dbl) {
        char temp[BUFF]; // makes it so fgets can still be used for this input
        fgetsRemoveNewLine(temp);
        char *ptr; // needed for strtod function
        // converts the returned fgets value to a double
        *dbl = strtod(temp, &ptr);
        if(*dbl < min || max < *dbl){
            printf("Error: Enter a value from %d to %d\nTry again:\n", min, max);
        }
    }
}

char getValidChar(char prompt[], const char *str[], int size) {
    char input = '\0';
    bool exit = false;
    while(!exit){
        input = tolower(getchar());
        for(unsigned int i = 0; i < size; i++){
            char value = str[i][1];
            if(input == value){
                exit = true;
            }
        }
        if(exit == false){
            puts(prompt);
            // clear getchar() buffer so it works next time around
            while ((getchar()) != '\n');
        }
    }
    // clear getchar()
    while ((getchar()) != '\n');
    return input;
}

// method moves through linked list and deallocates all of it
void deallocate(Node** headPtr) {
    puts("Organizations removed from memory before exiting program");
    
    Node* currentPtr = *headPtr;
    Node* nextNodePtr = NULL;
    
    while (currentPtr != NULL) {
        nextNodePtr = currentPtr->next;
        free(currentPtr);
        currentPtr = nextNodePtr;
    }

    *headPtr = NULL;
}
