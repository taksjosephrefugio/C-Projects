#include <stdio.h>
#include <stdlib.h>
#include "myHeader.h"

// This function computes for the cost of one kit
double kitCost(Kit *thisKit)
{
	// Declaring the return variable
	double temp = 0.0;

	// Declaring the part traverser
	Part* headPart;
	headPart = thisKit->firstPart;

	// Goes through all the parts in one kit and calculates the cost of a kit
	while (headPart != NULL)
	{
		temp = (headPart->costPerItem * headPart->qtyPerKit) + temp;
		headPart = headPart->nextPart;
	}

	return temp;
}