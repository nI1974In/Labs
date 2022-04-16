#ifndef _UDT_H_
#define _UDT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {

	int size;
	int* deck;
	int front;
	int back;
} udt;

void udt_create(udt* x);
bool udt_is_empty(const udt* x);

void udt_push_front(udt* x, int a);
void udt_push_back(udt* x, int a);

void udt_pop_front(udt* x);
void udt_pop_back(udt* x);

void udt_print(const udt* x);
size_t udt_size(const udt* x);

#endif

