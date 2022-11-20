#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 25

int main(int argc, const char * argv[]) {
    // 1.1 Login
    char pin[SIZE]; // declaration for pin
    unsigned int attempts = 0; // counter for password attempts
    while (strncmp(pin, "B!k34u", 6) != 0 && attempts <= 3) {
        puts("Enter admin pin to set up race information:");
        fgets(pin, SIZE, stdin);
        // checks for valid password and ends while loop if entered
        if (strncmp(pin, "B!k34u", 6) != 0) {
            printf("Error: the password is incorrect\n\n");
            attempts++;
        }
    }
    if(attempts <= 3){
        puts("\nSet up the fundraising information for the organization:");
    }
    else {
        puts("Exiting admin set-up");
    }
    
    
    // 1.2 Organization Name
    char orgName[SIZE]; // declaration for organization name
    puts("Enter fundraising organizations name:");
    fgets(orgName, SIZE, stdin);
    
    
    // 1.3 Ride Distance
    int distance = 0;
    while(distance < 1 || 200 < distance) {
        puts("\nEnter distance in miles for the bike course:");
        scanf("%d", &distance);
        if(distance < 1 || 200 < distance){
            puts("Error: Enter a value from 1 to 200");
        }
    }
    
    
    // 1.4 Ride Cost
    int ride = 0;
    while(ride < 50 || 200 < ride) {
        printf("\nEnter the registration cost of the bike ride for %s", orgName);
        scanf("%d", &ride);
        if(ride < 50 || 200 < ride){
            puts("Error: Enter a value from 50 to 200");
        }
    }
    printf("The bike race cost is $%d\n", ride);
    
    
    // 1.5 Jersey Cost
    int jersey = 0;
    while(jersey < 50 || 150 < jersey) {
        printf("\nEnter sales price of jersey for %s", orgName);
        scanf("%d", &jersey);
        if(jersey < 50 || 150 < jersey){
            puts("Error: Enter a value from 50 to 150");
        }
    }
    printf("The bike jersey cost is $%d\n", jersey);
    
    
    // 1.6 Charity Percentage
    int charity = 0;
    while(charity < 5 || 30 < charity) {
        printf("\nEnter percentage of the bike race sales that will be donated to %s", orgName);
        scanf("%d", &charity);
        if(charity < 5 || 30 < charity){
            puts("Error: Enter a value from 5 to 30");
        }
    }
    printf("You entered %d%% of the bike race to go to charity\n\n", charity);
    
    
    // 2.1 Registration
    char input[SIZE];
    puts("Enter your first name and last name to register for the ride:");
    fgets(input, SIZE, stdin);
    char name[SIZE];
    puts("Enter your first name and last name to register for the ride:");
    fgets(name, SIZE, stdin);
    
    
    // 2.2 Jersey Selection
    char purchaseJersey = '\0';
    int exit = 1;
    while(exit != 0) {
        printf("\nDo you want to purchase a jersey for $%d?\n", jersey);
        purchaseJersey = getchar();
        
        // clear getchar() buffer so it works for size selection
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        if(purchaseJersey == 'y' || purchaseJersey == 'Y'){
            char size = '\0';
            while(exit != 0) {
                puts("\nEnter your size (s)mall, (m)edium, (l)arge, or (x)large:");
                size = getchar();
                if(size == 's' || size == 'S' || size == 'm' || size == 'M' || size == 'l' || size == 'L' || size == 'x' || size == 'X') {
                    exit = 0;
                }
            }
        }
        else if(purchaseJersey == 'n' || purchaseJersey == 'N'){
            // do nothing to continue to payment, while allowing the else statement to still work right
            exit = 0;
        }
        else {
            puts("Please enter y or n");
        }
    }
    
    
    // 2.3 Payment
    int total;
    if(purchaseJersey == 'y' || purchaseJersey == 'Y'){
        total = jersey + ride;
    }
    else{
        total = ride;
    }
    char creditCard[14];
    int exitt = 1;
    double charityAmt = total * (charity/100);
    while(exitt != 0){
        printf("\nYour total cost is %d. Enter your credit card\n", total);
        fgets(creditCard, SIZE, stdin);
        if(isdigit(creditCard[0]) && isdigit(creditCard[1]) && isdigit(creditCard[2]) && isdigit(creditCard[3]) && isalpha(creditCard[4]) && isalpha(creditCard[5]) && isalpha(creditCard[6]) && isalpha(creditCard[7]) && isalpha(creditCard[8]) && isalpha(creditCard[9]) && isalpha(creditCard[10]) && isalpha(creditCard[11]) && isalpha(creditCard[12])){
            printf("\nThank you %s for your purchase. %lf of the ticket sales will go to charity.", name, charityAmt);
            exitt = 0;
        }
    }
    
    
    // 2.4 Receipt
    char receipt = '\0';
    int exittt = 1;
    while(exittt != 0) {
        puts("\nDo you want a receipt (y)es or (n)o?\n");
        receipt = getchar();
        
        // clear getchar() buffer so it works for size selection
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        if(receipt == 'y' || receipt == 'Y'){
            printf("Race    $%d\n", ride);
            printf("Jersey    $%d\n", jersey);
            printf("Total Cost: $%d\n", total);
            printf("Donation to Charity: $%lf\n", charityAmt);
            exittt = 0;
        }
        else if(receipt == 'n' || receipt == 'N'){
            exittt = 0;
        }
        else {
            puts("Please enter y or n");
        }
    }
    
    
    return 0;
}
