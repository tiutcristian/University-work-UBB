#include "OperationsStack.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <crtdbg.h>
#include <stdio.h>

Operation* createOperation(Offer* p, char* operationType)
{
	Operation* o = malloc(sizeof(Operation));
	o->offer = copyOffer(p);
	o->operationType = malloc(sizeof(char) * (strlen(operationType) + 1));
	strcpy(o->operationType, operationType);

	return o;
}

void destroyOperation(Operation* o)
{
	if (o == NULL)
		return;
	destroyOffer(o->offer);
	free(o->operationType);
	free(o);
}

Operation* copyOperation(Operation * o)
{
	Operation* copy = createOperation(getOffer(o), getOperationType(o));
	return copy;
}

char* getOperationType(Operation* o)
{
	return o->operationType;
}

Offer* getOffer(Operation* o)
{
	return o->offer;
}

// ---------------------------------------------------------------

OperationsStack* createStack()
{
	OperationsStack* s = malloc(sizeof(OperationsStack));
	if (s == NULL)
		return NULL;
	s->stack = createDynamicArray(CAPACITY, &destroyOperation);
	if (s->stack == NULL)
	{
		free(s);
		return NULL;
	}

	return s;
}

void destroyStack(OperationsStack* s)
{
	if (s == NULL)
		return;
	destroy(s->stack);
	free(s);
}

void push(OperationsStack* s, Operation* o)
{
	if (s == NULL || o == NULL)
		return;
	addElement(s->stack, o);
}

Operation* pop(OperationsStack* s)
{
	if (s == NULL)
		return NULL;
	int lastPos = getLength(s->stack) - 1;
	Operation* o = (Operation*)get(s->stack, lastPos);
	Operation* lastOp = copyOperation(o);
	deleteElement(s->stack, lastPos);
	return lastOp;
}

int isEmpty(OperationsStack* s)
{
	if (s == NULL)
		return 1;
	return (getLength(s->stack) == 0);
}

void clearStack(OperationsStack* s)
{
	if (s == NULL)
		return;
	destroy(s->stack);
	s->stack = createDynamicArray(CAPACITY, &destroyOperation);
}


// Tests
void testsStack()
{
	OperationsStack* s = createStack();
	assert(isEmpty(s) == 1);

	Offer* p1 = createOffer("seaside", "Mamaia", 1, 2, 2025, 100);
	Offer* p2 = createOffer("mountain", "Busteni", 1, 2, 2025, 100);

	Operation* o1 = createOperation(p1, "add");
	Operation* o2 = createOperation(p2, "add");
	Operation* o3 = createOperation(p1, "remove");

	destroyOffer(p1);
	destroyOffer(p2);

	push(s, o1);
	push(s, o2);
	push(s, o3);

	assert(isEmpty(s) == 0);

	Operation* o = pop(s);
	assert(strcmp(o->operationType, "remove") == 0);
	destroyOperation(o);

	o = pop(s);
	assert(strcmp(o->operationType, "add") == 0);
	destroyOperation(o);

	o = pop(s);
	assert(strcmp(o->operationType, "add") == 0);
	destroyOperation(o);

	assert(isEmpty(s) == 1);

	destroyStack(s);
}