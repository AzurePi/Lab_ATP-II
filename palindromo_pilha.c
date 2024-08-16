#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct pilha{
	char c;
	struct pilha *prev;
}Pilha;

int main(){
	Pilha *topo = NULL, *aux;
	char pal[50];
	int i, l, flag = 1;
	
	printf("Digite uma palavra: ");
	scanf(" %s", pal);
	l = strlen(pal);
	
	//lendo a string, empilha
	for(i = 0; i<l; i++)
	{
		aux = malloc(sizeof(Pilha));
		aux->c = pal[i];
		aux->prev = topo;
		topo = aux;
	}
	
	//lendo a string, desempilha
	i = 0;
	while(flag == 1 && i<l)
	{
		if(topo->c == pal[i])
		{
			topo = topo->prev;
			i++;
		}else
			flag = 0;
	}
	
	if(topo == NULL)
		printf("A palavra é um palíndromo\n");
	else
		printf("A palavra não é um palíndromo\n");

	return 0;
}
