typedef struct str_sprzedawca {
    char* przedsiebiorca;
    char* nip;
    char* nr_konta;
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
}faktura;

typedef struct str_zamowienie{
    char* nazwa;
    int ilosc;
    float vat;
    float cena_netto;
    float wartosc_netto;
    float wartosc_brutto;
    faktura* fakt;
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