/* Jogo da Memória com três níveis de dificuldade
 * By Yure Pablo em 27/04/2019
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>

#define MAX_RAND 10 //define que o conjunto de numeros gerados aleatoriamente sera de 0 a 9
#define PONTO_POR_VALOR 10 
#define MAX_TENTATIVAS 3

//prototipos das funcoes
void ImprimirSequencia(int, int, int*);
int CompararSequencias(int, int*);
int ContarPontos(int,int,int,int,int*);
void GerarJogo(int, int, int); 

int main(void){ 
	int semente = 0; 
	char nivel;
	
	scanf("%d %c", &semente, &nivel); 
	
	srand (semente); //chamada da funcao srand com parametro definido pelo usuario
	
	switch(nivel){ //comando que determina qual tipo de jogo sera gerado com base no nivel de dificuldade
		case 'F': 
			{
				GerarJogo(5, 3, 5); //gera um jogo com 5 numeros aleatarios, 3 sequencias diferentes e tempo limite de 5 segundos para memorizacao
				break;
			}
		case 'I':
			{
				GerarJogo(7, 4, 7); //gera um jogo com 7 numeros aleatorios, 4 sequencias diferentes e tempo limite de 7 segundos para memorizacao
				break;
			}
		case 'A':
			{
				GerarJogo(9, 5, 10); //gera um jogo com 9 numeros aleatorios, 5 sequencias diferentes e tempo limite de 10 segundos para memorizacao
				break;
			}
	}
	
	return 0;
}

void ImprimirSequencia(int num_valores, int repeat, int* s){ //funcao que gera e imprime uma sequencia aleatoria
	int i = 0;
	
	for (i = 0; i < num_valores; i++){ //loop que gera uma sequencia ate uma quantidade i de numeros a depender do nivel de dificuldade
		if (repeat == 0){ //se o jogador esta pela primeira vez na sequencia
			s[i] = rand() % MAX_RAND;
		}
		//Obs.: Se o jogador errou, a sequencia tera que ser repetida, por isso nao é gerada uma nova sequencia
		if (i < num_valores - 1){
			printf("%d ", s[i]);
		}
		else{ 
			printf("%d\n", s[i]); 
		}
	}
}

int CompararSequencias(int num_valores, int *sequencia){ //funcao que compara a sequencia impressa com a dada pelo jogador
	int i = 0; 
	int quant_acertos = 0; 
	
	for (i = 0; i < num_valores; i++){ //loop que le um valor x e o compara com o valor respectivo no vetor sequencia
		int x = 0; 

		if (i < num_valores - 1){ 
			scanf("%d ", &x); 
		}
		else{ 
			scanf("%d",&x); 
		}
		if (x == sequencia[i]){ 
			quant_acertos++; 
		}
	}
	
	return quant_acertos;
}

int ContarPontos(int repeat, int num_valores, int quant_acertos, int pontos, int *ganhoMaximo){ //funcao que atualiza os pontos a cada rodada
	int perdaPorErros = 0; //controla a quantidade de erros em cada rodada
	
	if (repeat == 0){ //se o jogador esta pela primeira vez na sequencia
		pontos += num_valores*PONTO_POR_VALOR; 
		*ganhoMaximo = num_valores*PONTO_POR_VALOR; //inicializa o ganhoMaximo da rodada com a quantidade maxima de pontos da sequencia
	}  
	
	perdaPorErros = (num_valores - quant_acertos)*PONTO_POR_VALOR; 

	if (perdaPorErros <= *ganhoMaximo){ 
		pontos -= perdaPorErros; 
		*ganhoMaximo -= perdaPorErros; 
	} 
	else{
		pontos -= *ganhoMaximo;
		*ganhoMaximo = 0;
	}
	
	/*Obs.: ao longo dos loops o ganhoMaximo pode diminuir, entao é preciso testar se o numero de erros é menor do que o maximo que ele pode perder, 
	porque nao é possivel ter pontos negativos na rodada.*/
	
	return pontos;
}
void GerarJogo(int num_valores, int num_sequencias, int tempo){ //funcao que gera o jogo com base no nivel de dificuldade
	int j = 0; 
	int num_tentativas = MAX_TENTATIVAS; 
	int sequencia[9]; 
	int repeat = 0; 
	int quant_acertos = 0; 
	int pontos = 0; 
	int ganhoMaximo = 0; 
	int *g = &ganhoMaximo; 
	
	for (j=1; j <= num_sequencias; j++){ //loop principal que testa j sequencias a depender do nivel de dificuldade
		do{ 
			printf("Sequencia #%d:\n", j); 

			ImprimirSequencia(num_valores, repeat, sequencia);
			
			quant_acertos = CompararSequencias(num_valores, sequencia);
			
			pontos = ContarPontos(repeat, num_valores, quant_acertos, pontos, g);
			
			fflush(stdout); //garante que a sequecia sera exibida ate o tempo proposto
			sleep(tempo); //pausa a execucao do programa ate o tempo definido
			printf("\r                 \r"); //apaga a sequência
			
			if (quant_acertos == num_valores){ //se o jogador memorizou toda a sequencia
				printf("Correto!\n"); 
			}
			else{ 
				printf("Incorreto!\n"); 
				num_tentativas--; 
				repeat++; 
			}	
			
			printf("Tentativas disponiveis: %d\n", num_tentativas); 
			printf("Pontuacao: %d\n", pontos); 
			
			if (num_tentativas == 0){ 
				printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
				break; //encerra o loop while
			} 
		} while (num_valores != quant_acertos); //enquanto o jogador nao acertar toda a sequencia
		
		repeat = 0; //reinicializa a quantidade de repeticoes, porque o jogador esta entrando em uma nova sequencia pela primeira vez
		
		if (num_tentativas == 0){
			break; //encerra o loop for, se nao, mesmo que saisse do while, continuaria executando outras sequencias
		} 

		if (j == num_sequencias){ 
			printf("Otima memoria! Parabens!!!\n");
		} 
	}	
}


