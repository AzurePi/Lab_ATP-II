/*
Crie um programa que:
	- Receba o pre�o de 10 produtos e armazene-os em um vetor
	- Receba a quantidade estocada de cada um desses produtos, em 5 aramaz�ns diferentes, utilizando uma matriz
O programa dever� calcular e mostrar:
	- A quantidade de produtos estocados em cada um dos �rmazens
	- A quantidade de cada um dos produtos estocados em todos os �rmazens juntos
	- O pre�o do produto que possui maior estoque em um �nico �rmazem
	- O menor estoque armazenado
	- O custo de cada �rmazem
*/
#include <stdio.h>
#include <locale.h>

int main(){
	float quant[5][10], quantarm[5] = {0, 0, 0, 0, 0}, quantprod[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	float max = 0, min;
	float preco[10], custo[5] = {0, 0, 0, 0, 0};
	int i, j, prod;
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	printf("\tPre�o de cada produto:\n");
	for(i = 0; i<10; i++)
	{
		printf("Produto %d: ", i+1);
		scanf("%f", &preco[i]);
	}
	
	printf("\n\n\tQuantidade de produto em cada armaz�m:\n");
	
	for(i = 0; i<5; i++)
	{
		printf("Armaz�m %d:\n", i+1);
		for(j = 0; j<10; j++)
		{
			printf("\t - Produto %d: ", j+1);
			scanf("%f", &quant[i][j]);
			
			quantarm[i] += quant[i][j];
			quantprod[j] += quant[i][j];
			
			if(quant[i][j] > max)
			{
				max = quant[i][j];
				prod = j;
			}
			
			if(i == 0 && j == 0)
				min = quant[i][j];
			else if(quant[i][j] < min)
				min = quant[i][j];
		}
		
		for(j = 0; j<10; j++)
			custo[i] += quant[i][j] * preco[j];
		
		printf("\n");
	}
	
	printf("\tQuantidade armazenada em cada armaz�m:\n");
	for(i = 0; i<5; i++)
		printf("Armaz�m %d: %.0f\n", i+1, quantarm[i]);
	
	printf("\n");
	
	printf("\tQuantidade total de cada produto:\n");
	for(i = 0; i<10; i++)
		printf("Produto %d: %.0f\n", i+1, quantprod[i]);
	
	printf("\n");
	
	printf("Pre�o do produto com maior estoque em um �nico armaz�m: %.2f\n", preco[prod]);
	printf("Menor estoque armazenado: %.0f\n", min);
	
	printf("\n");
	
	printf("\tCusto total de cada armaz�m:\n");
	for(i = 0; i<5; i++)
		printf("Armaz�m %d: %.2f\n", i+1, custo[i]);
	
	return 0;
}
