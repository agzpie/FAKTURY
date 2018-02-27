#include <stdio.h>
#include <malloc.h>
#include <string.h>
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

faktura stworz_fakture(char* nr_faktury, firma* nabywca, char* data_wystawienia, char* data_sprzedazy, char* sposob_platnosci, char* termin_platnosci) {
    faktura fak = {
        nr_faktury,
        nabywca,
        data_wystawienia,
        data_sprzedazy,
        sposob_platnosci,
        termin_platnosci
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

void drukuj_zamowienie(zamowienie *zam) {
    //printf("Produkt = %s\t\tIlosc = %d\t\tWartosc netto = %f\t\tWartosc brutto = %f\t\tVAT = %f\t\tNr faktury = %s\n", zam->nazwa, zam->ilosc, zam->wartosc_netto, zam->wartosc_brutto, zam->vat, zam->fakt->nr_faktury);
    printf("Produkt = %s\t\tIlosc = %d\t\tWartosc netto = %f\t\tWartosc brutto = %f\t\tVAT = %f\n", zam->nazwa, zam->ilosc, zam->wartosc_netto, zam->wartosc_brutto, zam->vat);
};

void drukuj_fakture(faktura *fak) {
    printf("FAKTURA:\nnumer = %s\tnabywca = %s\tdata sprzedazy = %s\tdata wystawienia = %s\ttermin platnosci= %s\tsposob platnosci = %s\n",
           fak->nr_faktury, fak->nabywca->nazwa_firmy, fak->data_sprzedazy, fak->data_wystawienia, fak->termin_platnosci, fak->sposob_platnosci);
};

void drukuj_firme(firma *fir) {
    printf("Nazwa firmy = %s\t\tNumer NIP = %s\n", fir->nazwa_firmy, fir->nr_NIP);
};

void drukuj_sprzedawce() {
    printf("Przedsiebiorca = %s\t\tNumer NIP = %s\t\tNumer konta = %s\t\n", sprz.przedsiebiorca, sprz.nip, sprz.nr_konta);
};

float podsumuj_fakture(faktura *fak) {
    float suma_brutto = 0;
    zamowienia *current_zam = lista_zamowien->next;
    while (current_zam != NULL) {
        if (current_zam->value.fakt->nr_faktury == fak->nr_faktury) {
            suma_brutto += current_zam->value.wartosc_brutto;
        }

        current_zam = current_zam->next;
    }

    return suma_brutto;
}

int usun_sprzedawce() {
    int status = remove("settings.db");
    if (status != 0) {
        printf("Blad usuwania sprzedawcy");
    };

    return status;
};

void zainicjalizuj_sprzedawce() {
    char *plik = "settings.db";
    FILE *settings = fopen(plik, "r");

    if (settings != NULL) {
        char* buffer = malloc(sizeof(char) * 100); // 100 - maks dlugosc ciagu znakow

        int i = 1; // numer wiersza
        int poz = 0; // pozycja
        char ch;
        while (1) {
            ch = (char)fgetc(settings);
            if ((ch != ';') && (ch != (char)EOF)) {
                buffer[poz++] = ch;
            }
            else {
                char* value = malloc(sizeof(char) * (poz+1));

                for(int j = 0; j<poz; j++)
                {
                    value[j]=buffer[j];
                }

                value[poz] = '\0';

                switch (i){
                    case 1: sprz.przedsiebiorca = value;
                            break;
                    case 2: sprz.nip = value;
                            break;
                    case 3: sprz.nr_konta = value;
                            break;
                    default:
                            break;
                }

                if (ch == (char)EOF)
                    break;

                i++;
                poz=0;
            }
        }

        fclose(settings);
        return;
    }

    char *nazwa = malloc(sizeof(char)*30),* nip = malloc(sizeof(char)*30), *nr_konta = malloc(sizeof(char)*30);
    printf("Wczytaj nazwe sprzedawcy: ");
    scanf("%s", nazwa);
    printf("Wczytaj numer NIP: ");
    scanf("%s", nip);
    printf("Wczytaj numer konta: ");
    scanf("%s", nr_konta);

    sprz.przedsiebiorca = nazwa;
    sprz.nip = nip;
    sprz.nr_konta = nr_konta;

    settings = fopen(plik, "w");
    for (int i = 0; i <strlen(sprz.przedsiebiorca); i++) {
            fputc(sprz.przedsiebiorca[i], settings);
    }
    fputc((int)';', settings);

    for (int i = 0; i <strlen(sprz.nip); i++) {
            fputc(sprz.nip[i], settings);
    }

    fputc((int)';', settings);

    for (int i = 0; i <strlen(sprz.nr_konta); i++) {
            fputc(sprz.nr_konta[i], settings);
    }

    fclose(settings);
};

firma* znajdz_firme(char* nr_NIP) {
    firmy *current = lista_firm->next;
    while (current != NULL) {
        if (strcmp(current->value.nr_NIP,nr_NIP) != 0) {
            return &(current->value);
        }
        current = current->next;
    }

    return NULL;
};

faktura* wpisz_fakture() {
    int buffer = 100;
    char value[buffer];
    faktura *nowa_faktura = malloc(sizeof(faktura));

    printf("Numer faktury:\n");
    fgets(value, 100, stdin);
    nowa_faktura->nr_faktury = malloc(sizeof(char)*strlen(value));
    strcpy(nowa_faktura->nr_faktury, value);

    printf("Data sprzedazy:\n");
    fgets(value, buffer, stdin);
    nowa_faktura->data_sprzedazy = malloc(sizeof(char)*strlen(value));
    strcpy(nowa_faktura->data_sprzedazy, value);

    printf("Data wystawienia:\n");
    fgets(value, buffer, stdin);
    nowa_faktura->data_wystawienia = malloc(sizeof(char)*strlen(value));
    strcpy(nowa_faktura->data_wystawienia, value);

    printf("Termin platnosci:\n");
    fgets(value, buffer, stdin);
    nowa_faktura->termin_platnosci = malloc(sizeof(char)*strlen(value));
    strcpy(nowa_faktura->termin_platnosci, value);

    printf("Sposob platnosci:\n");
    fgets(value, buffer, stdin);
    nowa_faktura->sposob_platnosci = malloc(sizeof(char)*strlen(value));
    strcpy(nowa_faktura->sposob_platnosci, value);

    printf("P: %s", nowa_faktura->nr_faktury);

    drukuj_fakture(nowa_faktura);

    return nowa_faktura;
}

void opcja5_dodaj_firme () {
    char *nazwa = malloc(sizeof(char)*100);
    char *nip = malloc(sizeof(char)*10);
    printf("Podaj nazwe firmy: ");
    scanf("%s", nazwa);
    printf("Podaj nr NIP firmy: ");
    scanf("%s", nip);

    firma nowa_firma = stworz_firme(nazwa,nip);
    firmy_push_last(lista_firm, nowa_firma);
}

void opcja2_stworz_fakture () {
    firma *znaleziona_firma;

    while(1) {
        printf("Podaj NIP firmy:");
        char *nip = malloc(sizeof(char)*100);
        scanf("%s", nip);
        znaleziona_firma = znajdz_firme(nip);
        if (znaleziona_firma != NULL) {
            break;
        }
        free(nip);

        printf("Zly NIP. Wybierz:\n1) Sprobuj ponownie.\n2) Powrot do menu.");
        int choice;
        scanf("%d", choice);
        if (choice == 2) {
            return;
        }
    }

    // Na tym etapie znaleziona_firma powinno miec poprawna firme
    // Mozemy zaczac tworzyc fakture a nastepnie liste zamowien

    // TODO - kod do poprawki
    faktura *fakt = wpisz_fakture();
    printf("DRUKUJ2");
    drukuj_fakture(fakt);
    faktury_push_last(lista_faktur, *fakt);
    faktury_printall(lista_faktur);

    while(1) {
        zamowienie *nowe_zamowienie = malloc(sizeof(zamowienie));
        printf("Podaj dane zamowienia:\nNazwa produktu: ");
        scanf("%s", nowe_zamowienie->nazwa);
        printf("Ilosc: ");
        scanf("%d", nowe_zamowienie->ilosc);
        printf("VAT: ");
        scanf("%f", nowe_zamowienie->vat);
        printf("Wartosc netto: ");
        scanf("%f", nowe_zamowienie->wartosc_netto);
        printf("Numer faktury: ");
        scanf("%s", nowe_zamowienie->fakt);
        nowe_zamowienie->wartosc_brutto = ((nowe_zamowienie->vat/100) + 1)*(nowe_zamowienie->wartosc_netto);
        printf("Wartosc brutto = %f", nowe_zamowienie->wartosc_brutto);

        zamowienia_push_last(lista_zamowien, *nowe_zamowienie);

        printf("Wybierz:\n1) Dodaj kolejne zamowienie.\n2) Powrot do menu.");
        int choice;
        scanf("%d", choice);
        if (choice == 2) {
            return;
        }
    }
}

void faktury_printall_z_zamowieniami() {
    faktury *fak = lista_faktur->next;
    while (fak != NULL) {
        printf("-------\nNr faktury: %s\t", fak->value.nr_faktury);
        drukuj_firme(fak->value.nabywca);

        zamowienia *current_zam = lista_zamowien->next;
        float suma_brutto = 0;
        while (current_zam != NULL) {
            if (current_zam->value.fakt->nr_faktury == fak->value.nr_faktury) {
                suma_brutto += current_zam->value.wartosc_brutto;
                drukuj_zamowienie(&(current_zam->value));
            }

            current_zam = current_zam->next;
        }
        printf("SUMA BRUTTO = %f\n\n", suma_brutto);

        fak = fak->next;
    }
}

void zapisz_firmy() {
    char *plik = "firmy.db";
    FILE *baza = fopen(plik, "w");
    firmy *firma = lista_firm->next;

    int pierwsza_linia = 1;
    while (firma != NULL) {
        if (pierwsza_linia) {
            pierwsza_linia = 0;
        }
        else {
            fputc((int)'\n', baza);
        }
        for (int i = 0; i <strlen(firma->value.nazwa_firmy); i++) {
            fputc(firma->value.nazwa_firmy[i], baza);
        }
        fputc((int)';', baza);

        for (int i = 0; i <strlen(firma->value.nr_NIP); i++) {
            fputc(firma->value.nr_NIP[i], baza);
        }

        firma = firma->next;
    }

    fclose(baza);
}

void zapisz_zamowienia() {
    char *plik = "zamowienia.db";
    FILE *baza = fopen(plik, "w");
    zamowienia *zamowienie = lista_zamowien->next;
    char *buffer = malloc(sizeof(char)*100);

    int pierwsza_linia = 1;
    while (zamowienie != NULL) {
        if (pierwsza_linia) {
            pierwsza_linia = 0;
        }
        else {
            fputc((int)'\n', baza);
        }
        for (int i = 0; i <strlen(zamowienie->value.nazwa); i++) {
            fputc(zamowienie->value.nazwa[i], baza);
        }
        fputc((int)';', baza);

        for (int i = 0; i <strlen(zamowienie->value.fakt->nr_faktury); i++) {
            fputc(zamowienie->value.fakt->nr_faktury[i], baza);
        }
        fputc((int)';', baza);

        itoa(zamowienie->value.ilosc, buffer, 10);
        for (int i = 0; i <strlen(buffer); i++) {
            fputc(buffer[i], baza);
        }
        fputc((int)';', baza);

        int len = snprintf(NULL, 0, "%f", zamowienie->value.vat);
        char *result = (char *)malloc(sizeof(char)*(len+1));
        snprintf(result, sizeof(char)*(len+1), "%f", zamowienie->value.vat);
        for (int i = 0; i <len; i++) {
            fputc(result[i], baza);
        }
        free(result);
        fputc((int)';', baza);

        len = snprintf(NULL, 0, "%f", zamowienie->value.cena_netto);
        result = (char *)malloc(sizeof(char)*(len+1));
        snprintf(result, sizeof(char)*(len+1), "%f", zamowienie->value.cena_netto);
        for (int i = 0; i <len; i++) {
            fputc(result[i], baza);
        }
        free(result);
        /*fputc((int)';', baza);

        len = snprintf(NULL, 0, "%f", zamowienie->value.wartosc_netto);
        result = (char *)malloc(sizeof(char)*(len+1));
        snprintf(result, sizeof(char)*(len+1), "%f", zamowienie->value.wartosc_netto);
        for (int i = 0; i <len; i++) {
            fputc(result[i], baza);
        }
        free(result);
        fputc((int)';', baza);

        len = snprintf(NULL, 0, "%f", zamowienie->value.wartosc_brutto);
        result = (char *)malloc(sizeof(char)*(len+1));
        snprintf(result, sizeof(char)*(len+1), "%f", zamowienie->value.wartosc_brutto);
        for (int i = 0; i <len; i++) {
            fputc(result[i], baza);
        }
        free(result);*/

        zamowienie = zamowienie->next;
    }

    free(buffer);
    fclose(baza);
}

void zapisz_faktury() {
    char *plik = "faktury.db";
    FILE *baza = fopen(plik, "w");
    faktury *faktura = lista_faktur->next;
    char *buffer = malloc(sizeof(char)*100);

    int pierwsza_linia = 1;
    while (faktura != NULL) {
        if (pierwsza_linia) {
            pierwsza_linia = 0;
        }
        else {
            fputc((int)'\n', baza);
        }

        for (int i = 0; i <strlen(faktura->value.nr_faktury); i++) {
            fputc(faktura->value.nr_faktury[i], baza);
        }
        fputc((int)';', baza);

        for (int i = 0; i <strlen(faktura->value.nabywca->nr_NIP); i++) {
            fputc(faktura->value.nabywca->nr_NIP[i], baza);
        }
        fputc((int)';', baza);

        for (int i = 0; i <strlen(faktura->value.data_wystawienia); i++) {
            fputc(faktura->value.data_wystawienia[i], baza);
        }
        fputc((int)';', baza);

        for (int i = 0; i <strlen(faktura->value.data_sprzedazy); i++) {
            fputc(faktura->value.data_sprzedazy[i], baza);
        }
        fputc((int)';', baza);

        for (int i = 0; i <strlen(faktura->value.sposob_platnosci); i++) {
            fputc(faktura->value.sposob_platnosci[i], baza);
        }
        fputc((int)';', baza);

        for (int i = 0; i <strlen(faktura->value.termin_platnosci); i++) {
            fputc(faktura->value.termin_platnosci[i], baza);
        }

        faktura = faktura->next;
    }

    free(buffer);
    fclose(baza);
}

void zapisz_dane() {
    zapisz_firmy();
    zapisz_zamowienia();
    zapisz_faktury();
}

// MAIN
int main() {
    // LISTY - POCZATEK PROGRAMU
    // Lista firm
    lista_firm = malloc(sizeof(firmy));
    if (lista_firm == NULL)
        return 1;
    lista_firm->next = NULL;

    // Lista faktur
    lista_faktur = malloc(sizeof(faktury));
    if (lista_faktur == NULL)
        return 1;
    lista_faktur->next = NULL;

    // Lista zamowien
    lista_zamowien = malloc(sizeof(zamowienia));
    if (lista_zamowien == NULL)
        return 1;
    lista_zamowien->next = NULL;

    // TEMP
    firma firmaturbokolor = stworz_firme("turbokolor", "1234567890");
    firma firmanowak = stworz_firme("nowak and nowak", "5678956757");
    firma firmakielbasy = stworz_firme("tarczynski kielbasy", "2123576545");
    faktura faktura1 = stworz_fakture("101/2018", &firmaturbokolor, "28/01/2018", "20/01/2018", "przelew", "23/01/2018");
    faktura faktura2 = stworz_fakture("102/2018", &firmaturbokolor, "29/01/2018", "29/01/2018", "gotowka", "24/01/2018");
    faktura faktura3 = stworz_fakture("103/2018", &firmaturbokolor, "30/01/2018", "30/01/2018", "czek", "25/01/2018");
    faktura faktura4 = stworz_fakture("104/2018", &firmanowak, "11/02/2018", "22/02/2018", "przelew", "14/02/2018");
    faktura faktura5 = stworz_fakture("105/2018", &firmakielbasy, "12/02/2018", "23/02/2018", "gotowka", "15/02/2018");
    faktura faktura6 = stworz_fakture("106/2018", &firmakielbasy, "25/02/2018", "05/03/2018", "czek", "30/02/2018");
    zamowienie zamowienie1 = stworz_zamowienie("chleb", 20, 0.23, 1.9, &faktura1);
    zamowienie zamowienie2 = stworz_zamowienie("maslo", 8, 0.23, 8.20, &faktura1);
    zamowienie zamowienie3 = stworz_zamowienie("wedlina", 4, 0.23, 19.0, &faktura1);
    zamowienie zamowienie4 = stworz_zamowienie("wedka", 3, 0.23, 21.0, &faktura2);
    zamowienie zamowienie5 = stworz_zamowienie("woda", 6, 0.23, 2.0, &faktura2);
    zamowienie zamowienie6 = stworz_zamowienie("wiertarka", 2, 0.23, 200.0, &faktura3);
    zamowienie zamowienie7 = stworz_zamowienie("betoniarka", 1, 0.23, 1500.0, &faktura3);
    zamowienie zamowienie8 = stworz_zamowienie("ryba", 3, 0.23, 17.0, &faktura4);
    zamowienie zamowienie9 = stworz_zamowienie("komputer", 1, 0.23, 3000, &faktura5);
    zamowienie zamowienie10 = stworz_zamowienie("brzeszczot", 1, 0.23, 260.0, &faktura6);
    zamowienie zamowienie11 = stworz_zamowienie("pila", 2, 0.23, 340.0, &faktura6);
    firmy_push_last(lista_firm, firmaturbokolor);
    firmy_push_last(lista_firm, firmanowak);
    firmy_push_last(lista_firm, firmakielbasy);
    faktury_push_last(lista_faktur, faktura1);
    faktury_push_last(lista_faktur, faktura2);
    faktury_push_last(lista_faktur, faktura3);
    faktury_push_last(lista_faktur, faktura4);
    faktury_push_last(lista_faktur, faktura5);
    faktury_push_last(lista_faktur, faktura6);
    zamowienia_push_last(lista_zamowien, zamowienie1);
    zamowienia_push_last(lista_zamowien, zamowienie2);
    zamowienia_push_last(lista_zamowien, zamowienie3);
    zamowienia_push_last(lista_zamowien, zamowienie4);
    zamowienia_push_last(lista_zamowien, zamowienie5);
    zamowienia_push_last(lista_zamowien, zamowienie6);
    zamowienia_push_last(lista_zamowien, zamowienie7);
    zamowienia_push_last(lista_zamowien, zamowienie8);
    zamowienia_push_last(lista_zamowien, zamowienie9);
    zamowienia_push_last(lista_zamowien, zamowienie10);
    zamowienia_push_last(lista_zamowien, zamowienie11);
    zapisz_dane();
    printf("Podsumuj fakture 1 = %f\n", podsumuj_fakture(&faktura1));
    printf("Podsumuj fakture 2 = %f\n", podsumuj_fakture(&faktura2));
    // TEMP

    zainicjalizuj_sprzedawce();
    drukuj_sprzedawce();
    int opcja;
    printf("\tWitaj towarzyszu, co chcesz dzis zrobic? Wybierz numer: \n");

    while (1) {
        printf("\n___________________________\n");
        printf("1) Zmodyfikuj dane sprzedawcy.\n2) Wystaw fakture VAT.\n3) Usun fakture z bazy danych.\n"
                       "4) Wyswietl wystawione faktury.\n5) Dodaj firme.\n6) Usun firme.\n7) Wyswietl firmy.\n8) Wyjdz stad.\n");
        scanf("%d", &opcja);
        if ((opcja < 1) || (opcja > 8)) {
            printf("Nie ma takiej opcji. Sprobuj ponownie: ");
            scanf("%d", &opcja);
        }
        switch (opcja) {
            case 1:
                if (usun_sprzedawce() != 0) {
                    return -1;
                };
                zainicjalizuj_sprzedawce();
                drukuj_sprzedawce();
                break;
            case 2:
                opcja2_stworz_fakture();
                // ZAPISZ
                break;
            case 3:
                printf("ZAIMPLEMENTOWAC\n");
                // ZNAJDZ FAKTURE
                // USUN ZAMOWIENIA Z LISTY
                // USUN FAKTURE Z LISTY
                // ZAPISZ
                break;
            case 4:
                faktury_printall_z_zamowieniami();
                break;
            case 5:
                opcja5_dodaj_firme();
                // ZAPISZ
                break;
            case 6:
                printf("ZAIMPLEMENTOWAC\n");
                // ZNAJDZ FIRME
                // USUN FIRME Z LISTY
                // ZAPISZ
                break;
            case 7:
                printf("Dostepne firmy:\n");
                firmy_printall(lista_firm);
                break;
            case 8:
                return 0;
            default:
                break;
        }
    }
}
