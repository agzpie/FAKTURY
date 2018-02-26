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

//faktura stworz_fakture(char* nr_faktury, firma* nabywca, char* data_wystawienia, char* data_sprzedazy, char* sposob_platnosci, char* termin_platnosci, zamowienia zam) {
faktura stworz_fakture(char* nr_faktury, firma* nabywca, char* data_wystawienia, char* data_sprzedazy, char* sposob_platnosci, char* termin_platnosci) {
    faktura fak = {
        nr_faktury,
        nabywca,
        data_wystawienia,
        data_sprzedazy,
        sposob_platnosci,
        termin_platnosci
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

void drukuj_sprzedawce() {
    printf("Przedsiebiorca = %s\t\tNumer NIP = %s\t\tNumer konta = %s\t\n", sprz.przedsiebiorca, sprz.nip, sprz.nr_konta);
};

int usun_sprzedawce() {
    int status = remove("settings.db");
    if (status != 0) {
        printf("Blad usuwania sprzedawcy");
    };

    return status;
};

void zainicjalizuj_sprzedawce() {
    char* plik = "settings.db";
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

    char * nazwa = malloc(sizeof(char)*30),* nip = malloc(sizeof(char)*30), *nr_konta = malloc(sizeof(char)*30);
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
        if (current->value.nr_NIP == nr_NIP) {
            return &(current->value);
        }
        current = current->next;
    }
    printf("Nie znaleziono takiej firmy. ");
    return NULL;
};

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
        char *nip;
        scanf("%s", nip);
        znaleziona_firma = znajdz_firme(nip);
        if (znaleziona_firma != NULL) {
            break;
        }

        printf("Zly NIP. Wybierz:\n1) Sprobuj ponownie.\n2) Powrot do menu.");
        int choice;
        scanf("%d", choice);
        if (choice == 2) {
            return;
        }
    }

    // Na tym etapie znaleziona_firma powinno miec poprawna firme
    // Mozemy zaczac tworzyc fakture a nastepnie liste zamowien


    faktura *fak1;
    printf("Podaj date wystawienia: ");
    scanf("%s", fak1->data_wystawienia);
    printf("Sprzedazy: ");
    scanf("%s", fak1->data_sprzedazy);
    printf("Sposob platnosci: ");
    scanf("%s", fak1->sposob_platnosci);
    printf("Termin platnosci: ");
    scanf("%s", fak1->termin_platnosci);

    while(1) {
        zamowienie nowe_zamowienie;
        printf("Podaj dane zamowienia:\nNazwa produktu: ");
        scanf("%s", nowe_zamowienie.nazwa);
        printf("Ilosc: ");
        scanf("%d", nowe_zamowienie.ilosc);
        printf("VAT: ");
        scanf("%f", nowe_zamowienie.vat);
        printf("Wartosc netto: ");
        scanf("%f", nowe_zamowienie.wartosc_netto);
        printf("Numer faktury: ");
        scanf("%s", nowe_zamowienie.fakt);
        nowe_zamowienie.wartosc_brutto = ((nowe_zamowienie.vat/100) + 1)*(nowe_zamowienie.wartosc_netto);
        printf("Wartosc brutto = %f", nowe_zamowienie.wartosc_brutto);

        zamowienia_push_last(lista_zamowien, nowe_zamowienie);

        printf("Wybierz:\n1) Dodaj kolejne zamowienie.\n2) Powrot do menu.");
        int choice;
        scanf("%d", choice);
        if (choice == 2) {
            return;
        }
    }



    /*
    printf("Liczba zamowien: ");
    int licz = 0;
    int licznik = 0;
    scanf("%d", licz);

    float brutto;
    zamowienie *zam1;
    while(licznik<licz) {
        printf("Podaj dane zamowienia:\nNazwa produktu: ");
        scanf("%s", zam1->nazwa);
        printf("Ilosc: ");
        scanf("%d", zam1->ilosc);
        printf("VAT: ");
        scanf("%f", zam1->vat);
        printf("Wartosc netto: ");
        scanf("%f", zam1->wartosc_netto);
        printf("Numer faktury: ");
        scanf("%s", zam1->fakt);
        //brutto = (*(zam1->vat)**(zam1->wartosc_netto)/100);
        printf("Wartosc brutto: %f", brutto);
        licznik++;
    }

    firma fir1;
    printf("Podaj dane firmy:\nNazwa firmy: ");
    scanf("%s", fir1.nazwa_firmy);
    printf("Nr NIP: ");
    scanf("%s", fir1.nr_NIP);

    faktura *fak1;
    printf("Podaj date wystawienia: ");
    scanf("%s", fak1->data_wystawienia);
    printf("Sprzedazy: ");
    scanf("%s", fak1->data_sprzedazy);
    printf("Sposob platnosci: ");
    scanf("%s", fak1->sposob_platnosci);
    printf("Termin platnosci: ");
    scanf("%s", fak1->termin_platnosci);

    faktura f1 = stworz_fakture(zam1->fakt, fir1.nazwa_firmy, fak1->data_wystawienia, fak1->data_sprzedazy, fak1->sposob_platnosci, fak1->termin_platnosci);
    pokaz_fakture(f1);
    */
}

void faktury_printall_z_zamowieniami() {
    faktury *current = lista_faktur->next;
    while (current != NULL) {
        printf("---\nNr faktury: %s\tFirma = %s\n", current->value.nr_faktury, current->value.nabywca->nazwa_firmy);

        // Zamowienia:
        zamowienia *current_zam = lista_zamowien->next;
        while (current_zam != NULL) {
            if (current_zam->value.fakt->nr_faktury == current->value.nr_faktury) {
                printf("Produkt: %s\t\n", current_zam->value.nazwa);
            }

            current_zam = current_zam->next;
        }

        current = current->next;
    }
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
    zamowienie zamowienie1 = stworz_zamowienie("chleb", 3, 0.23, 4.0, &faktura1);
    zamowienie zamowienie2 = stworz_zamowienie("maslo", 8, 0.23, 8.20, &faktura1);
    zamowienie zamowienie3 = stworz_zamowienie("wedlina", 4, 0.23, 19.0, &faktura1);
    zamowienie zamowienie4 = stworz_zamowienie("wedka", 3, 0.23, 21.0, &faktura2);
    zamowienie zamowienie5 = stworz_zamowienie("woda", 6, 0.23, 2.0, &faktura2);
    zamowienie zamowienie6 = stworz_zamowienie("wiertarka", 44, 0.23, 200.0, &faktura3);
    zamowienie zamowienie7 = stworz_zamowienie("betoniarka", 15, 0.23, 1500.0, &faktura3);
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
    /*
    drukuj_firme(firmaturbokolor);
    drukuj_firme(firmanowak);
    drukuj_firme(firmakielbasy);drukuj_zamowienie(zamowienie1);
    drukuj_zamowienie(zamowienie2);
    drukuj_zamowienie(zamowienie3);
    drukuj_zamowienie(zamowienie4);
    drukuj_zamowienie(zamowienie5);
    drukuj_zamowienie(zamowienie6);
    drukuj_zamowienie(zamowienie7);
    drukuj_fakture(faktura1);
    drukuj_fakture(faktura2);
    drukuj_fakture(faktura3);
    drukuj_fakture(faktura4);
    drukuj_fakture(faktura5);
    drukuj_fakture(faktura6);
    pokaz_fakture(faktura1);
    pokaz_fakture(faktura2);
    pokaz_fakture(faktura3);
    pokaz_fakture(faktura4);
    pokaz_fakture(faktura5);
    pokaz_fakture(faktura6);
    */

    faktury_printall_z_zamowieniami();
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
