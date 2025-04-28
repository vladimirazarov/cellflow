/**
 * @author Vladimir Azarov
 */

int main() {
    // Parametry simulace
    int t_cur = 0;           // Aktuální čas
    int t_end = 99;          // Konec simulace
    int processing = 5;      // Doba obsluhy
    int linky = 3;           // Počet volných linek
    int t_new = 1;           // Interval příchodů
    Stack fronta;            // LIFO fronta požadavků
    Calendar calendar;       // Kalendář událostí

    // Inicializace simulace
    calendar.add(0, "ve_fronte");  // Naplánuj první příchod

    // Hlavní smyčka simulace
    while (!calendar.empty()) {
        Event event = calendar.get_first();   // Získej nejbližší událost
        t_cur = event.acttime;                // Aktualizuj aktuální čas

        if (t_cur > t_end) {
            break;                            // Ukončení simulace
        }

        if (event.type == "ve_fronte") {
            if (linky > 0) {                  // Pokud je volná linka
                linky--;                      // Obsazení linky
                calendar.add(t_cur + processing, "uvolnit_linku");  // Naplánuj uvolnění linky
            } else {
                fronta.push(t_cur);           // Ulož požadavek do fronty (LIFO logika)
            }
            calendar.add(t_cur + t_new, "ve_fronte");  // Naplánuj další příchod
        }

        if (event.type == "uvolnit_linku") {
            linky++;                          // Uvolni linku
            if (!fronta.empty()) {            // Pokud jsou požadavky ve frontě
                int request_time = fronta.pop(); // Získej poslední požadavek
                linky--;                      // Obsazení linky
                calendar.add(t_cur + processing, "uvolnit_linku");  // Naplánuj uvolnění
            }
        }
    }
}

void uvolnit_linku() { linky++; }