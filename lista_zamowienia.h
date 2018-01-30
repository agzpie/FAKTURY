#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef _STRUCTURES_
#define _STRUCTURES_
#include "structures.h"
#endif
//https://stackoverflow.com/questions/5430019/redefinition-errors-in-h-files

typedef struct node_zamowienia zamowienia;

void zamowienia_push_last(zamowienia *head_node, zamowienie value);

void zamowienia_push_first(zamowienia *head_node, zamowienie value);

zamowienie zamowienia_pop_last(zamowienia *head_node);

zamowienie zamowienia_pop_first(zamowienia *head_node);

void zamowienia_clean(zamowienia *head_node);

void zamowienia_printall(zamowienia *head_node);
