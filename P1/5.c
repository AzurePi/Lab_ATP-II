#include <stdio.h>

int main(){
	int vetor[18], arranjo[3][6];
	int i, j = 0;
	
	for(i = 0; i < 18; i++){
		scanf("%d", &vetor[i]); //lê os números e armazena no vetor
		
		if(i == 6 || i == 12) //pula a linha da matriz
			j++;
		
		arranjo[j][i % 6] = vetor[i]; //passa o valor do vetor para a matriz
	}
	
	//imprime a matriz
	for(i = 0; i < 3; i++){
		for(j = 0; j < 6; j++)
			printf("%d ", arranjo[i][j]);
		printf("\n");
	}
		
	return 0;
}
