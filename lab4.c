/* Uma empresa fez uma pesquisa de mercado para saber se as pessoas gostaram ou não de um novo produto lançado.
Para isso, forneceu o sexo do entrevistado e sua resposta ("S" para sim e "N" para não). Sabe-se que foram
etrevistadas 10 pessoas. Faça um programa que calcule e mostre:
 - O número de pessoas que responderam sim
 - O número e pessoas que responderam não
 - O número de mulheres que responderam sim
 - A porcentagem de homens que reponderam não dentre todos os homens analisados
*/

#include <stdio.h>

int main() {
  int M = 0, F = 0, S = 0, N = 0, FS = 0, MN = 0; 
  int i;
  float Mporcent, Fporcent;
  char sexo, resp;

  for(i = 0; i<10; i++)
    {
      scanf(" %c", &sexo);
      if(sexo == 'm')
        M++;
      else if(sexo == 'f')
        F++;

      scanf(" %c", &resp);
      if(resp == 's')
        S++;
      else if(resp == 'n')
        N++;

      if(sexo == 'm' && resp == 'n')
        MN++;

      if(sexo == 'f' && resp == 's')
        FS++;
    }
  printf("\n");
  printf("SIM: %d\n", S);
  printf("NÃO: %d\n", N);
  
  if(M != 0)
  	Mporcent = ((float)MN/M)*100;
  else
  	Mporcent = 0;

  if(F != 0)
  	Fporcent = ((float)FS/F)*100;
  else
  	Fporcent = 0;
  
  printf("Homens que responderam não: %.2f%%\n", Mporcent);
  printf("Mulheres que responderam sim: %.2f%%\n", Fporcent);
  
    return 0;
}
  
