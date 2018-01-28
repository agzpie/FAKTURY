#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node thunderstruct;

void push_last(thunderstruct *head_node, int value);

void push_first(thunderstruct *head_node, int value);

int pop_last(thunderstruct *head_node);

int pop_first(thunderstruct *head_node);

void clean(thunderstruct *head_node);

void printall(thunderstruct *head_node);
