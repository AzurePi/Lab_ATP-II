#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
	int A[5][5];
	int i, j;
	int flag = 1; //assume que toda matriz é simétrica
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	//gera uma matriz aleatória
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			A[i][j] = rand() % 11;
	
	//verifica a simetria
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			if(A[i][j] != A[j][i])
				flag = 0; //a matriz não é simétrica
	
	if(flag == 1)
		printf("A matriz é simétrica");
	else
		printf("A matriz não é simétrica");
		
	return 0;
}
