// Carson Jenkins
// 09/21/22
// Homework 3

#include <stdio.h>

// swappable constants for different values
#define MIN_COST 50 // minimum charge
#define MAX_COST 80 // maximum charge
#define MIN_HRS_CHRGD 3 // minimum hours charged for
#define MAX_HRS 10 // max hours to rent for
#define MIN_HRS 0 // min hours to rent for
#define ADD_CHARGE 8 // additional charge for each hour after 2

// function prototypes
void getValidInput(void);
double calculateCharge(double x, double y);
void displaySummary(double input, unsigned int boardCount, float hourCount, float chargeCount);

int main(void) {
    getValidInput();
}

// checks for valid input
void getValidInput(void){
    double input = 0;
    double charge = 0;
    unsigned int boardCount = 0;
    float hourCount = 0;
    float chargeCount = 0;
    
    do{
        // prompts user for hours
        printf("Enter the number of hours the board was rented or enter -1 to quit.\n");
        // checks for user entering a character
        if((scanf("%lf", &input)) == 1){
            // checks for input inside minimum and maximum amount of hours allowed
            if(input > MIN_HRS && input <= MAX_HRS){
                if(input <= MIN_HRS_CHRGD){
                    charge = MIN_COST;
                }
                else{
                    double num = input - MIN_HRS_CHRGD;
                    // checks for decimal remainder to count as another hour over the minimum hours
                    if(calculateCharge(num, 1) == 0){
                        charge = MIN_COST + (num * ADD_CHARGE);
                    }
                    else{
                        // calculates proper amount for values with decimals
                        charge = MIN_COST + ((num - (calculateCharge(num, 1)) + 1) * ADD_CHARGE);
                    }
                }
                
                // sets charge to MAXCOST if charge exceeds MAXCOST
                if(charge > MAX_COST){
                    charge = MAX_COST;
                }
                
                // keeping counters for displaying totals
                boardCount++;
                hourCount = hourCount + input;
                chargeCount = chargeCount + charge;
                
                printf("    Board   Hours   Charge\n    %d       %.2lf    $%.2lf\n\n", boardCount, input, charge);
            } // if
            else{
                displaySummary(input, boardCount, hourCount, chargeCount);
            } // if-else
        }
        else{
            while ((getchar()) != '\n');
            printf("    Error: The number of hours must be greater than %d and not more than %d hours.\n\n", MIN_HRS, MAX_HRS);
        }
    } while(input != -1); // do while ends program when user enters -1
}

// calculates modulus with doubles, so I can check for decimals and can calculate them as an additional hourly charge
double calculateCharge(double x, double y){
    return x - (int)(x/y) * y;
}

// displays summary of boards throughout the day
void displaySummary(double input, unsigned int boardCount, float hourCount, float chargeCount){
    // prints totals when user enters -1
    if(input == -1){
        printf("    Total for the day\n");
        if(boardCount == 0){
            printf("    No boards were rented today.\n\n");
        }
        else{
            printf("    Boards   Total Hours   Total Charge\n    %d        %.2f          $%.2f\n\n", boardCount, hourCount, chargeCount);
        }
    }
    // prints the error otherwise
    else{
        printf("    Error: The number of hours must be greater than %d and not more than %d hours.\n\n", MIN_HRS, MAX_HRS);
    }
}

// function allows modulus with doubles, so I can check for decimals so that they will count as an additional hourly charge
double mod(double x, double y) {
    return x - (int)(x/y) * y;
}
