/**
 * @author Vladimir Azarov
 */

    double y[2] = {2.0, 3.0};
    double y_in[2], step = 0.01;

    void Dynamic() {
        y_in[0] = y[1];
        y_in[1] = -3.0 / 4.0 * y[1];
    }

    void Step() {
        Dynamic();
        y[0] = y[0] + step * y_in[0];
        y[1] = y[1] + step * y_in[1];
    }

    void PRINT() {
        printf("%f\n%f\n", y[0], y[1]);
    }

    void SimRun() {
        Calendar cal;
        double t_cur = 0.0;
        cal_init(cal);
        cal_insert(PRINT, 0, PRINTSTEP);
        cal_insert(END, -100, t_end);
        Event e;
        while (1) {
            e = cal_get_first();
            if (e.atime > t_end) {
                END();
                break;
            }

            while (t_cur < e.atime) {
                Step();
                t_cur += step;
            }

            e.run_event();
        }
    }