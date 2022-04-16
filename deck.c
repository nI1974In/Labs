#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Deck.h"

void udt_create(udt* x) {

	x->size = 0;
	x->deck = (int*)calloc(10, sizeof(int));

	x->front = 0;
	x->back = 0;
}

bool udt_is_empty(const udt* x) {

	if (x->size > 0) {
		return false;
	}
	else {
		return true;
	}
}

void udt_push_front(udt* x, int a) {

	if ((x->size / 10 > 0) && (x->size % 10 == 0))
	{

		int* tmp = (int*)realloc(x->deck, (x->size + 10) * sizeof(int));

		if (tmp == NULL) {

			printf("\nRealloc error. Element %d didn't pushed in deck", a);
			return;
		}

		x->deck = tmp;
	}

	x->deck[x->size] = a;
	x->front = a;

	if (x->size == 0) { x->back = a; }

	x->size++;
}

void udt_push_back(udt* x, int a) {

	if ((x->size / 10 > 0) && (x->size % 10 == 0))
	{

		int* tmp = (int*)realloc(x->deck, (x->size + 10) * sizeof(int));

		if (tmp == NULL) {

			printf("Realloc error. Element %d didn't pushed in deck", a);
			return;
		}

		x->deck = tmp;
	}

	for (int i = 0; i < x->size; i++)
	{
		x->deck[x->size - i] = x->deck[x->size - (i + 1)];
	}

	x->deck[0] = a;
	x->back = a;

	if (x->size == 0) { x->front = a; }

	x->size++;
}

void udt_pop_front(udt* x) {

	if (x->size == 0)
	{
		printf("\nDeck already empty");
		return;
	}

	x->size--;

	if (x->size == 0)
	{
		x->front = 0;
		x->back = 0;
	}
	else
	{
		x->front = x->deck[x->size - 1];
	}
}

void udt_pop_back(udt* x) {

	if (x->size == 0)
	{
		printf("\nDeck already empty");
		return;
	}

	x->size--;

	if (x->size == 0)
	{
		x->front = 0;
		x->back = 0;
	}
	else
	{
		for (int i = 0; i < x->size; ++i) {

			x->deck[i] = x->deck[i + 1];
		}

		x->back = x->deck[0];
	}
}

void udt_print(const udt* x) {

	if (x->size == 0)
	{
		printf("\nDeck is empty");
		return;
	}

	printf("	< %d", x->deck[0]);

	for (int i = 1; i < x->size; ++i)
	{
		printf(", %d", x->deck[i]);
	}

	printf(" >	\n\n");
}

size_t udt_size(const udt* x) {

	return x->size;
}