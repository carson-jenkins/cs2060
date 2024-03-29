// Fig. 2.1: fig02_01.c
// A first program in C 
#include <stdio.h>

// function main begins program execution 
int main( void )
{
    // declare and initialize 3 integers called length, width, and area
    int length = 0;
    int width = 0;
    int area = 0;
    int difference = 0;
    
    printf( "Welcome to C!\n" );
    
    // prompts user to enter length
    printf("\nEnter the length: ");
    scanf("%d", &length);

    // prompts user to enter width
    printf("Enter the width: ");
    scanf("%d", &width);
    
    // calculates area
    area = length * width;
    
    // displays all the information
    printf("\nLength: %d\n", length);
    printf("Width: %d\n", width);
    printf("Area: %d\n", area);
    
    
    difference = length/width;
    printf("Length/Width = %d\n\n", difference);
    
    return 0;
} // end function main


/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
