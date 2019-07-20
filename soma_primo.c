#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define UMMILHAO 1000000
#define LIM_PRIMO 2*UMMILHAO

int *num_primo = NULL;
int next = 4;

bool isPrimo(int N){ //para N>=11
        int count = 0;

        while(count < next && num_primo[count] <= sqrt(N)) {
            if (N % num_primo[count] == 0) return false;
            count++;
        }

        num_primo = (int *) realloc(num_primo, (next+1)*sizeof(int));

        num_primo[next++] = N;

        return true;
}

int main(void){
    long long int soma = 17;
    num_primo = (int *) malloc(4*sizeof(int));
    num_primo[0] = 2; num_primo[1] = 3; num_primo[2] = 5; num_primo[3] = 7;

    for (int i = 11; i < LIM_PRIMO; i++){
        if (isPrimo(i)){
            soma+=i;
        }  
    }

    printf("%lld\n", soma);
}