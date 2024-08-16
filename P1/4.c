#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
	int A[5][5];
	int i, j;
	int flag = 1; //assume que toda matriz � sim�trica
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	//gera uma matriz aleat�ria
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			A[i][j] = rand() % 11;
	
	//verifica a simetria
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			if(A[i][j] != A[j][i])
				flag = 0; //a matriz n�o � sim�trica
	
	if(flag == 1)
		printf("A matriz � sim�trica");
	else
		printf("A matriz n�o � sim�trica");
		
	return 0;
}
