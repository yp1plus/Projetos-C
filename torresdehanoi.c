#include <stdio.h>

//By Yure Pablo em 21/06/2019
//Este programa contabiliza quantos movimentos são necessários para resolver a torre de hanoi com N discos

void solve(int numDiscos, char origem, char destino, char aux, int *quant){
    if (numDiscos == 1)
    {
        (*quant)++;
    }
    else
    {
        solve(numDiscos - 1, origem, aux, destino, quant);

        (*quant)*=2; //O movimento acima segue o mesmo padrão do movimento posterior de devolver da torre auxiliar para o destino
        (*quant)++;

        //solve(numDiscos - 1, aux, destino, origem, quant);    
    }
}


int main(void){
    int quant = 0;
    int N = 0;
    int i = 1;
    
    scanf("%d", &N);
    while (N!=0)
    {
        solve(N, 'A', 'B', 'C', &quant);
        printf("Teste %d\n", i);
        i++;
        printf("%d\n\n", quant);
        scanf("%d", &N);
        quant = 0;
    }


    return 0;
}
