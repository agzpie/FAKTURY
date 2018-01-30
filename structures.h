
/*#ifndef _LISTA_ZAMOWIEN_
#define _LISTA_ZAMOWIEN_
#include "lista_zamowienia.h"
#endif
#ifndef _LISTA_FAKTUR_
#define _LISTA_FAKTUR_
#include "lista_faktury.h"
#endif
#ifndef _LISTA_FIRM_
#define _LISTA_FIRM_
#include "lista_firmy.h"
#endif*/

typedef struct str_sprzedawca {
    char przedsiebiorca[31];
    char nip[11];
    char nr_konta[27];
}sprzedawca;

typedef struct str_firma{
    char* nazwa_firmy;
    char* nr_NIP;
}firma;

typedef struct str_faktura{
    char* nr_faktury;
    firma* nabywca;
    char* data_wystawienia;
    char* data_sprzedazy;
    char* sposob_platnosci;
    char* termin_platnosci;
    //zamowienia zam;
}faktura;

typedef struct str_zamowienie{
    char* nazwa;
    //faktura* nr_faktury;
    int ilosc;
    float vat;
    float cena_netto;
    float wartosc_netto;
    float wartosc_brutto;
}zamowienie;

typedef struct node_zamowienia {
    zamowienie value;
    struct node_zamowienia *next;
}zamowienia;

typedef struct node_faktury {
    faktura value;
    struct node_faktury *next;
}faktury;

typedef struct node_firmy {
    firma value;
    struct node_firmy *next;
}firmy;