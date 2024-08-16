#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main(){
	int quant[12][4]; //quantidade de cada produto por m�s
	float cl[4][2]; //matriz custo e lucro de cada produto
	int tot[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //total mensal
	int totprod[4] = {0, 0, 0, 0}; //total de cada produto
	int total = 0;
	float financa[12][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}; //matriz de custo lucro mensal
	float custo = 0, lucro = 0; //totais anuais
	int i, j, k;
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	//custo e lucro aleat�rios
	for(i = 0; i < 4; i++){
		for(j = 0; j < 2; j++){
			cl[i][j] = (float)(i + j) * (rand() % 100) / 13;
		}
	}
	

	for(i = 0; i < 12; i++){
		for(j = 0; j < 4; j++){
			quant[i][j] = (i+j) * (rand() % 500); //quantidades aleat�rias
			
			totprod[j] += quant[i][j]; //quantidade anualmente fabricada de cada produto
			tot[i] += quant[i][j]; //quantidade total de produtos por m�s
			total += quant[i][j]; //total anual de produtos
			
			for(k = 0; k < 2; k++){
				financa[i][k] += cl[j][k] * quant[i][j];
				if(k == 0)
					custo += cl[j][k] * quant[i][j];
				if(k == 1)
					lucro += cl[j][k] * quant[i][j];
			}
		}
	}
	
	for(i = 0; i < 12; i++){
		printf("Total de produtos fabricados no m�s %d: %d\n", i+1, tot[i]);
	}
	
	printf("\n");
		
	for(i = 0; i < 4; i++){
		printf("Total do produto %d fabricados no ano: %d\n", i+1, totprod[i]);
	}
	
	printf("\n");
		
	printf("Produ��o anual total: %d\n\n\n", total);
	
	for(i = 0; i < 12; i++){
		printf("Custo total do m�s %d: %.2f\n", i+1, financa[i][0]);
		printf("Lucro total do m�s %d: %.2f\n\n", i+1, financa[i][1]);
		
	}
	
	printf("Custo anual: %.2f\n", custo);
	printf("Lucro anual: %.2f", lucro);
		
	return 0;
}
