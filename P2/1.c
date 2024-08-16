#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define max 1000

typedef struct reg{
	int numero;
	char nome[51], curso[51];
	float nota1, nota2;
}Reg;

Reg registro[max];

int main(){
	FILE *alunos;
	int i = 0, j;
	int op;
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	alunos = fopen("ALUNOS.dat", "w"); 
	
	do
	{
		printf("____________MENU____________\n");
		printf("\t1 - Inserir aluno\n");
		printf("\t2 - Editar nota de aluno\n");
		printf("\t0 - Sair\n");
		scanf("%d", &op);
		
		printf("\n");
		
		if(op == 1)
		{
			registro[i].numero = i;
			
			printf("Nome do aluno: ");
			scanf(" %s", registro[i].nome);
			
			printf("Curso do aluno: ");
			scanf(" %s", registro[i].curso);
			
			printf("Nota 1: ");
			scanf("%f", &registro[i].nota1);
			
			printf("Nota 2: ");
			scanf("%f", &registro[i].nota2);
			
			i++;
			
			for(j = 0; j<i; j++)
				fprintf(alunos, "%d %s %s %.2f %.2f\n", registro[j].numero, registro[j].nome, registro[j].curso, registro[j].nota1, registro[j].nota2);
			
			printf("\nAluno inserido\n\n");
		}else if(op == 2)
		{
			printf("Número do aluno a editar: ");
			scanf("%d", &j);
			
			if(j >= i)
				printf("Número inválido\n\n");
			else
			{
				printf("Nota 1: ");
				scanf("%f", &registro[j].nota1);
				printf("Nota 2: ");
				scanf("%f", &registro[j].nota2);
				
				for(j = 0; j<i; j++)
					fprintf(alunos, "%d %s %s %.2f %.2f\n", registro[j].numero, registro[j].nome, registro[j].curso, registro[j].nota1, registro[j].nota2);
				
				printf("\nAluno editado\n\n");	
			}	
		}	
	}while(op != 0);
	
	fclose(alunos);
	
	return 0;
}
