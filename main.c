#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 50
struct Fahrzeuge {
    char NameFahrzeug[MAX_LEN];
    float Kaufpreis;
    float Zinssatz;
    int Laufzeit;
    float TilgungsPlan[MAX_LEN][3];
};

void userEingabe(char *UserName, float *UserRate){
    /*  I set the username no input */
    char UserNameEingabe[MAX_LEN] = "Dustin";
    float UserRateEingabe = 350.0;

    strcpy(UserName, UserNameEingabe);
    *UserRate = UserRateEingabe;
} // end user Eingabe

float preisBerechnung(struct Fahrzeuge *Kfz) {
    // für iteration durch Kfz struct
    int GuenstigtesAutoIndex = 0;

    for(int KfzNummerIndex = 0; KfzNummerIndex <= 2; KfzNummerIndex++){
        float Schulden = Kfz[KfzNummerIndex].Kaufpreis;
        float ZinsSatz = Kfz[KfzNummerIndex].Zinssatz;
        float UserRate = 350;
        float Tilgung = 0;
        float PeriodenZins = 0;

        for(int Zeile = 0; Zeile < MAX_LEN; Zeile++){
            PeriodenZins = Schulden / 100 * (ZinsSatz/12);
            Tilgung = UserRate - PeriodenZins;
            if(Schulden <= Tilgung) {
                Tilgung = Schulden;
            }
            Kfz[KfzNummerIndex].TilgungsPlan[Zeile][0] = Schulden;
            Kfz[KfzNummerIndex].TilgungsPlan[Zeile][1] = PeriodenZins;
            Kfz[KfzNummerIndex].TilgungsPlan[Zeile][2] = Tilgung;
            Schulden = Schulden - Tilgung;
            if(Schulden == 0 ) {
                Kfz[KfzNummerIndex].Laufzeit = Zeile;
                break;
            }
        }
    }
    /*  check which runtime is the shortest*/
    if(Kfz[0].Laufzeit > Kfz[1].Laufzeit && Kfz[1].Laufzeit > Kfz[2].Laufzeit ){
        GuenstigtesAutoIndex = 0;
    }
    if(Kfz[1].Laufzeit > Kfz[2].Laufzeit && Kfz[1].Laufzeit > Kfz[0].Laufzeit ){
        GuenstigtesAutoIndex = 1;
    }
    if(Kfz[2].Laufzeit < Kfz[1].Laufzeit && Kfz[2].Laufzeit < Kfz[0].Laufzeit){
        GuenstigtesAutoIndex = 2;
    }
    return GuenstigtesAutoIndex;
} // end preisBerechnung

void ergebnissAusgabe(char *UserName, float UserRate, struct Fahrzeuge *Kfz, int GuenstigtesAutoIndex){
    printf("\n Name des Kunden: %s \n",UserName);
    printf(" Rate des Kunden: %.2f \n",UserRate);
    printf(" Das guenstigste Fahrzeug ist: %s \n",Kfz[GuenstigtesAutoIndex].NameFahrzeug);
    printf("-----------------------------------------------------------------\n");
    printf("\t\t Schulden \t\t Zinsen \t Tilgung \n");
    printf("-----------------------------------------------------------------\n");
    for(int Zeile = 0; Zeile <= Kfz[GuenstigtesAutoIndex].Laufzeit; Zeile++){
        printf("%d. Monat \t",Zeile+1);
        for(int Spalte = 0; Spalte <= 2; Spalte++){
            printf("%.2f \t\t",Kfz[GuenstigtesAutoIndex].TilgungsPlan[Zeile][Spalte]);
        }
        printf("\n");
    }
    printf("Das Auto ist nach: %d Monaten Abgezahlt\n\n\n",Kfz[GuenstigtesAutoIndex].Laufzeit+1);
} // end ergebnisAusgabe


int main() {
    
int GuenstigtesAutoIndex = 0;
struct Fahrzeuge Kfz[3];

strcpy(Kfz[0].NameFahrzeug, "Opel Corsa");
Kfz[0].Kaufpreis = 12500;
Kfz[0].Zinssatz = 8;

strcpy(Kfz[1].NameFahrzeug, "Scoda Fabia");
Kfz[1].Kaufpreis = 800;
Kfz[1].Zinssatz = 5;

strcpy(Kfz[2].NameFahrzeug, "Renault Clio");
Kfz[2].Kaufpreis = 15000;
Kfz[2].Zinssatz = 6;

char UserName[MAX_LEN];
float UserRate = 0;

    userEingabe(UserName, &UserRate);

    GuenstigtesAutoIndex=preisBerechnung(Kfz);

    ergebnissAusgabe(UserName,UserRate, Kfz, GuenstigtesAutoIndex);

    return 0;
} // end main

