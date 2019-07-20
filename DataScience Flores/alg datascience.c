/* Programa para calcular a menor distância entre flores e determinados grupos e a quantidade por grupos
 * By Yure Pablo em 12/06/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct representante{
    float x1;
    float y1;
    float x2;
    float y2;
} representante;

float distancia(float x0, float x){
    return (x0 - x) * (x0 - x);
}

float distN(float x0, float x, float y0, float y, float x1, float x2, float y1, float y2){
    return sqrt(distancia(x0, x) + distancia(y0, y) + distancia(x1, x2) + distancia(y1, y2));
}

int main(void){
    FILE *dados;
    representante rp[3] = {{5.4, 3.7, 1.5, 0.2}, { 6.0, 2.2, 4.0, 1.0}, {5.8, 2.7, 5.1, 1.9}};
    float dist;
    float menorD = 2000000;
    int indice;
    int soma[3] = {0};
    dados = fopen("iris.data", "r");

    if (dados == NULL)
    {
        printf("ERRO\n");
        exit(1);
    }

    float x1, y1, x2, y2;
    char aux;
    char tipo[20];
    
    while(!feof(dados))
    {
        fscanf(dados, "%f %c %f %c %f %c %f %c", &x1, &aux, &y1, &aux, &x2, &aux, &y2, &aux);
        for (int i = 0; i < 3; i++)
        {
            dist = distN(x1, rp[i].x1, y1, rp[i].y1, x2, rp[i].x2, y2, rp[i].y2);
            if (dist < menorD)
            {
                menorD = dist;
                indice = i;
            }
        }
        soma[indice]++;
        menorD = 2000000;
        fscanf(dados, "%s ", tipo);
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Total do Grupo %d: %d\n", i, soma[i]);
    }

    return 0;

    
    

    
    


}