#include <stdio.h>

typedef struct {
    char name[50];
    double price;
    double interestRate;
    double financing[50][3];
} Car;

void eingabe(char*, unsigned int* );
Car berechnung(unsigned int);
void ausgabe(Car*, unsigned int, char* );

int main()
{
    Car car;
    unsigned int rate;
    unsigned char name[50];

    eingabe(name, &rate);
    car = berechnung(rate);
    ausgabe(&car, rate, name);


    return 0;
}

void eingabe(char* name, unsigned int* interestRate){

    printf("\n\nHallo.\nName: ");
    scanf("%s", name);

    printf("\nRatensatz: ");
    scanf("%u", interestRate);
}

Car berechnung(unsigned int rate){

    Car cars[3] = {
        { .name = "Opel Corsa", .price = 12500, .interestRate = 8},
        { .name = "Scoda Fabia", .price = 13800, .interestRate = 5},
        { .name = "Renault Clio", .price = 15000, .interestRate = 6}
    };

    unsigned int car;
    unsigned int
            bestIndex = 0,
            lowestRunntime = 51,
            month;

    double instalment, repayment, price;

    for(car = 0; car < 3; car++){
        price = cars[car].price;
        for(month = 0; month < 50; month++){
            instalment = price / 100 * (cars[car].interestRate / 12);
            repayment = rate - instalment;
            if(repayment > price)
                repayment = price;

            cars[car].financing[month][0] = price;
            cars[car].financing[month][1] = instalment;
            cars[car].financing[month][2] = repayment;

            if(price <= repayment)
                break;

            price -= repayment;
        }

        if(lowestRunntime > month){
            lowestRunntime = month;
            bestIndex = car;
        }
    }

    return cars[bestIndex];
}

void ausgabe(Car* car, unsigned int rate, char* name){

    unsigned int month;

    printf("Fahrzeug:\t%s\tName des Kunden:\t%s\n\n", car->name, name);
    printf("Monat\t\tSchulden\tZinsen\t\tTilgung\n");
    for(month = 0; month < 50 ; month++){
        printf("%d. Monat\t%8.2lf\t%8.2lf\t%8.2lf\n", month+1, car->financing[month][0], car->financing[month][1], car->financing[month][2]);
    }
}











