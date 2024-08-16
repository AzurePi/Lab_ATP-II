#ifndef HEADER_STRUCTS
#define HEADER_STRUCTS

//definição de tipos de structs usadas em main.c

typedef struct data {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct ano {
  int ano;
  int semestre;
} Ano;

typedef struct aluno {
  /*
   Vetor que vai ter o tamanho de qtd de aulas. Cada índice é uma aula, e cada
   indice vai ter P ou F.
  */
  int numero; // entre 1 e 50
  char nome[51];
  float *nota;     // a ser mallocado depois, quando souber quantas provas na
                   // disciplina; entre 0.0 e 10.0
  float notaFinal; // entre 0.0 e 10.0, mudar somente na hora de imprimir
  char *presenca;  //"P" ou "F"
} Aluno;

typedef struct aula {
  int ordem; // começando de 1
  Data data; // igual ou posterior ao início do semestre
  int horas; // default: 2 horas
  char conteudo[256];
  char tipo; // N normal A atividade
} Aula;

typedef struct atividade // prova ou trabalho
{
  char nome[51];
  char tipo;  //"P" prova, "T" trabalho, "E" exame
  Data data;  // igual ou posterior ao início do semestre
  float peso; // entre 0% e 100%
} Ativ;

typedef struct disciplina {
  char codigo[11];
  char nome[51];
  Ano semestre;           // semestre 1 ou 2; ano 2013 a 2030
  int numAlunos;          // quantidade de alunos matriculados, max 50
  int qtdProvas;          // quantidade de provas, max 4
  int qtdTrabalhos;       // quantidade de trabalhos, max 10
  int cargaPrevista; // default 60 horas
  int cargaRealizada;
  int horasPorAula;
  float notaMin; // nota mínima para aprovação, entre 0 e 10, default 5.0
  float frequenciaMin; // frequência mínima para aprovação, entre 0 e 100, default 70
  Aluno *alunos; // aponta para o primeiro elemento da lista aluno da disciplina
  Ativ *atividade;
  Aula *aula;
//int preenchida 
} Disciplina;

typedef struct professor {
  char nome[51];
  int qtdMaterias; // max 5
  Disciplina *disciplina; 
  /*
   Caso o o usuario queira aumentar o numero de disciplinas, podemos usar o
   realloc.

  */
} Prof;

#endif