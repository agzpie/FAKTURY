#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef _STRUCTURES_
#define _STRUCTURES_
#include "structures.h"
#endif
//https://stackoverflow.com/questions/5430019/redefinition-errors-in-h-files

typedef struct node_faktury faktury;

void faktury_push_last(faktury *head_node, faktura value);

void faktury_push_first(faktury *head_node, faktura value);

faktura faktury_pop_last(faktury *head_node);

faktura faktury_pop_first(faktury *head_node);

void faktury_clean(faktury *head_node);

void faktury_printall(faktury *head_node);
