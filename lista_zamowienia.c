#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista_zamowienia.h"

void zamowienia_push_last(zamowienia *head_node, zamowienie value) {
    if (head_node->next == NULL) {
        // First node
        head_node->next = malloc(sizeof(zamowienia));
        head_node->next->value = value;
        head_node->next->next = NULL;
    } else {
        // Second or later node
        zamowienia *current = head_node->next;
        while (current->next != NULL)
            current = current->next;

        current->next = malloc(sizeof(zamowienia));
        current->next->value = value;
        current->next->next = NULL;
    }
}

void zamowienia_push_first(zamowienia *head_node, zamowienie value) {
    if (head_node->next == NULL) {
        // First node with data
        head_node->next = malloc(sizeof(zamowienia));
        head_node->next->value = value;
        head_node->next->next = NULL;
    }

    // Existing list
    zamowienia *oldfirst = head_node->next;
    head_node->next = malloc(sizeof(zamowienia));
    head_node->next->value = value;
    head_node->next->next = oldfirst;
}

zamowienie zamowienia_pop_last(zamowienia *head_node) {
    zamowienie ret;
    if (head_node->next == NULL) {
        return ret;
    }

    zamowienia *current = head_node->next;
    zamowienia *prev_current = head_node;
    while (current->next != NULL) {
        prev_current = current;
        current = current->next;
    }

    ret = current->value;
    free(prev_current->next);
    prev_current->next = NULL;

    return ret;
}

zamowienie zamowienia_pop_first(zamowienia *head_node) {
    zamowienia *current = head_node->next;
    zamowienia *headnn = head_node->next->next;
    zamowienie value = current->value;
    free(head_node->next);
    head_node->next=headnn;

    return value;
}

void zamowienia_clean(zamowienia *head_node) {
    while (head_node->next != NULL)
    {
        zamowienia_pop_first(head_node);
    }
}

void zamowienia_printall(zamowienia *head_node) {
    zamowienia *current = head_node->next;
    while (current != NULL) {
        printf("Nazwa zamowienia: %s\t\tNr faktury = %s\n", current->value.nazwa, current->value.fakt->nr_faktury);
        current = current->next;
    }
}
