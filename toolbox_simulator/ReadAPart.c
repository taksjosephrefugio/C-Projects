#include <stdio.h>
#include <stdlib.h>
#include "myHeader.h"

// Reading in values for a single part
Part* ReadAPart(FILE* inFile, Part*headPart)
{
	// Initializing definitions for the return value
	Part*newNode;
	newNode = (Part*)malloc(sizeof(Part));

	// Initializing Temporary Variables
	int tempInt; double tempDouble; char*tempString;
	tempString = (char*)malloc(sizeof(char) * 500);

	// Reading in the data from textfile
	ReadData_singlePart(inFile, tempString, &tempInt, &tempDouble);

	newNode->description = tempString;
	newNode->qtyPerKit = tempInt;
	newNode->costPerItem = tempDouble;
	newNode->nextPart = headPart;
	return newNode;
}