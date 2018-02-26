#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista_zamowienia.h"

void firmy_push_last(firmy *head_node, firma value) {
    if (head_node->next == NULL) {
        // First node
        head_node->next = malloc(sizeof(firmy));
        head_node->next->value = value;
        head_node->next->next = NULL;
    } else {
        // Second or later node
        firmy *current = head_node->next;
        while (current->next != NULL)
            current = current->next;

        current->next = malloc(sizeof(firmy));
        current->next->value = value;
        current->next->next = NULL;
    }
}

void firmy_push_first(firmy *head_node, firma value) {
    if (head_node->next == NULL) {
        // First node with data
        head_node->next = malloc(sizeof(firmy));
        head_node->next->value = value;
        head_node->next->next = NULL;
    }

    // Existing list
    firmy *oldfirst = head_node->next;
    head_node->next = malloc(sizeof(firmy));
    head_node->next->value = value;
    head_node->next->next = oldfirst;
}

firma firmy_pop_last(firmy *head_node) {
    firma ret;
    if (head_node->next == NULL) {
        return ret;
    }

    firmy *current = head_node->next;
    firmy *prev_current = head_node;
    while (current->next != NULL) {
        prev_current = current;
        current = current->next;
    }

    ret = current->value;
    free(prev_current->next);
    prev_current->next = NULL;

    return ret;
}

firma firmy_pop_first(firmy *head_node) {
    firmy *current = head_node->next;
    firmy *headnn = head_node->next->next;
    firma value = current->value;
    free(head_node->next);
    head_node->next=headnn;

    return value;
}

void firmy_clean(firmy *head_node) {
    while (head_node->next != NULL)
    {
        firmy_pop_first(head_node);
    }
}

void firmy_printall(firmy *head_node) {
    firmy *current = head_node->next;
    while (current != NULL) {
        printf("Nazwa firmy:\t%s\t\tNr NIP:\t%s\n", current->value.nazwa_firmy, current->value.nr_NIP);
        current = current->next;
    }
}
