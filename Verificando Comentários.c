/* Programa experimental em DataScience
 * Verifica quantas vezes determinada palavra aparece em um comentário previamente formatado
 * Contabiliza comentários negativos e positivos de um determinado produto
 * By Yure Pablo em 28/05/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LIM_STR 20
#define LIM_CHAR 20
#define ASK_WORDS 5
#define WORDS_POSITIVE_OR_NEGATIVE 12
#define MAX_WORDS 200
#define NUM_ADVERBIOS 3

//structs

typedef struct produto {
	char tipo[LIM_CHAR];
	char marca[LIM_CHAR];
} produto;

typedef struct BagOfWords {
	int quant[MAX_WORDS];
	char sentenca[LIM_STR][LIM_CHAR];
} BoW;

//prototipos das funcoes

bool isIgual(char*, char*);
bool leuCaractereEspecial(char *);
void armazenarComentarios(int, produto*, BoW*);
int quantificarPalavra(int, produto*, BoW*, char[ASK_WORDS][LIM_CHAR]);
bool existeNegacao(BoW*, int, int);
float contarPositivosOuNegativos(int, produto*, BoW*, char[ASK_WORDS][LIM_CHAR]);
void responderPerguntas(int, int, produto*, BoW*);
void liberarMemoria(BoW*, produto*);
void finalizarPrograma();

int main(void){
	/* lê a quantidade de sentencas e de perguntas, aloca memoria para os vetores das structs, verifica
	   se a alocacao foi bem sucedida, e chama as funcoes responsaveis por ler as sentencas e perguntas e responder às perguntas */
	   
	int num_sentencas = 0, num_perguntas = 0;

	scanf("%d %d", &num_sentencas, &num_perguntas);
	
	produto *nome_produto = (produto*) malloc(num_sentencas*sizeof(produto));
	
	if (nome_produto == NULL)
	{
        finalizarPrograma();
    }
	
	BoW *comentario = (BoW*) malloc(num_sentencas*sizeof(BoW));
	
	if (comentario == NULL)
	{
        finalizarPrograma();
    }
	
	armazenarComentarios(num_sentencas, nome_produto, comentario);
	responderPerguntas(num_perguntas, num_sentencas, nome_produto, comentario);
	liberarMemoria(comentario, nome_produto);
}

