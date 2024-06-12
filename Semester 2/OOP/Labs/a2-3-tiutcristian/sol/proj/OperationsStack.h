#pragma once
#include "domain.h"
#include "DynamicArray.h"
#include <string.h>

typedef struct
{
	Offer* offer;
	char* operationType;
} Operation;

Operation* createOperation(Offer* p, char* operationType);
void destroyOperation(Operation* o);
Operation* copyOperation(Operation* o);
char* getOperationType(Operation* o);
Offer* getOffer(Operation* o);

// ---------------------------------------------------------------
typedef struct
{
	DynamicArray* stack;
} OperationsStack;

OperationsStack* createStack();
void destroyStack(OperationsStack* s);
void push(OperationsStack* s, Operation* o);
Operation* pop(OperationsStack* s);
int isEmpty(OperationsStack* s);
void clearStack(OperationsStack* s);

void testsStack();