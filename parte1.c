#include <stdio.h>
#include <stdlib.h>

double* valoresL(int totalPontosConhecidos, double pontosX[], int totalPontosInterpolados, double interpoladosX[]){
    double* lPontos;
    lPontos = (double*) malloc(totalPontosConhecidos * totalPontosInterpolados * sizeof(double));
    for(int i = 0; i < (totalPontosConhecidos * totalPontosInterpolados); i++) lPontos[i] = 1.0;

    for(int l = 0; l < totalPontosConhecidos; l++){
        for(int auxL = 0; auxL < totalPontosConhecidos; auxL++){
            if(l != auxL){
                for(int j = 0; j < totalPontosInterpolados; j++){
                    lPontos[l + (j*totalPontosConhecidos)] = lPontos[l + (j*totalPontosConhecidos)] * (interpoladosX[j] - pontosX[auxL])/(pontosX[l] - pontosX[auxL]);
                }
            }
        }
    }
    return lPontos;
}

double* valsInterpolados(int totalPontosConhecidos, int totalPontosInterpolados, double* pontosY, double* lPontos){
    double* valPontos;
    valPontos = (double*) malloc(totalPontosInterpolados * sizeof(double));
    for(int j = 0; j < totalPontosInterpolados; j++){
        double valor = 0;
        for(int auxJ = 0; auxJ < totalPontosConhecidos; auxJ++){
            valor += pontosY[auxJ] * lPontos[auxJ + (j * totalPontosConhecidos)];
        }
        //printf("%f\n", valPontos[j]);
        valPontos[j] = valor;  
    }
    return valPontos;
}



double* lagrange(int totalPontosConhecidos, double pontosX[], double pontosY[], int totalPontosInterpolados, double xInterpolados[]){
    double *lPontos = valoresL(totalPontosConhecidos, pontosX, totalPontosInterpolados, xInterpolados);
    double *valorPontos = valsInterpolados(totalPontosConhecidos, totalPontosInterpolados, pontosY, lPontos);
    free(lPontos);
    return valorPontos;
}

double* interpolaY(double valMax, double h, int totalPontosConhecidos, double pontosX[], double pontosY[]){
    double* pontosInterpolados;
    pontosInterpolados = (double*) malloc(((valMax/h) + 1) * sizeof(double));
    for(int i = 0; i < (int)((valMax/h) + 1); i++) pontosInterpolados[i] = i*h;
    double* yInterpolados = lagrange(totalPontosConhecidos, pontosX, pontosY, (valMax/h) + 1, pontosInterpolados);
    return yInterpolados;
}


double trapezio(double valMax, double h, double yInterpolados[]){
    double area = 0;
    for(int i = 0; i < (int)((valMax/h)); i++)
        area += yInterpolados[i] + yInterpolados[i+1];
    return (h/2)*area;
}

double simpson(double valMax, double h, double yInterpolados[]){
    double area = 0;
    for(int i = 0; i < (int)((valMax/h) - 1); i += 2)
        area += yInterpolados[i] + (4*yInterpolados[i+1]) + yInterpolados[i+2];
    return (h/3)*area;
}


int main(){
    double pontosX[7] = {0, 5, 10, 15, 20, 25, 30};
    double pontosY[7] = {0, 1.5297, 9.5120, 8.7025, 2.8087, 1.0881, 0.3537};
    double h = 1;
    int totalPontos = sizeof(pontosX) / sizeof(pontosX[0]);
    double valMax = pontosX[totalPontos - 1];
    double* yInterpolados = interpolaY(valMax, h, totalPontos, pontosX, pontosY);
    double area1 = trapezio(valMax, h, yInterpolados);
    double area2 = simpson(valMax, h, yInterpolados);
    printf("Integral trapezio = %f\n", area1);
    printf("Integral simpson = %f\n", area2);

    
    return 0;
}