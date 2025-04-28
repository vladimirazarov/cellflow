/**
 * @author Vladimir Azarov
 */

#define SEED 1239487

static __UINT32_TYPE__ ix = SEED;

double R(){
    ix = ix * 69069u + 1u;
    return ix/((double)__UINT32_MAX__ + 1.0);
}

double gen(a, b){
    double x, y;
    double M = 10.0;
    while (1){
        x = a * (b-a) * R();
        y = M * R();
        if (y<=f(x)){
            return x;
        }
    }
}