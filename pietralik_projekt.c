#include <stdio.h>
#include <malloc.h>
#ifndef _STRUCTURES_
#define _STRUCTURES_
#include "structures.h"
#endif
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

#include "lista_zamowienia.h"
#include "lista_faktury.h"
#include "lista_firmy.h"


// ZMIENNE GLOBALNE
sprzedawca sprz;
firmy *lista_firm;
faktury *lista_faktur;
zamowienia *lista_zamowien;

// FUNKCJE
zamowienie stworz_zamowienie(char* p_nazwa, int p_ilosc, float p_vat, float p_cena_netto, faktura* fak) {
    float wartosc_netto = p_ilosc * p_cena_netto;
    zamowienie zam = {
            p_nazwa,
            p_ilosc,
            p_vat,
            p_cena_netto,
            wartosc_netto,
            wartosc_netto * (1 + p_vat),
            fak
    };

    return zam;
};

//faktura stworz_fakture(char* nr_faktury, firma* nabywca, char* data_wystawienia, char* data_sprzedazy, char* sposob_platnosci, char* termin_platnosci, zamowienia zam) {
faktura stworz_fakture(char* nr_faktury, firma* nabywca, char* data_wystawienia, char* data_sprzedazy, char* sposob_platnosci, char* termin_platnosci) {
    faktura fak = {
        nr_faktury,
        nabywca,
        data_wystawienia,
        data_sprzedazy,
        sposob_platnosci,
        termin_platnosci//,
        //zam
    };

    return fak;
};

void pokaz_fakture(faktura fak) {
    printf("FAKTURA VAT\n");
    printf("Nr faktury: %s\n\n", fak.nr_faktury);
    printf("Sprzedawca:\n%s\nNIP: %s\nnr konta: %s\n\n", sprz.przedsiebiorca, sprz.nip, sprz.nr_konta);
    // https://stackoverflow.com/questions/10036381/arrow-operator-vs-dot-operator
    printf("Nabywca:\n%s\nNIP: %s\n\n", fak.nabywca->nazwa_firmy, fak.nabywca->nr_NIP);
    printf("Data wystawienia:\t%s\nData sprzedazy:\t%s\nSposob platnosci:\t%s\nTermin platnosci:\t%s\n", fak.data_wystawienia, fak.data_sprzedazy, fak.sposob_platnosci, fak.termin_platnosci);
}

firma stworz_firme(char* nazwa_firmy, char* nr_NIP) {
    firma fir = {
            nazwa_firmy,
            nr_NIP
    };

    return fir;
};

void drukuj_zamowienie(zamowienie zam) {
    printf("Produkt = %s\t\tWartosc brutto = %f\t\tNr faktury = %s\n", zam.nazwa, zam.wartosc_brutto, zam.fakt->nr_faktury);
};

void drukuj_fakture(faktura fak) {
    printf("Numer faktury = %s\t\tNazwa nabywcy = %s\n", fak.nr_faktury, fak.nabywca->nazwa_firmy);
};

void drukuj_firme(firma fir) {
    printf("Nazwa firmy = %s\t\tNumer NIP = %s\n", fir.nazwa_firmy, fir.nr_NIP);
};

void drukuj_sprzedawce(sprzedawca sprz) {
    printf("Przedsiebiorca = %s\t\tNumer NIP = %s\t\tNumer konta = %s\t\n", sprz.przedsiebiorca, sprz.nip, sprz.nr_konta);
};

int usun_sprzedawce() {
    int status = remove("settings.db");
    if (status != 0) {
        printf("Blad usuwania sprzedawcy");
    };

    return status;
};

