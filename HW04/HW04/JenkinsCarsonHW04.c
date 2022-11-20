#include <stdio.h>

// Constants
#define STUDENTS 2
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final "
const double GRADE_CATEGORY_WEIGHT[] = {0.1, 0.3, 0.3, 0.15, .15};

// Fucntion prototypes
void getInput(int result[STUDENTS][GRADE_CATEGORIES]);
void displayGrades(int result[STUDENTS][GRADE_CATEGORIES]);
void finalDisplay(int result[STUDENTS][GRADE_CATEGORIES]);

int main(int argc, const char * argv[]) {
    int result[STUDENTS][GRADE_CATEGORIES];
    getInput(result);
    displayGrades(result);
    finalDisplay(result);
    return 0;
}

void getInput(int result[STUDENTS][GRADE_CATEGORIES]){

    printf("This program will calculate the grades for these categories %s\nThe category weights are\n", CATEGORIES);
    for(int i = 0; i < GRADE_CATEGORIES; i++){
        printf("Category %d weight is %.2f\n", i+1, GRADE_CATEGORY_WEIGHT[i]);
    }
    printf("\nThe correct order to enter grades for each student is: %s\n\n", CATEGORIES);

    for(int i = 0; i < STUDENTS; i++){
        for(int j = 0; j < GRADE_CATEGORIES; j++){
            printf("Enter the grade for each category for student %d, category %d: ", i+1, j+1);
            scanf("%d\n", &result[i][j]);
        }
        printf("\n"); // add space between each student
    }
}

// Displays grades entered
void displayGrades(int result[STUDENTS][GRADE_CATEGORIES]){
    printf("Grades entered for each student\n");
    for (int i = 0; i < STUDENTS; i++) {
        printf("Student %d: ", i+1);
        for (int j = 0; j < GRADE_CATEGORIES; j++) {
            printf("%d  ", result[i][j]);
        }
        printf("\n");
    }
}

void finalDisplay(int result[STUDENTS][GRADE_CATEGORIES]){
    float finalGrades[STUDENTS] = {0};
    float classAverage = 0;
    
    // Displays final grades
    printf("\nFinal grades for students, respectively:");
    for (int i = 0; i < STUDENTS; i++) {
        for (int j = 0; j < GRADE_CATEGORIES; j++) {
            finalGrades[i] += result[i][j];
        }
        
        char letterGrade;
        float averageGrade = finalGrades[i]/GRADE_CATEGORIES;
        
        // Grading scale
        if(averageGrade >= 90){
            letterGrade = 'A';
        }
        else if(averageGrade >= 80){
            letterGrade = 'B';
        }
        else if(averageGrade >= 70){
            letterGrade = 'C';
        }
        else if(averageGrade >= 60){
            letterGrade = 'D';
        }
        else{
            letterGrade = 'F';
        }
        
        printf("\nStudent %d: %.1f  %c", i+1, averageGrade, letterGrade);
        classAverage += averageGrade;
    }
    // Displays class average
    printf("\n\nClass average is %.1f\n\n", classAverage/STUDENTS);
}
