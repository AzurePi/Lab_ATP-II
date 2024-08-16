#ifndef HEADER_FUNCS
#define HEADER_FUNCS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

//protótipos de funções utilizadas em main.c
void inicializar_matriz();
void atualizarMatriz();
void retirarMatriz(int indice);
void iniciar();
int VerificaQtdMateria(int ano, int semestre, int cod);
void firstLogin();
void preencherProfessor(FILE *fp);
void preencherDisciplinas(FILE *disciplina, int i);
void abrirMenu();
void atualizar();
void alterar_materias();
void alterar_disciplina();
int descobreSemestre(int mes);
char *aprovacao(float faltas, int i, int j);
float calcula_final(int i, int j);
float frequencia_aluno(int i, int j);
void relatorios();
int acha_disciplina();
void imprime_aluno(int i, int j);
void individual();
void listagem();
void relatorioNotas();
void exame();
void relatorioAprovados();
void salvar();
void printStructs();
void reatualizar(int opcao, int indice, FILE *fp);


#endif