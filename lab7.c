/*
Faça uma função que receba um vetor A de dez elmentos inteiros como parâmetro.
Ao final dessa função, deverá ter sido gerado um vetor B contendo o fatorial de cada elemento de A.
O vetor B deverá ser mostrado no programa principal.
*/

#include <stdio.h>

int fatorial(int a){
	int f = 1;
	
	if(a == 0)
		return 1;
	
	while(a > 1)
	{
		f *= a;
		a--;
	}
	
	return f;
}

int main(){
	int A[10], B[10];
	int i;
	
	for(i = 0; i<10; i++)
	{
		printf("A[%d]: ", i);
		scanf("%d", &A[i]);
		B[i] = fatorial(A[i]);
	}
	
	printf("\n");
	
	for(i = 0; i<10; i++)
		printf("B[%d]: %d\n", i, B[i]);
	printf("\n");
	
	return 0;
}
