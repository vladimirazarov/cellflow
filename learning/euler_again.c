/**
 * @author Vladimir Azarov
 */

#include <stdio.h>

double y[2] = {1.0, 2.0};
double in[2]; double stepsize = 0.1; double end = 20.0;

void f(){
in[0] = y[1];
in[1] = y[1] * 5 - 2;}
void euler(){
    f();
y[0] = y[0] + stepsize * in[0];
y[1] = y[1] + stepsize * in[1];
}

int main(){
double t = 0.0;
while (t < end){
if(t+stepsize>end){
stepsize = end-t;}
euler();
t+=stepsize;
printf("cas: %f, y[0]: %f, y[1]: %f\n", t, y[0], y[1]);
}}