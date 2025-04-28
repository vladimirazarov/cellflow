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
    double t_cur, t_end, step_def;
    while (!calendar_empty(calendar))
    {
        event = calendar_get(calendar);
        if (event.acttime > t_end){
            break;
        }
        execute(event);
    }
    t_cur = t_end;
}