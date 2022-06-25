#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double func1(double x){
    return sin(x);
}

double func2(double x){
    return pow((4*x + 3), 3) * 4; 
}

double func3(double x){
    return exp(-log(1 - x))*(1 - x);
}

double monteCarlo(int total, double (*func)(double)){
    double area = 0;
    for(int i = 0; i < total; i++){
        double aleatorio = (double)rand()/(double)RAND_MAX;
        area += func(aleatorio);
    }
    return area/(double)total;
}

int main(){
    void (*func)(double);
    printf("O valor da integral é: %f\n", monteCarlo(10000, func3));
    return 0;
}