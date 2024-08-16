#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int main(){
	char frase[201];
	char letra[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int quant[26];
	int len, i, j, flag = 0;
	char c;
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	scanf(" %[^\n]s", frase);
	len = strlen(frase);
	
	for(i = 0; i<26; i++)
		quant[i] = 0;
	
	for(i = 0; i<len; i++)
	{
		frase[i] = tolower(frase[i]);
		
		j = 0;
		do
		{
			if(frase[i] == letra[j])
			{
				quant[j]++;
				flag = 1;
			}
			j++;
		}while(flag != 1 && j<26);
	}

	for(i = 0; i<26; i++)
	{
		if(quant[i] > 1)
		{
			c = letra[i];
			printf("A letra %c se repete %d vezes\n", c, quant[i]);
		}
	}

	return 0;
}
