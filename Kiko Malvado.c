#include <stdio.h>
#include <stdbool.h>

long long int MMC_2(long long int n1, long long int n2) {
	
	long long int resto, x = n1, y = n2;

    do {
        resto = x % y;

        x = y;
        y = resto;

    } while (resto != 0);

    return ( n1 * n2) / x;
}

long long int MMC_Geral(long long int *TQ, int N){
	long long int mmc = TQ[0];
	
	if (N!=1){
		int i = 0;	
		for (i = 1; i < N; i++){
			mmc = MMC_2(mmc, TQ[i]);
		}
	}
	
	return mmc;
	
}

long long int acharX(long long int mmc, long long int T, int N, long long int *TQ){
	long long int i = 0;
	long long int x = 0;
	
	for (i = 2; i <= T; i++){
			long long int Y = MMC_2(mmc, i);
			bool isInvalido = false;
			if (Y == T){
				int j = 0;
				for (j = 0; j < N; j++){
					if (i==TQ[j]){
						isInvalido = true;
						break;
					}
				}
				if (!isInvalido){
					x = i;
					break;	
				}	
			}
	}
	
	return x;
		
}

int main(void){
	int N = 0, T = 0; //número de bolas e tempo das N+1 bolas
	scanf("%d %d", &N, &T);
	
	while((N!=0) && (T!=0)){
		long long int *TQ = (long long int*) malloc(N*sizeof(long long int)); //tempo de quique de cada uma das bolas
		
		int i = 0;
		for (i = 0; i < N; i++){
			scanf("%d", &TQ[i]);
		}
		
		long long int mmc = MMC_Geral(TQ, N);
		long long int x = acharX(mmc, T, N, TQ);
		
		if (x==0){
			printf("impossivel\n");
		}
		else{
			printf("%ld\n", x);
		}
		
		scanf("%d %d", &N, &T);
	}
	
	return 0;
	
}
