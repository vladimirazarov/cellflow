/**
 * @author Vladimir Azarov
 */

// Stavove promenne
// y je vyska micku [aktualni_stavy[0]
// v je rychlost micku [aktualni stavy [1]

// Derivace stavovych promennyc
// derviace_stavu[0] je rychlost
// derivace_stavu[1] je zrychleni (-9.81)

// Vstup:
// aktualni_stav[0] = y (výška)
 // aktualni_stav[1] = v (rychlost)

// Výstup: derivace stavů 0 = rychlost
//                        1 = zrychleni
void derivace(double *aktualni_stavy, double *derivace_stavu) {

    // derivace vysky je rychlost
    derivace_stavu[0] = aktualni_stavy[1];
    // derivace rychlosti je zrychleni 
    derivace_stavu[1] = -9.81;
}

void krok(double *aktualni_cas, double delka_kroku, double *aktualni_stavy){
    // Chceme zjistit jaky je dalsi stav (derivace)
    double derivace_stavu[2];
    // VYPOCET DERIVACE STAVU V AKTUALNIM CASE
    derivace(aktualni_stavy, derivace_stavu); 
    // 0 = zrychleni 1 = konstanta 
    aktualni_stavy[0] = aktualni_stavy[0] + delka_kroku * derivace_stavu[0];
    aktualni_stavy[1] = aktualni_stavy[1] + delka_kroku * derivace_stavu[1];
    *aktualni_cas += delka_kroku;

}

int stavova_udalost(double *aktualni_stavy){
    if (aktualni_stavy[0] <= 0)
    {
        aktualni_stavy[1] = -0.8 * aktualni_stavy[1];
        aktualni_stavy[0] = 0;
        return 1;
    }
    return 0;
}

void simulace(double cas_start, double cas_konec, double *pocatecni_stavy, double delka_kroku, double minimalni_krok){
    double aktualni_cas = cas_start;
    double aktualni_delka_kroku = delka_kroku;
    while (aktualni_cas < cas_konec)
    {
        krok(&aktualni_cas, aktualni_delka_kroku, pocatecni_stavy);
        if (stavova_udalost(pocatecni_stavy))
        {
            aktualni_delka_kroku = delka_kroku;
        }
        else
        {
            aktualni_delka_kroku /= 2;
            if (aktualni_delka_kroku < minimalni_krok)
                aktualni_delka_kroku = minimalni_krok;
        }
    }
}

int main()
{
   double pocatecni_stavy[2];
   pocatecni_stavy[0] = 10;
   pocatecni_stavy[1] = 0;
   simulace(0, 10, pocatecni_stavy, 0.01, 0.001);
   double t = pocatecni_stavy[0] * (-2);
   printf("%f\n", t);
}