sprzedawca zainicjalizuj_sprzedawce() {
    sprzedawca sprz;
    char* plik = "settings.db";
    FILE *settings = fopen(plik, "r");

    if (settings != NULL) {
        int i = 1; // numer wiersza
        int poz = 0; // pozycja
        char ch;
        while ((ch = (char)fgetc(settings)) != (char)EOF) {
            if (ch == '\t') {
                i++;
                poz = 0;
            }
            else {
                switch (i){
                    case 1: sprz.przedsiebiorca[poz] = ch;
                            sprz.przedsiebiorca[++poz] = '\0';
                            break;
                    case 2: sprz.nip[poz] = ch;
                            sprz.nip[++poz] = '\0';
                            break;
                    case 3: sprz.nr_konta[poz] = ch;
                            sprz.nr_konta[++poz] = '\0';
                            break;
                    default:
                            break;
                }
            }
        }
        fclose(settings);

        return sprz;
    }

    printf("Wczytaj nazwe sprzedawcy: ");
    scanf("%s", sprz.przedsiebiorca);
    printf("Wczytaj numer NIP: ");
    scanf("%s", sprz.nip);
    printf("Wczytaj numer konta: ");
    scanf("%s", sprz.nr_konta);

    settings = fopen(plik, "w");
    for (int i = 0; i <sizeof(sprz.przedsiebiorca); i++) {
        if (sprz.przedsiebiorca[i]!='\0') {
            fputc(sprz.przedsiebiorca[i], settings);
        }
        else {
            fputc((int)'\t', settings);
            break;
        }
    }

    for (int i = 0; i <sizeof(sprz.nip); i++) {
        if (sprz.nip[i]!='\0') {
            fputc(sprz.nip[i], settings);
        }
        else {
            fputc((int)'\t', settings);
            break;
        }
    }

    for (int i = 0; i <sizeof(sprz.nr_konta); i++) {
        if (sprz.nr_konta[i]!='\0') {
            fputc(sprz.nr_konta[i], settings);
        }
        else {
            break;
        }
    }

    return sprz;
}

