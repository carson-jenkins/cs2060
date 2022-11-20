// Passing Primitive Data Types and pointers
//Add comments to explain the code

#include <stdio.h>	
#include <stdlib.h>

// function prototypes
int cubePass1(int number);
int cubePass2(int * numberPtr);

int main(void) {

	int numberMain = 5;
	int result = 0;
	
	printf ("In main before cubePass1  numberMain = %d\n", numberMain); // prints numberMain (5)
	printf("&numberMain = %p\n", &numberMain); // prints address of numberMain
	result = cubePass1(numberMain); // sets result equal to cubePass1(numberMain)
	printf ("In main after cubePass1  numberMain = %d\n", numberMain); // prints numberMain (5)
	printf ("Result = %d\n", result); // prints result of cubePass1(numberMain) (125)
	printf("\nIn main before cubePass2  numberMain = %d\n", numberMain); // prints numberMain (5)
	result = cubePass2(&numberMain); // sets result equal to cubePass2(&numberMain)
	printf("\nIn main after cubePass2  numberMain = %d\n", numberMain); // prints numberMain (125)
	printf("result = %d\n", result); // prints result of cubePass2(&numberMain) (125)

} // main


int cubePass1 (int number) 
{
	int cube = 0;
	puts("\nIn cubePass1");
	printf("number = %d\n", number); // plugs in number and prints it (5)
	printf("&number = %p\n", &number); // prints address of number
	cube = number * number * number; // sets cube equal to number^3 (125)
	printf("cube  = %d\n", cube); // prints cube (125)
	number = cube; // sets number equal to cube
	printf("number = %d\n", number); // prints value number (125)
	return cube; // returns cube (125)
} 

int cubePass2 (int * numberPtr) 
{
    int cube = 0;
    puts ("\nIn cubePass2");
    printf("numberPtr = %p\n", numberPtr); // plugs in numberPtr and prints the address
    printf ("*numberPtr = %d\n", *numberPtr); // prints value numberPtr points to (5)
    printf("&numberPtr = %p\n", &numberPtr); // prints address numberPtr is pointing to
    cube = (* numberPtr )* (* numberPtr )* (* numberPtr);  // sets cube equal to numberPtr^3 (125)
    *numberPtr = cube; // sets numberPtr to cube (125)
    printf ("*numberPtr = %d\n", *numberPtr); // prints numberPtr (125)
    return cube; // returns cube (125)
}
