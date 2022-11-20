#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// global constants
#define BUFF 80
#define DISTANCE_MAX 200
#define DISTANCE_MIN 1
#define COST_MAX 200
#define COST_MIN 50
const char *SIZES[4] = {"(s)mall", "(m)edium", "(l)arge", "(x)tra-large"};

void fgetsRemoveNewLine(char *str);
void adminSetUp(void);
void getValidDouble(double *dbl, int min, int max);
char getValidChar(char prompt[], const char *input[], int inputSize);

int main(int argc, const char * argv[]) {
    
    adminSetUp();
    
    return 0;
}

// Replicates the fgets function, and then runs strtok to remove the trailing new line character
void fgetsRemoveNewLine(char *str){
    fgets(str, BUFF, stdin);
    // this strategy works except when a user hits enter right away without entering anything else, which shouldn't be an issue for this problem
    strtok(str, "\n");
}

void adminSetUp(void){
    char organizationName[BUFF]; // declaration for organization name
    double raceDistance;
    double raceCost;
    
    puts("Enter fundraising organizations name:");
    fgetsRemoveNewLine(organizationName);
    
    puts("\nEnter race distance:");
    getValidDouble(&raceDistance, DISTANCE_MIN, DISTANCE_MAX);

    puts("\nEnter race cost:");
    getValidDouble(&raceCost, COST_MIN, COST_MAX);
    
    getValidChar("\nSelect your shirt size by entering the character in parenthesis: (s)mall (m)edium (l)arge (x)tra-large", SIZES, 4); // get jersery size
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

char getValidChar(char prompt[], const char *input[], int inputSize){
    char in = '\0';
    
    bool exit = false;
    while(!exit){
        puts(prompt);
        in = tolower(getchar());
        
        for(unsigned int i = 0; i < inputSize; i++){
            char value = input[i][1];
            if(in == value){
                exit = true;
            }
        }
        
        
        // clear getchar() buffer so it works for next time around
        while ((in = getchar()) != '\n' && in != EOF);
    }
    
    return in;
}
