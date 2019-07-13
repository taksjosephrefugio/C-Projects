#include <stdio.h>
#include <stdlib.h>
#include "myHeader.h"

// Reading in values for a single kit
Kit* ReadAKit(FILE*inFile)
{
	Kit *temp;
	temp = (Kit*)malloc(sizeof(Kit));

	// Storing first line as the kit title 
	char *tempString;
	tempString = (char*)malloc(sizeof(char) * 500);
	fgets(tempString, 500, inFile);

	// Declaring head part object
	Part *headPart = NULL;

	while (!feof(inFile))
	{
		headPart = ReadAPart(inFile, headPart);
	}
	temp->firstPart = headPart;
	temp->kitName = tempString;
	temp->nextKit = NULL;
	temp->kitCost = kitCost(temp);

	return temp;
}
