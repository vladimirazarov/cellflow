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
        if (calendar_empty(calendar)){
            t_cur = t_end;
            end_sim();
        }
        event = calendar_get(calendar);
        while((t_cur + step < event.acttime) && (t_cur + step < t_end)){
            f(state_vars);
            rk_or_euler();
            t_cur+=step;
            if(event.acttime > t_end){
                //dokroceni 
                step = t_end - t_cur;
                rk_or_euler();
                t_cur += step;
                end_sim();
            }
            else{
                step = event.acttime - t_cur;
                rk_or_euler();
                t_cur += step;
                execute(event);
                step = step_def;
            }
        }

    }
}