/**
 * @author Vladimir Azarov
 */

// k1 = f(t, y(t));

// k2 = f(t+h/2, y(t) + k1 * h/2)
// Dole je vypocet dalsiho stavu systemu, v case aktualni cas  + krok
// Slovni vysvetleni: Hodnota funkci v dalsim okamziku je urcena jako
// Hodnota funkce v danem okamziku + krok/4 * (k1+3*k2)
// k1 a k2 jsou koeficienty pro zlepseni presnosti
// y(t+h) = y(t) + h/4*(k1+3*k2)


// 6*y'' + 2y' - 5y = 0
// Urcime pocet integratoru (pocet stavovych promennych)
// 2 integratory (protoze nejvetsi rad je 2)
// y = y (nepotrebujeme)
// v = y' (integrator 1)
// y'' = (5y-2v)/6 (integrator 2)

// Implementace dalsi derivace
// Dynamic(t, st, der)

// Tato funkce v podstate reprezentuje zmenu stavu systemu a tady pracuje 2 integratory
// t je aktualni modelovy cas
// st je aktualni stav stavovych promennych
// der jsou derivovane stavove promenne
// Ucel: definice vstupu pro integratory
void Dynamic(double t, double *st, double *der){
    der[0] = st[1];
    der[1] = (5 * st[0] - 2 * st[1]) / 6;
}
// Cil = numericky vypocet dalsiho stavu systemu
void Step(double *t, double *stav, double krok){
    double k1[2];
    Dynamic(*t, stav, k1); // t je t stav je y(t)


    double k2[2];
    double state_in_half[2];
    state_in_half[0] = stav[0] + k1[0] * krok/2;
    state_in_half[1] = stav[1] + k1[1] * krok/2;

    // NEUDELAL JSEM VYPOCET STAVU SYSTEMU V POLOVINE KROKU
    Dynamic(*t + krok/2, state_in_half, k2);

    stav[0] = stav[0] + krok/4 * (k1[0] + 3 * k2[0]);
    stav[1] = stav[1] + krok/4 * (k1[1] + 3 * k2[1]);

    *t += krok;
}
// Doplnime pocatecni podminky 
// y(0) = 2
// y'(0) = 3
void Simulace(double start_t, double end_t, double step, double min_step, double *state){
    double current_t = start_t; 
    double current_step = step;

    // poc podminky jsou v state
    while(current_t <= end_t){
        if (current_t + current_step * 1.01 > end_t)
            current_step = end_t - current_t;
        Step(&current_t, state, current_step);
}

