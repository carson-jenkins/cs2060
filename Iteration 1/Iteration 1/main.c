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
#define SEPERATOR "-------------------------------------------------------------------------" // for formatting
const char *SIZES[4] = {"(s)mall", "(m)edium", "(l)arge", "(x)tra-large"};
const char *CHOICE[2] = {"(y)es", "(n)o"};

struct Info {
    char organizationName[BUFF];
    double raceDistance;
    double raceCost;
    double jerseyCost;
    double charityPercent;
    double totalCost;
};

void adminSetUp(struct Info *info);
void registration(struct Info *info);
void fgetsRemoveNewLine(char *str);
void getValidDouble(double *dbl, int min, int max);
char getValidChar(char prompt[], const char *str[], int size);

int main(int argc, const char * argv[]) {
    struct Info info = {};
    adminSetUp(&info);
    // only runs registration if admin makes it past the pin and enters a distance for the race
    if(info.raceDistance != 0) {
        registration(&info);
    }
    return 0;
}

void adminSetUp(struct Info *info){
    char entry[BUFF]; // declaration for entry
    unsigned int attempts = 0; // counter for password attempts
    while (strcmp(entry, PIN) != 0 && attempts <= 3) {
        puts("Enter admin pin to set up race information:");
        fgetsRemoveNewLine(entry);
        // checks for valid password and ends while loop if entered
        if (strcmp(entry, PIN) != 0) {
            puts("Error: the password is incorrect\n");
            attempts++;
        }
    }
    
    if(attempts <= 3){
        printf("\n\nSet up the fundraising information for the organization\n%s\n\nEnter fundraising organizations name:\n", SEPERATOR);
        fgetsRemoveNewLine(info->organizationName);
        
        puts("\nEnter distance in miles for the bike course:");
        getValidDouble(&info->raceDistance, DISTANCE_MIN, DISTANCE_MAX);
        printf("The bike race distance is %.0lf miles\n", info->raceDistance);
        
        printf("\nEnter the registration cost of the bike ride for %s:\n", info->organizationName);
        getValidDouble(&info->raceCost, COST_MIN, COST_MAX);
        printf("The bike race cost is $%.2lf\n", info->raceCost);
        
        printf("\nEnter sales price of jersey for %s:\n", info->organizationName);
        getValidDouble(&info->jerseyCost, JERSEY_MIN, JERSEY_MAX);
        printf("The bike jersey cost is $%.2lf\n", info->jerseyCost);
        
        printf("\nEnter percentage of the bike race sales that will be donated to %s:\n", info->organizationName);
        getValidDouble(&info->charityPercent, CHARITY_MIN, CHARITY_MAX);
        printf("You entered %.0lf%% of the bike race to go to charity\n", info->charityPercent);
    }
    else {
        puts("Exiting admin set-up");
    }
}

