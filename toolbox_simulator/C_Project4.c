/*
This program will read in a file of one kit and then store the 
data of all parts inside that kit.

Part Data consists of -> (1) Part Description; (2) Qty of Parts; and
(3) Cost Per One Quantity.

After getting all the parts with their corresponding data, the program
shall store that data in a linked list for reading and future operations
as required. 

Then the program shall also compute the total cost of one kit.

Then the program shall print all data listed above in the terminal.

Program Name: Linked Lists, Files, Structures, and Pointers (OH MY!!!!), Project 4
System: Microsoft Visual Studio Community 2015, Windows 10
@author: TAK'S JOSEPH REFUGIO
@version: April 25, 2017
*/
// HEADER DECLARATION
#include <stdio.h>
#include <stdlib.h>
#include "myHeader.h"


// FUNCTION PROTOTYPES
void PrintKit(Kit*);
void ReadData_singlePart(FILE*inFile, char*, int*thisInt, double*thisDouble);

int main()
{
	Kit *myKit;
	myKit = (Kit*)malloc(sizeof(Kit));

	// Declaring Filename
	FILE* inFile;
	inFile = fopen("myFile.txt", "r");

	// Error message is printed when program cannot open or find the file
	if (inFile == NULL) printf("Cannot Open File.\n");

	myKit = ReadAKit(inFile);

	PrintKit(myKit);
	return 0;
}
// Reads one set of Data from a file
void ReadData_singlePart(FILE* inFile, char*thisString, int*thisInt, double*thisDouble)
{
	fgets(thisString, 500, inFile);
	fscanf(inFile, "%d %lf ", &*thisInt, &*thisDouble);;
}

// This function prints the contents of one kit
void PrintKit(Kit*thisKit)
{
	// Initializes the head part
	Part* headPart;
	headPart = (Part*)malloc(sizeof(Part));
	headPart = thisKit->firstPart;

	// Prints the Kit Name
	printf("%s", thisKit->kitName);

	// Prints the data corresponding to a given part
	while (headPart != NULL)
	{
		PrintParts(headPart);
		headPart = headPart->nextPart;
	}

	printf("Kit Cost is: $%lf\n", thisKit->kitCost);

}