/**
 * @author Vladimir Azarov
 */

typedef struct
{
    double acttime;
} Event;
typedef struct
{
    int dummy;
} Calendar;

Event calendar_get();

int main(int argc, char *argv)
{
    Event event;
    Calendar calendar;
    double t_cur, t_end, step_def, step;
    double *state_vars;
    while(t_cur < t_end){
        if (t_cur + step > t_end){
            step = t_end - t_cur; 
        }
        // obnova integratoru
        f(state_vars);
        // euler step
        euler();
        t_cur+=step;
    }
}