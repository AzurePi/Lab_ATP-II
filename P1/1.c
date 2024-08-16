#include <stdio.h>
#include <locale.h>

int main(){
	int voto;
	int v1 = 0, v2 = 0, v3 = 0, v4 = 0, vn = 0, vb = 0, total = 0;
	float p1, p2, p3, p4, pn, pb;
	
	setlocale(LC_ALL, "PORTUGUESE");
	
	do{
		scanf("%d ", &voto);
		switch(voto){
			case 1: v1++; total++; break;
			case 2: v2++; total++; break;
			case 3: v3++; total++; break;
			case 4: v4++; total++; break;
			case 5: vn++; total++; break;
			case 6: vb++; total++; break;
			default: break;
		}
	}while(voto < 7 && voto > 0); //por algum motivo,
	//só sai do laço na segunda iteração após um número que não seja voto
	
	p1 = ((float)v1 / total) * 100;
	p2 = ((float)v2 / total) * 100;
	p3 = ((float)v3 / total) * 100;
	p4 = ((float)v4 / total) * 100;
	pn = ((float)vn / total) * 100;
	pb = ((float)vb / total) * 100;
	
	printf("Candidato 1: %d votos, %.2f\%\n", v1, p1);
	printf("Candidato 2: %d votos, %.2f\%\n", v2, p2);
	printf("Candidato 3: %d votos, %.2f\%\n", v3, p3);
	printf("Candidato 4: %d votos, %.2f\%\n", v4, p4);
	printf("Votos nulos: %d votos, %.2f\%\n", vn, pn);
	printf("Votos brancos: %d votos, %.2f\%\n", vb, pb);
	
	//considerando um sistema de votação "first-past-the-post"
	if(v1 > v2 && v1 > v3 && v1 > v4)
		printf("O candidato vencedor é o candidado 1");
	else if(v2 > v1 && v2 > v3 && v2 > v4)
		printf("O candidato vencedor é o candidado 2");
	else if(v3 > v1 && v3 > v2 && v3 > v4)
		printf("O candidato vencedor é o candidado 3");
	else if(v4 > v1 && v4 > v2 && v4 > v3)
		printf("O candidato vencedor é o candidado 4");

	return 0;
}
