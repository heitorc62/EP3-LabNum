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
        valPontos[j] = valor;  
    }
    return valPontos;
}



double* lagrange(int totalPontosConhecidos, double pontosX[], double pontosY[], int totalPontosInterpolados, double xInterpolados[]){
    double *lPontos = valoresL(totalPontosConhecidos, pontosX, totalPontosInterpolados, xInterpolados);
    double *valorPontos = valsInterpolado(totalPontosConhecidos, totalPontosInterpolados, pontosY, lPontos);
    free(lPontos);
    return valorPontos;
}


int main(){
    double pontoX[7] = {0, 5, 10, 15, 20, 25, 30};
    double pontY[7] = {0, 1.5297, 9.5120, 8.7025, 2.8087, 1.0881, 0.3537};








    return 0;
}