
typedef struct str_sprzedawca {
    char przedsiebiorca[31];
    char nip[11];
    char nr_konta[27];
} sprzedawca;

typedef struct str_firma{
    char* nazwa_firmy;
    char* nr_NIP; //bo nr nip jest 10-cyfrowy
    char* nr_konta; //nr konta ma 26 znaków; oslo bug check: co jeśli ktoś wpisze z odstępami
}firma;

typedef struct str_faktura{
    char* nr_faktury;
    firma nabywca;
    char* data_wystawienia;
    char* data_sprzedazy;
    char* sposob_platnosci;
}faktura;

typedef struct str_zamowienie{
    char* nazwa;
    int ilosc;
    float vat;
    float cena_netto;
    float wartosc_netto;
    float wartosc_brutto;
}zamowienie;


typedef struct node {
    zamowienie value;
    struct node *next;
}thunderstruct;