bool isIgual(char *p1, char *p2){
	/* Compara duas palavras utilizando a funcao strcmp(). Se retornar 0, sao iguais.*/
	
	if (strcmp(p1, p2) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool leuCaractereEspecial(char *palavra){
	/* Verifica se o caractere "Ø" de condicao de parada foi lido. */
	
	if (isIgual(palavra, "Ø"))
	{
		return true;
	}
	else
	{
		return false;
	}
		
}	

void armazenarComentarios(int num_sentencas, produto *nome_produto, BoW *comentario){
	/* Le e armazena cada nome_do_produto e cada sentenca (palavra a palavra), e armazena a quantidade de cada palavra da sentenca
	   num vetor cuja posicao é a mesma da palavra exibida pela primeira vez */
	
	char identificador;
	int i = 0, j = 0, k = 0;
	
	for (i = 0; i < num_sentencas; i++)
	{
		scanf("%s %s %c", nome_produto[i].tipo, nome_produto[i].marca, &identificador);

		for (j = 0; j < LIM_STR; j++)
		{
			scanf("%s", comentario[i].sentenca[j]);
			
			if (leuCaractereEspecial(comentario[i].sentenca[j]))
			{
				break;
			}
			
			comentario[i].quant[j] = 1;
			
			for (k = 0; k < j; k++)
			{
				if (isIgual(comentario[i].sentenca[k], comentario[i].sentenca[j]))
				{
					comentario[i].quant[k]++;
					comentario[i].quant[j]--;
					break;
				}
			}
			
		}
	}
}

void responderPerguntas(int num_perguntas, int num_sentencas, produto *nome_produto, BoW *comentario){
	/* Le e armazena cada pergunta, verifica a pergunta que foi feita, e responde essa pergunta. 
	   Como só há dois tipos de pergunta, se ela começar com "palavra" chama a funcao que retorna a quantidade de uma palavra,
	   caso contrario, chama a funcao que retorna a porcentagem de comentarios positivos ou negativos */
	   
	int i = 0, j = 0;
	int quant = 0;
	float porcentagem = 0;
	char pergunta[ASK_WORDS][LIM_CHAR];
	
	for (i = 0; i < num_perguntas; i++)
	{
		for (j = 0; j < ASK_WORDS; j++)
		{
			scanf("%s", pergunta[j]);
		}

		if (isIgual(pergunta[0], "palavra"))
		{
			quant = quantificarPalavra(num_sentencas, nome_produto, comentario, pergunta);
			printf("%d\n", quant);
		}
		else
		{
			porcentagem = contarPositivosOuNegativos(num_sentencas, nome_produto, comentario, pergunta);
			printf("%.1f%%\n", porcentagem);
		}
	}
}

int quantificarPalavra(int num_sentencas, produto *nome_produto, BoW *comentario, char pergunta[5][20]){
	/* Verifica sobre qual produto é a pergunta e retorna a quantidade de vezes que a palavra solicitada 
	aparece na(s) sentenca(s) desse produto */
	
	int i = 0, j = 0;
	int quant = 0;
	
	for (i = 0; i < num_sentencas; i++)
	{
			if ((isIgual(nome_produto[i].tipo, pergunta[3])) && (isIgual(nome_produto[i].marca, pergunta[4])))
			{
				for (j = 0; j < LIM_STR; j++)
				{
			
					if (leuCaractereEspecial(comentario[i].sentenca[j]))
					{
							break;
					}
						
					if (isIgual(comentario[i].sentenca[j], pergunta[1]))
					{
						quant+=comentario[i].quant[j];
					}
				}	
			}
	}
	
	return quant;
}

float contarPositivosOuNegativos(int num_sentencas, produto *nome_produto, BoW *comentario, char pergunta[5][20]){
	/* Verifica sobre qual produto é a pergunta e compara as palavras da(s) sentenca(s) desse produto com 
	   a base de dados de palavras padrões de respostas positivas e negativas, contabilizando o número de mençoes positivas e negativas.
	   Ainda chama uma funcao que verifica a existencia de adverbios que invertem a polaridade. Ao final, retorna a porcentagem de 
	   mencoes negativas ou positivas, a depender da pergunta */
	   
	int i = 0, j = 0, k = 0;
	char positivo[WORDS_POSITIVE_OR_NEGATIVE][LIM_CHAR] = {"bom", "maravilhoso", "otimo", "sensacional", "excelente", "adorei", "gostei", "amei", "eficiente", "boa", "maravilhosa", "otima"};
	char negativo[WORDS_POSITIVE_OR_NEGATIVE][LIM_CHAR] = {"detestei", "odiei", "ruim", "pessimo", "terrivel", "raiva", "odio", "pessima", "lento", "lenta", "fragil", "desisti"};
	int sentencasPositivas = 0, sentencasNegativas = 0;
	int total = 0;
	float porcentagem = 0.0;
	
	for (i = 0; i < num_sentencas; i++)
	{
			int quantPositivos = 0, quantNegativos = 0;
			if ((isIgual(nome_produto[i].tipo, pergunta[3])) && (isIgual(nome_produto[i].marca, pergunta[4])))
			{
				for (j = 0; j < LIM_STR; j++)
				{
					if (leuCaractereEspecial(comentario[i].sentenca[j]))
					{
						break;
					}
					
					for (k = 0; k < WORDS_POSITIVE_OR_NEGATIVE; k++)
					{
						if (isIgual(comentario[i].sentenca[j], positivo[k]))
						{
							if (existeNegacao(comentario, j, i))
							{
								quantNegativos++;
							}
							else
							{
								quantPositivos++;
							}
						}	
						else
						{
							if (isIgual(comentario[i].sentenca[j], negativo[k]))
							{
								if (existeNegacao(comentario, j, i))
								{
									quantPositivos++;
								}
								else
								{
									quantNegativos++;
								}
						
							}
						} 	
					}
				}
				if (quantPositivos > quantNegativos)
				{
					sentencasPositivas++;
				}		
				else
				{
					sentencasNegativas++;
				}
			}

			
	}
	
	total = sentencasPositivas + sentencasNegativas;
	if (isIgual(pergunta[1], "positivos"))
	{
		if (total!=0)
		{
			porcentagem = (float) (sentencasPositivas*100)/total;
		}
		else
		{
			porcentagem = 0;	
		}
		
	}
	else
	{
		if (total!=0)
		{
			porcentagem = (float) (sentencasNegativas*100)/total;
		}
		else
		{
			porcentagem = 0;
		}
		
	}
	
	return porcentagem;
}

bool existeNegacao(BoW *comentario, int indice_palavra, int indice_sentenca){
	/* Verifica se existe um dos tres adverbios de negacao mais frequentes em até tres posicoes antes da palavra analisada. 
	   Note que a funcao garante a comparacao apenas com posicoes positivas */
	
	int i = indice_palavra-1, j = 0;
	char adverbiosDeNegacao[NUM_ADVERBIOS][LIM_CHAR] = {"nao", "jamais", "nunca"};
	bool res = false;
	
	while ((i >= 0) && (i >= indice_palavra-3)) 
	{
		for (j = 0; j < NUM_ADVERBIOS; j++)
		{
			if (isIgual(comentario[indice_sentenca].sentenca[i], adverbiosDeNegacao[j]))
			{
				res = true;
				break;
			}
		}
		i--;
	}	
	
	return res;
}

void finalizarPrograma(){
	/* Encerra forçadamente o programa caso falte memoria para alocar em algum dos vetores */
	
	printf("\n Sem memoria! \n");
    exit(1);
}

void liberarMemoria(BoW *comentario, produto *nome_produto){
	free(comentario);
	free(nome_produto);
}
