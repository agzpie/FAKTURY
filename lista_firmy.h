#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef _STRUCTURES_
#define _STRUCTURES_
#include "structures.h"
#endif
//https://stackoverflow.com/questions/5430019/redefinition-errors-in-h-files

typedef struct node_firmy firmy;

void firmy_push_last(firmy *head_node, zamowienie value);

void firmy_push_first(firmy *head_node, zamowienie value);

zamowienie firmy_pop_last(firmy *head_node);

zamowienie firmy_pop_first(firmy *head_node);

void firmy_clean(firmy *head_node);

void firmy_printall(firmy *head_node);
