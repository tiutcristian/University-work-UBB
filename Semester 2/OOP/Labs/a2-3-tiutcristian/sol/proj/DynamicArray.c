#include "DynamicArray.h"
#include "domain.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

DynamicArray* createDynamicArray(int capacity, DestroyFunctionType destroyFct)
{
	DynamicArray* da = malloc(sizeof(DynamicArray));
	// make sure that the space was allocated
	if (da == NULL)
		return NULL;

	da->capacity = capacity;
	da->length = 0;

	// allocate space for the elements
	da->elems = malloc(capacity * sizeof(TElement));
	if (da->elems == NULL)
	{
		free(da);
		return NULL;
	}
	da->destroyFct = destroyFct;

	return da;
}

void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	// considering that the dynamic array takes responsibility of all the elements, it will have to deallocate the memory for these
	for (int i = 0; i < arr->length; i++)
		arr->destroyFct(arr->elems[i]);
	
	// free the space allocated for the elements
	free(arr->elems);
	//arr->elems = NULL;

	// free the space allocated for the dynamic array
	free(arr);
}

// Resizes the array, allocating more space.
// If more space cannot be allocated, returns -1, else it returns 0.
int resize(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;

	arr->capacity *= 2;

	TElement* aux = realloc(arr->elems, arr->capacity * sizeof(TElement));
	if (aux == NULL)
		return -1;
	arr->elems = aux;
	return 0;
}

void addElement(DynamicArray* arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;

	if (arr->length == arr->capacity)
		resize(arr);
	arr->elems[arr->length++] = t;
}

void deleteElement(DynamicArray* arr, int pos)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;
	arr->destroyFct(arr->elems[pos]);
	arr->elems[pos] = arr->elems[--arr->length];
}

int getLength(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;
	return arr->length;
}

TElement get(DynamicArray* arr, int pos)
{
	if (arr == NULL)
		return NULL;
	if (pos < 0 || pos >= arr->length)
		return NULL;
	return arr->elems[pos];
}

void set(DynamicArray* arr, int pos, TElement t)
{
	if (arr == NULL)
		return;
	if (pos < 0 || pos >= arr->length)
		return;
	arr->elems[pos] = t;
}

// ------------------------------------------------------------------------------------------------------------
// Tests

void testsDynamicArray()
{
	DynamicArray* da = createDynamicArray(2, &destroyOffer);
	if (da == NULL)
		assert(0);

	assert(da->capacity == 2);
	assert(da->length == 0);

	Offer* p1 = createOffer("seaside", "Mamaia", 1, 1, 2024, 100);
	addElement(da, p1);
	assert(da->length == 1);

	Offer* p2 = createOffer("mountain", "Zell am See", 2, 3, 2024, 200);
	addElement(da, p2);
	assert(da->length == 2);

	Offer* p3 = createOffer("city break", "Paris", 4, 5, 2025, 300);
	addElement(da, p3);
	assert(da->length == 3);
	assert(da->capacity == 4);

	Offer* p = (Offer*)get(da, 0);
	assert(strcmp(getDestination(p), "Mamaia") == 0);

	deleteElement(da, 0);
	
	destroy(da);
}