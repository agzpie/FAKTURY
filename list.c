#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

typedef struct node {
    int value;
    struct node *next;
}thunderstruct;

void push_last(thunderstruct *head_node, int value) {
    if (head_node->next == NULL) {
        // First node with data
        head_node->next = malloc(sizeof(thunderstruct));
        head_node->next->value = value;
        head_node->next->next = NULL;
    } else {
        // Second or later node with data
        thunderstruct *current = head_node->next;
        while (current->next != NULL)
            current = current->next;

        current->next = malloc(sizeof(thunderstruct));
        current->next->value = value;
        current->next->next = NULL;
    }
}

void push_first(thunderstruct *head_node, int value) {
    if (head_node->next == NULL) {
        // First node with data
        head_node->next = malloc(sizeof(thunderstruct));
        head_node->next->value = value;
        head_node->next->next = NULL;
    }

    // Existing list
    thunderstruct *oldfirst = head_node->next;
    head_node->next = malloc(sizeof(thunderstruct));
    head_node->next->value = value;
    head_node->next->next = oldfirst;
}

int pop_last(thunderstruct *head_node) {
    if (head_node->next == NULL) {
        return -1;
    }

    thunderstruct *current = head_node->next;
    thunderstruct *prev_current = head_node;
    while (current->next != NULL) {
        prev_current = current;
        current = current->next;
    }

    int ret = current->value;
    free(prev_current->next);
    prev_current->next = NULL;

    return ret;
}

int pop_first(thunderstruct *head_node) {
    thunderstruct *current = head_node->next;
    thunderstruct *headnn = head_node->next->next;
    int value = current->value;
    free(head_node->next);
    head_node->next=headnn;

    return value;
}

void clean(thunderstruct *head_node) {
    while (head_node->next != NULL)
    {
        pop_first(head_node);
    }
}

void printall(thunderstruct *head_node) {
    thunderstruct *current = head_node->next;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
}
