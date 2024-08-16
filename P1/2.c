#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

typedef struct{
	int num, idade, sexo, exp;
}Funcionario;

int main(){
	float h = 0, h2 = 0, h2id = 0, h45 = 0;
	int m = 0;
	int i = 0;
	int size = 1;
	Funcionario *func; //ponteiro para um vetor de Funcionario
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	func = malloc(size*sizeof(Funcionario));
	scanf("%d", &func[i].num);
	scanf("%d", &func[i].idade);
	scanf("%d", &func[i].sexo);
	scanf("%d", &func[i].exp);
	
	if(func[i].sexo == 1){
		h++;
		if(func[i].exp > 2){
			h2++;
			h2id += func[i].idade;
		}
		if(func[i].idade > 45){
			h45++;
		}
	}else if(func[i].idade < 45 && func[i].exp != 0){
		m++;
	}
	
	while(func[i].num != 0){
		size++;
		func = realloc(func, size*sizeof(Funcionario));
		i++;
		scanf("%d", &func[i].num);
		scanf("%d", &func[i].idade);
		scanf("%d", &func[i].sexo);
		scanf("%d", &func[i].exp);
		
		if(func[i].sexo == 1){
			h++;
			if(func[i].exp > 2){
				h2++;
				h2id += func[i].idade;
			}
			if(func[i].idade > 45){
				h45++;
			}
		}else if(func[i].idade < 45 && func[i].exp != 0){
			m++;
		}
	}
	
	h2id = h2id / h2; //cálculo da idade média
	h45 = (h45 / h) *100; //cálculo da porcentagem
	
	printf("A idade média dos homens com mais de 2 anos de experiência é %f\n", h2id);
	printf("A porcentagem de homens com mais de 45 anos é %f\%\n", h45);
	printf("Há %d mulheres com idade inferior a 35 anos e com experiência de serviço\n", m);
	
	return 0;
}
