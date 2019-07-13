#include <stdio.h>
#include <stdlib.h>
#include "myHeader.h"

// This function prints the details of one part
void PrintParts(Part*thisPart)
{
	printf("%s%d %lf\n", thisPart->description, thisPart->qtyPerKit, thisPart->costPerItem);
}