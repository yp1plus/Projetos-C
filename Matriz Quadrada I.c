#include <stdio.h>
#include <stdlib.h>

#define TAM_M 100

int M[TAM_M][TAM_M];

void MontarMatriz(int inicio, int fim, int n, int N){
	int i,j;
	
	while (M[(int) (N-1)/2][(int) (N-1)/2] < 1){
	for (i = inicio; i < fim; i++){
			for (j = inicio; j < fim; j++){
				if ((i == inicio) || (i==(fim-1)) || (j==inicio) || (j==(fim-1))){
					M[i][j] = n;
				}
			}
	}
	inicio++;
	fim--;
	n++;
	}
	
}

void imprimirMatriz(int N){
	int i,j;
	
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (j < (N-1)){
				printf ("%3d ", M[i][j]);
				M[i][j] = 0;
			}
			else{
				printf ("%3d\n", M[i][j]);
				M[i][j] = 0;
				if (i == N-1) printf("\n");
			}
		}
	}
}

int main(void){
	int N;
	
	scanf("%d", &N);
	
	while (N!=0){

		MontarMatriz(0, N, 1, N);
		
		imprimirMatriz(N);
		
		scanf("%d", &N);
			
	}
	
	return 0;
}
