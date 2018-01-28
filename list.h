#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef _STRUCTURES_
#define _STRUCTURES_
#include "structures.h"
#endif

typedef struct node thunderstruct;

void push_last(thunderstruct *head_node, zamowienie value);

void push_first(thunderstruct *head_node, zamowienie value);

zamowienie pop_last(thunderstruct *head_node);

zamowienie pop_first(thunderstruct *head_node);

void clean(thunderstruct *head_node);

void printall(thunderstruct *head_node);
