/**
 * @author Vladimir Azarov
 */

double gen(){
    int N = 10000;
    double E;
    for (int i = 0; i < 10000; i++)
    {
        E += f(30 - 10 * R());
    }
    E = E/10000;
    return 20 * E; 
}