// MAIN
int main() {

    sprz = zainicjalizuj_sprzedawce();
    drukuj_sprzedawce(sprz);

    firma firmaturbokolor = stworz_firme("turbokolor", "1234567890");
    firma firmanowak = stworz_firme("nowak and nowak", "5678956757");
    firma firmakielbasy = stworz_firme("tarczynski kielbasy", "2123576545");
    drukuj_firme(firmaturbokolor);
    drukuj_firme(firmanowak);
    drukuj_firme(firmakielbasy);

    faktura faktura1 = stworz_fakture("101/2018", &firmaturbokolor, "28/01/2018", "20/01/2018", "przelew", "23/01/2018");
    faktura faktura2 = stworz_fakture("102/2018", &firmaturbokolor, "29/01/2018", "29/01/2018", "gotowka", "24/01/2018");
    faktura faktura3 = stworz_fakture("103/2018", &firmaturbokolor, "30/01/2018", "30/01/2018", "czek", "25/01/2018");
    faktura faktura4 = stworz_fakture("104/2018", &firmanowak, "11/02/2018", "22/02/2018", "przelew", "14/02/2018");
    faktura faktura5 = stworz_fakture("105/2018", &firmakielbasy, "12/02/2018", "23/02/2018", "gotowka", "15/02/2018");
    faktura faktura6 = stworz_fakture("106/2018", &firmakielbasy, "25/02/2018", "05/03/2018", "czek", "30/02/2018");

    zamowienie zamowienie1 = stworz_zamowienie("chleb", 3, 0.23, 4.0, &faktura1);
    zamowienie zamowienie2 = stworz_zamowienie("maslo", 8, 0.23, 8.20, &faktura1);
    zamowienie zamowienie3 = stworz_zamowienie("wedlina", 4, 0.23, 19.0, &faktura1);
    zamowienie zamowienie4 = stworz_zamowienie("sroba", 3, 0.23, 21.0, &faktura2);
    zamowienie zamowienie5 = stworz_zamowienie("woda", 6, 0.23, 2.0, &faktura2);
    zamowienie zamowienie6 = stworz_zamowienie("wiertarka", 44, 0.23, 200.0, &faktura3);
    zamowienie zamowienie7 = stworz_zamowienie("betoniarka", 15, 0.23, 1500.0, &faktura3);
    /*drukuj_zamowienie(zamowienie1);
    drukuj_zamowienie(zamowienie2);
    drukuj_zamowienie(zamowienie3);
    drukuj_zamowienie(zamowienie4);
    drukuj_zamowienie(zamowienie5);
    drukuj_zamowienie(zamowienie6);
    drukuj_zamowienie(zamowienie7);*/

    /*drukuj_fakture(faktura1);
    drukuj_fakture(faktura2);
    drukuj_fakture(faktura3);
    drukuj_fakture(faktura4);
    drukuj_fakture(faktura5);
    drukuj_fakture(faktura6);*/

    pokaz_fakture(faktura1);
    pokaz_fakture(faktura2);
    pokaz_fakture(faktura3);
    pokaz_fakture(faktura4);
    pokaz_fakture(faktura5);
    pokaz_fakture(faktura6);

    ///////////
    // Lista firm
    lista_firm = malloc(sizeof(firmy));
    if (lista_firm == NULL)
        return 1;
    lista_firm->next = NULL;
    firmy_push_last(lista_firm, firmaturbokolor);
    firmy_push_last(lista_firm, firmanowak);
    firmy_push_last(lista_firm, firmakielbasy);
    printf("Test listy firm:\n");
    firmy_printall(lista_firm);

    // Lista faktur
    lista_faktur = malloc(sizeof(faktury));
    if (lista_faktur == NULL)
        return 1;
    lista_faktur->next = NULL;
    faktury_push_last(lista_faktur, faktura1);
    faktury_push_last(lista_faktur, faktura2);
    faktury_push_last(lista_faktur, faktura3);
    faktury_push_last(lista_faktur, faktura4);
    faktury_push_last(lista_faktur, faktura5);
    faktury_push_last(lista_faktur, faktura6);
    printf("Test listy faktur:\n");
    faktury_printall(lista_faktur);

    // Lista zamowien
    lista_zamowien = malloc(sizeof(zamowienia));
    if (lista_zamowien == NULL)
        return 1;
    lista_zamowien->next = NULL;
    zamowienia_push_last(lista_zamowien, zamowienie1);
    zamowienia_push_last(lista_zamowien, zamowienie2);
    zamowienia_push_last(lista_zamowien, zamowienie3);
    zamowienia_push_last(lista_zamowien, zamowienie4);
    zamowienia_push_last(lista_zamowien, zamowienie5);
    zamowienia_push_last(lista_zamowien, zamowienie6);
    zamowienia_push_last(lista_zamowien, zamowienie7);
    printf("Test listy zamowien:\n");
    zamowienia_printall(lista_zamowien);


    // MENU (nieskonczone)
    /*
    // start
    zainicjalizuj_sprzedawce();
    int opcja;
    printf("\tWitaj przybyszu, co chcesz dzis zrobic? Wybierz numer: \n");
    printf("1) Zmodyfikuj dane sprzedawcy.\n2) Wystaw fakture VAT.\n3) Usun fakture z bazy danych.\n4) Wyswietl wystawione faktury.\n5) Wyjdz stad.\n");
    while (1) {
        scanf("%d", &opcja);
        if ((opcja < 1) || (opcja > 5)) {
            printf("Nie ma takiej opcji. Sprobuj ponownie: ");
            scanf("%d", &opcja);
        }
        switch (opcja) {
            case 1:
                if (usun_sprzedawce() != 0) {
                    return -1;
                };
                zainicjalizuj_sprzedawce();
                break;
            case 2:
                printf("opcja jeszcze niedostepna, prosze sprobowac za kilka dni\n");
                break;
            case 3:
                printf("opcja niedostepna, niedlugo bedzie dzialac\n");
                break;
            case 4:
                printf("opcja niekoniecznie dziala, przepraszamy\n");
                break;
            case 5:
                return 0;
            default:
                break;
        }
    }*/

    return 0;
}