void registration(struct Info *info){
    // counters for registrants and jersey purchases
    unsigned int registrants = 0;
    unsigned int jerseys = 0;
    
    char userName[BUFF];
    bool quit = false;
    
    while(!quit){
        // race variables update
        printf("\n\nYou can register for one of the following races and %.0lf%% will be raised for %s:\nRace\t\tDistance\t\tCost\n#1\t\t\t%.0lf miles\t\t$%.2lf\n\nYou can purchase a jersey for $%.2lf\n%s\n", info->charityPercent, info->organizationName, info->raceDistance, info->raceCost, info->jerseyCost, SEPERATOR);
        
        puts("\nEnter your first name and last name to register for the ride:");
        fgetsRemoveNewLine(userName);
        // converts first letter and first letter after a space as uppercase, rest lowercase
        for(unsigned int i = 1; i < strlen(userName); i++){
            userName[0] = toupper(userName[0]);
            if(isspace(userName[i-1])){
                userName[i] = toupper(userName[i]);
            }
            else{
                userName[i] = tolower(userName[i]);
            }
        }
        
        
        if(strcmp(userName, "Quit") == 0){
            char entry[BUFF]; // declaration for entry
            unsigned int attempts = 0; // counter for password attempts
            while (strcmp(entry, PIN) != 0 && attempts <= 3) {
                puts("Enter admin pin to quit:");
                fgetsRemoveNewLine(entry);
                // checks for valid password and ends while loop if entered
                if (strcmp(entry, PIN) != 0) {
                    puts("Error: the password is incorrect\n");
                    attempts++;
                }
                else{
                    // print summary
                    printf("\n\nSummary of race sales where %.0lf%% goes to charity:\nRace\t\tDistance\t\tCost\t\tRegistrants\t\tTotal Sales\t\tCharity Amount\n#1\t\t\t%.0lf miles\t\t$%.2lf\t\t%d\t\t\t\t$%.2lf\t\t\t$%.2lf\n\nJerseys Sold\t\tSales\t\tCharity\n%d\t\t\t\t\t$%.2lf\t\t$%.2lf\n\nTotal Sales: $%.2lf\nTotal Funds Raised for Charity: $%.2lf\n%s\n\n", info->charityPercent, info->raceDistance, info->raceCost, registrants, registrants*info->raceCost, (info->charityPercent/100)*(registrants*info->raceCost), jerseys, jerseys*info->jerseyCost, (info->charityPercent/100)*(jerseys*info->jerseyCost), info->totalCost, (info->charityPercent/100)*info->totalCost, SEPERATOR);
                    quit = true;
                }
            }
        }
        else {
            registrants++;
            info->totalCost = info->totalCost + info->raceCost;
            double localTotal = info->raceCost; // for printing certain totals throughout
            printf("\nDo you want to purchase a jersey for $%.2lf?\n", info->jerseyCost);
            if(getValidChar("Please enter y or n", CHOICE, 2) == 'y') {
                jerseys++;
                puts("\nSelect your shirt size by entering the character in parenthesis - (s)mall (m)edium (l)arge (x)tra-large:");
                // get jersery size
                getValidChar("Please enter s, m, l or x", SIZES, 4);
                info->totalCost = info->totalCost + info->jerseyCost;
                localTotal = localTotal + info->jerseyCost;
            }
            
            // validate credit card for number XXXX-####-#####
            char creditCard[BUFF] = {};
            while(!(isdigit(creditCard[0]) && isdigit(creditCard[1]) && isdigit(creditCard[2]) && isdigit(creditCard[3]) && creditCard[4] == '-' && isalpha(creditCard[5]) && isalpha(creditCard[6]) && isalpha(creditCard[7]) && isalpha(creditCard[8]) && creditCard[9] == '-' && isalpha(creditCard[10]) && isalpha(creditCard[11]) && isalpha(creditCard[12]) && isalpha(creditCard[13]) && isalpha(creditCard[14]))){
                printf("\nYour total cost is $%.2lf. Enter your credit card (####-XXXX-XXXXX):\n", localTotal);
                fgetsRemoveNewLine(creditCard);
            }
            printf("\nThank you %s for your purchase. $%.2lf of the ticket sales will go to charity\n", userName, (info->charityPercent/100)*localTotal);
        
            puts("\nDo you want a receipt (y)es or (n)o?");
            if(getValidChar("Please enter y or n", CHOICE, 2) == 'y') {
                // prints receipt
                printf("\nRace\t$%.2lf\nJersey\t$%.2lf\n\nTotal Cost: $%.2lf\nDonation to Charity: $%.2lf\n", info->raceCost, info->jerseyCost, localTotal, (info->charityPercent/100)*localTotal);
            }
        }
    } // while
}

// replicates the fgets function, and then runs strtok to remove the trailing new line character
void fgetsRemoveNewLine(char *str){
    fgets(str, BUFF, stdin);
    strtok(str, "\n");
}

void getValidDouble(double *dbl, int min, int max){
    while(*dbl < min || max < *dbl) {
        char temp[BUFF]; // makes it so fgets can still be used for this input
        fgetsRemoveNewLine(temp);
        char *ptr; // needed for strtod function
        *dbl = strtod(temp, &ptr); // converts the returned fgets value to a double
        if(*dbl < min || max < *dbl){
            printf("Error: Enter a value from %d to %d\nTry again:\n", min, max);
        }
    }
}

char getValidChar(char prompt[], const char *str[], int size){
    char in = '\0';
    
    bool exit = false;
    while(!exit){
        
        in = tolower(getchar());
        
        for(unsigned int i = 0; i < size; i++){
            char value = str[i][1];
            if(in == value){
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
    
    return in;
}
