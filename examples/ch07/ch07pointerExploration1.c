/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
    int *houseNumPtr = &houseNum; // houseNumPtr points to address of houseNum
	
	printf("houseNum %d\n", houseNum); // prints houseNum value (13)

	printf("&houseNum %p\n\n", &houseNum); // prints address of houseNum

	printf ("*houseNumPtr  %d\n", *houseNumPtr); // points to adress of houseNum to return its value (13)

	printf ("houseNumPtr %p\n\n", houseNumPtr); // without * symbol, prints the address of houseNum

	printf ("&houseNumPtr %p\n\n", &houseNumPtr); // prints address of houseNum

	calcHouseNum1 =  *houseNumPtr + *houseNumPtr; // sets calcHouseNum1 to houseNum * houseNum (13 * 13 = 26)

	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1); // prints calcHouseNum1 value (26)

	calcHouseNum2 = 2 * (*houseNumPtr); // sets calcHouseNum2 to 2 * houseNum (2 * 13 = 26)

	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2); // prints calcHouseNum2 value (26)

	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr); // prints the address of houseNum for both values
			
	return 0;
}
