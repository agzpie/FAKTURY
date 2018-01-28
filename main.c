#include <stdio.h>
#include <malloc.h>
//#include <sys/_null.h>
#include "queue.h"
#include "list.h"
#include "thunderstruct.h"

// FUNKCJE
zamowienie stworz_zamowienie(char* p_nazwa, int p_ilosc, float p_vat, float p_cena_netto) {
    float wartosc_netto = p_ilosc * p_cena_netto;
    zamowienie zam = {
            p_nazwa,
            p_ilosc,
            p_vat,
            p_cena_netto,
            wartosc_netto,
            wartosc_netto * (1 + p_vat)
    };

    return zam;
};

faktura stworz_fakture(char* nr_faktury, firma nabywca, char* data_wystawienia, char* data_sprzedazy, char* sposob_platnosci) {
    faktura fak = {
        nr_faktury,
        nabywca,
        data_wystawienia,
        data_sprzedazy,
        sposob_platnosci
    };

    return fak;
};

firma stworz_firme(char* nazwa_firmy, char* nr_NIP, char* nr_konta) {
    firma fir = {
            nazwa_firmy,
            nr_NIP,
            nr_konta,
    };

    return fir;
};

void drukuj_zamowienie(zamowienie zam) {
    printf("Nazwa = %s\t\t\t wartosc brutto = %f\n", zam.nazwa, zam.wartosc_brutto);
};

void drukuj_fakture(faktura fak) {
    printf("Numer faktury = %s\t Nazwa nabywcy = %s\n", fak.nr_faktury, fak.nabywca.nazwa_firmy);
};

void drukuj_firme(firma fir) {
    printf("Nazwa firmy = %s\t Numer NIP = %s\t Numer konta = %s\n", fir.nazwa_firmy, fir.nr_NIP, fir.nr_konta);
};

int main() {


    //FILE *settings = fopen(*settings.db, "r");



/*
 * ToDo na Sobotę:
 * 1. Struktury dla firmy, faktury i zamówienia.
 * 2. Funkcje przyjmujące wartości wprowadzane przez użytkownika.
 * 3. BARDZO PODSTAWOWE funkcje które przyjmują strukturę i wyświetlają jej dane na ekranie
 * 4. Używaj pascal_case a nie camelCase.
 */

    zamowienie zamowienie1 = stworz_zamowienie("chleb", 3, 0.23, 4.0);
    drukuj_zamowienie(zamowienie1);

    zamowienie zamowienie2 = stworz_zamowienie("maslo", 8, 0.23, 8.20);
    drukuj_zamowienie(zamowienie2);

    firma firmaturbokolor = stworz_firme("firmaturbokolor", "1234567890", "09876543210987654321098765");
    drukuj_firme(firmaturbokolor);

    faktura faktura1 = stworz_fakture("100/2018", firmaturbokolor, "28/01/2018", "20/1/2018", "przelew");
    drukuj_fakture(faktura1);



    /*
    int opcja;
    printf("\tWitaj przybyszu, co chcesz dziś zrobić? Wybierz numer:\n");
    printf("1) Dodaj dane o przedsiebiorcy.\n2)Wystaw fakture VAT.\n3)Usun fakture z bazy danych.\n4)Wyswietl wystawione faktury\n");
    scanf("%d", opcja);
    if (opcja<1 && opcja>4){
        printf("Nie ma takiej opcji. Sprobuj ponownie: ");
        scanf("%d", opcja);
    }
     */

    return 0;
}