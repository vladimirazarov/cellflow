/**
 * @author Vladimir Azarov
 */

#define N 3

void Dynamic(double t, double *st, double *der){
    der[0] = st[1];
    der[1] = (st[0]*3 - sin(st[1]))/7;
}
void STEP(double *t, double *stav, double krok){
    double k1[N];
    double k2[N];
    double stav_polovina[N];
    Dynamic(*t, stav, k1); 
    for (int i = 0; i < N; i++){
        stav_polovina[i] = stav[i] + k1[i] * krok/2;
    }
    Dynamic(*t + krok/2, stav_polovina, k2);
    for (int i = 0; i < N; i++){
        k1[i] = stav[i] + krok * k2[i];
    }
    *t = *t + krok;
    Dynamic(*t, k1, stav);
}

void Sim(double t_start, double t_end, double *start_values, double step){
    double cur_values[N];
    double cur_step = step;
    double cur_t = t_start;
    // start_values obsahuje pocatecni podminky
    for (int i = 0; i < N; i++){
        cur_values[i] = start_values[i];
    }
    while (cur_t <= t_end){
        if (cur_t + cur_step * 1.01 > t_end)
            cur_step = t_end - cur_t;
        STEP(&cur_t, cur_values, cur_step);
    }
}


