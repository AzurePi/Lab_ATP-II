#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(){
	char frase[201];
	int len, i;
	int pal = 1;
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	scanf(" %[^\n]s", frase);
	len = strlen(frase);
	
	for(i = 0; i<len; i++)
	{
		if(frase[i] == ' ')
			pal++;
	}
	
	printf("Há %d palavras", pal);

	return 0;
}
