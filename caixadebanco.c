#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//By Yure Pablo em 20/05/2019
//Este programa lê transações de diversos clientes e calcula...
//QD- quantidade de depósitos; QS - Quantidade de Saques; SF - Saldo Final; DFS - saldo final do cliente - Média Diferença Absoluta

int** lerTransacoes(int N, int*T); 
float calcularMedia(int **cliente, int N, int *T);
void imprimir(int **cliente, float media, int N, int *T);
void liberaMemoria(int **cliente, int N, int*T);

int main(void){
	int N = 0;
	float media = 0;
	int **cliente = NULL;
	
	scanf("%d", &N);
	
	int *T = (int *) malloc(N*sizeof(int));
	
	cliente = lerTransacoes(N, T);
	media = calcularMedia (cliente, N, T);
	imprimir(cliente, media, N, T);
	liberaMemoria(cliente, N, T);
	
	return 0;
}

int** lerTransacoes(int N, int *T){
	int i = 0, j = 0;
	int **cliente = NULL; //matriz de transações para cada cliente
	
	cliente = (int **) malloc(N * sizeof(int*)); //quantidade de clientes
	
	for (i = 0; i < N; i++){
		scanf("%d", &T[i]);
		cliente[i] = (int *) malloc(T[i] * sizeof(int)); //quantidade de transações por cliente
		for (j = 0; j < T[i]; j++){
			scanf("%d", &cliente[i][j]);
		}
	}
	
	return cliente;
	
}

float calcularMedia(int **cliente, int N, int *T){
	int i = 0, j = 0;
	float media = 0;
	
	for (i = 0; i < N; i++){
		for (j=0; j < T[i]; j++){
			media += (float) cliente[i][j];
		}
	}
	
	return media/N;	
}

void imprimir(int **cliente, float media, int N, int *T){
	int i = 0, j = 0;
	float DSF = 0;
	int QS = 0, QD = 0;
	float SF = 0;
	
	for (i = 0; i < N; i++){
		for(j = 0; j < T[i]; j++){
			if (cliente[i][j] < 0){ //Saques são representados por números negativos
				QS++; 
			}
			else if (cliente[i][j] > 0){
				QD++;
			}
			SF+=cliente[i][j];
		}
		DSF = fabs (SF - media);
		printf("%d %d %.2f %.2f\n", QD, QS, SF, DSF);
		QS = 0;
		QD = 0;
		SF = 0;
		DSF = 0;
	}
}

void liberaMemoria(int **cliente, int N, int *T){
	int i = 0;
	
	free (T);
	
	for (i = 0; i < N; i++){
		free(cliente[i]);
	}
	
	free(cliente);	
}

