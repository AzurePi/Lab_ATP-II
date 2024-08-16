#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(){
	char frase[201];
	char mai[5] = {'A', 'E', 'I', 'O', 'U'};
	char min[5] = {'a', 'e', 'i', 'o', 'u'};
	int len, i, k;
	int maiusculas = 0, minusculas = 0;
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	scanf(" %[^\n]s", frase);
	len = strlen(frase);
	
	for(i = 0; i<len; i++)
	{
		for(k = 0; k<5; k++)
		{
			if(frase[i] == mai[k])
				maiusculas++;
			if(frase[i] == min[k])
				minusculas++;
		}
	}
	
	printf("Há %d vogais minúsculas\n", minusculas);
	printf("Há %d vogais maiúsculas\n", maiusculas);

	return 0;
}
