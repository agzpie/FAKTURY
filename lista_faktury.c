#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista_zamowienia.h"

void faktury_push_last(faktury *head_node, faktura value) {
    if (head_node->next == NULL) {
        // First node
        head_node->next = malloc(sizeof(faktury));
        head_node->next->value = value;
        head_node->next->next = NULL;
    } else {
        // Second or later node
        faktury *current = head_node->next;
        while (current->next != NULL)
            current = current->next;

        current->next = malloc(sizeof(faktury));
        current->next->value = value;
        current->next->next = NULL;
    }
}

void faktury_push_first(faktury *head_node, faktura value) {
    if (head_node->next == NULL) {
        // First node with data
        head_node->next = malloc(sizeof(faktury));
        head_node->next->value = value;
        head_node->next->next = NULL;
    }

    // Existing list
    faktury *oldfirst = head_node->next;
    head_node->next = malloc(sizeof(faktury));
    head_node->next->value = value;
    head_node->next->next = oldfirst;
}

faktura faktury_pop_last(faktury *head_node) {
    faktura ret;
    if (head_node->next == NULL) {
        return ret;
    }

    faktury *current = head_node->next;
    faktury *prev_current = head_node;
    while (current->next != NULL) {
        prev_current = current;
        current = current->next;
    }

    ret = current->value;
    free(prev_current->next);
    prev_current->next = NULL;

    return ret;
}

faktura faktury_pop_first(faktury *head_node) {
    faktury *current = head_node->next;
    faktury *headnn = head_node->next->next;
    faktura value = current->value;
    free(head_node->next);
    head_node->next=headnn;

    return value;
}

void faktury_clean(faktury *head_node) {
    while (head_node->next != NULL)
    {
        faktury_pop_first(head_node);
    }
}

void faktury_printall(faktury *head_node) {
    faktury *current = head_node->next;
    while (current != NULL) {
        printf("Nr faktury: %s\n", current->value.nr_faktury);
        current = current->next;
    }
}
