#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main(){
	char frase[201];
	char con[21] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
	int len, i, k;
	int maiusculas = 0, minusculas = 0;
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	scanf(" %[^\n]s", frase);
	len = strlen(frase);
	
	for(i = 0; i<len; i++)
	{
		for(k = 0; k<21; k++)
		{
			con[k] = toupper(con[k]);
			if(frase[i] == con[k])
				maiusculas++;
			con[k] = tolower(con[k]);
			if(frase[i] == con[k])
				minusculas++;
		}
	}
	
	printf("Há %d consoantes minúsculas\n", minusculas);
	printf("Há %d consoantes maiúsculas\n", maiusculas);

	return 0;
}
