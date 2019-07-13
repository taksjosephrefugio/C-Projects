// STRUCTURE DEFINITIONS
typedef struct Node_struct {
	int data;
	struct Node* next;
}Node;

typedef struct Part {
	char *description;
	int qtyPerKit;
	double costPerItem;
	struct Part *nextPart;
} Part;

typedef struct Kit {
	char *kitName;
	struct part *firstPart;
	double kitCost;
	struct kit *nextKit;
}Kit;

// FUNCTION PROTOTYPES
void ReadData_singlePart(FILE*inFile, char*, int*thisInt, double*thisDouble);
Part* ReadAPart(FILE*, Part*);
Kit* ReadAKit(FILE*);
double kitCost(Kit*);
void PrintParts(Part*);
void PrintKit(Kit*);