#include "prototypes.h"
#include "structs.h"

// Declarando as structs globalmente
Prof prof;
int matriz_disciplinas[36][5]; // cada linha representa um semestre, havendo 5
                               // colunas (espaços para matérias a serem
                               // ministradas no semestre)

int main() {
  setlocale(LC_ALL, "Portuguese");
  inicializar_matriz();
  iniciar();

  return 0;
}

// inicializamos a matriz com -1 em todas as posições, sinalizando
// disponibilidade
void inicializar_matriz() {
  int i, j;
  for (i = 0; i < 36; i++)
    for (j = 0; j < 5; j++)
      matriz_disciplinas[i][j] = -1;
}

// preenche matriz de semestre/disciplinas com as disciplinas do professor por
// semestre a partir do arquivo
void atualizarMatriz() {
  int aux;

  for (int i = 0; i < prof.qtdMaterias; i++) {
    aux = VerificaQtdMateria(prof.disciplina[i].semestre.ano,
                             prof.disciplina[i].semestre.semestre, i);
  }
}

// libera espaço da matriz
void retirarMatriz(int indice) {
  int linha, coluna;
  linha = (prof.disciplina[indice].semestre.ano - 2013) * 2 +
          (prof.disciplina[indice].semestre.semestre - 1);
  for (coluna = 0; coluna < 5; coluna++) {
    if (matriz_disciplinas[linha][coluna] == indice) {
      matriz_disciplinas[linha][coluna] = -1;
      return;
    }
  }
}

// verifica a primeira atitude a ser tomada ao iniciar o programa ("criar"
// professor ou importar informações dos arquivos)
void iniciar() {
  FILE *fp, *fd, *materias;
  int ano, semestre, flag;

  fp = fopen("professor.txt", "r");

  if (fp == NULL) // se não há arquivo professor.txt, preenchemos um novo
  {
    fp = fopen("professor.txt", "w");

    printf("Nome do professor: ");
    scanf("%s", prof.nome);
    printf("Quantidade de disciplinas: ");
    scanf("%d", &prof.qtdMaterias);
    fprintf(fp, "%s\n", prof.nome);
    fprintf(fp, "%d\n", prof.qtdMaterias);

    prof.disciplina = malloc(prof.qtdMaterias * sizeof(Disciplina));

    // para cada disciplina
    for (int i = 0; i < prof.qtdMaterias; i++) {
      printf("\n---- Nova disciplina ----\n");
      printf("Ano e semestre: ");
      scanf("%d %d", &ano, &semestre);

      flag = VerificaQtdMateria(ano, semestre, i);
      if (flag) {
        prof.disciplina[i].semestre.ano = ano;
        prof.disciplina[i].semestre.semestre = semestre;
      } else {
        printf("\n Já há 5 disciplinas no semestre");
        // O professor "perde" a disciplina. Aí reajustamos o índice e a
        // quantidade de matérias
        i--;
        prof.qtdMaterias--;
        continue;
      }

      printf("Nome da disciplina: ");
      scanf(" %s", prof.disciplina[i].nome);
      fprintf(
          fp, "%s ",
          prof.disciplina[i]
              .nome); // imprimimos no arquivo do professor o nome das matérias
      printf("Código: ");
      scanf(" %s", prof.disciplina[i].codigo);

      do {
        printf("Número de alunos: ");
        scanf("%d", &prof.disciplina[i].numAlunos);
        if (prof.disciplina[i].numAlunos > 50)
          printf("\nNúmero de alunos excedeu o máximo. Tente novamente.\n");
      } while (prof.disciplina[i].numAlunos > 50);

      do {
        printf("Quantidade de provas: ");
        scanf("%d", &prof.disciplina[i].qtdProvas);
        if (prof.disciplina[i].qtdProvas > 4)
          printf("\nQuantidade de provas execedeu o máximo. Tente novamente");
      } while (prof.disciplina[i].qtdProvas > 4);

      do {
        printf("Quantidade de trabalhos: ");
        scanf("%d", &prof.disciplina[i].qtdTrabalhos);
        if (prof.disciplina[i].qtdTrabalhos > 10)
          printf("\nQuantidade de trabalhos excedeu o máximo. Tente novamente");
      } while (prof.disciplina[i].qtdTrabalhos > 10);

      printf("Duração da aula em horas: ");
      scanf("%d", &prof.disciplina[i].horasPorAula);
      printf("Carga horária prevista da disciplina: ");
      scanf("%d", &prof.disciplina[i].cargaPrevista);
      // carga realizada começa com zero
      // valores de default da disciplina
      prof.disciplina[i].notaMin = 5;
      prof.disciplina[i].frequenciaMin = 0.7;

      // alocando vetores de structs para aulas (e atividades) e alunos (provas
      // e presença)
      prof.disciplina[i].aula = malloc(
          (prof.disciplina[i].cargaPrevista / prof.disciplina[i].horasPorAula) *
          sizeof(Aula));
      prof.disciplina[i].alunos =
          malloc(prof.disciplina[i].numAlunos * sizeof(Aluno));

      for (int j = 0; j < prof.disciplina[i].numAlunos; j++) { // cada aluno
        prof.disciplina[i].alunos[j].presenca =
            malloc((prof.disciplina[i].cargaPrevista /
                    prof.disciplina[i].horasPorAula) *
                   sizeof(char));
        prof.disciplina[i].alunos[j].nota = calloc(
            prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos,
            sizeof(float));
        strcpy(prof.disciplina[i].alunos[j].presenca, "NULL");
      }

      /*Os vetores notas e atividades aparecerão na mesma ordem (cronológica das
atividades - vetor Ativ) Ex: p1, t1, p2, t2, p3 - vetor notas: 10 9 6 4 7 - nota
da p1 é 10, nota da t1 é 9 e etc...
*/

      prof.disciplina[i].atividade = malloc(
          (prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos) *
          sizeof(Ativ)); 

      for (int j = 0; j < prof.disciplina[i].numAlunos; j++) {
        printf("\n---- Preenchendo aluno ----\n");
        printf("Nome: ");
        scanf(" %s", prof.disciplina[i].alunos[j].nome);
        printf("Número: ");
        scanf("%d", &prof.disciplina[i].alunos[j].numero);
      }

      for (int j = 0; j < prof.disciplina[i].cargaPrevista /
                              prof.disciplina[i].horasPorAula;
           j++) {
        strcpy(prof.disciplina[i].aula[j].conteudo, "NULL");
        prof.disciplina[i].aula[j].tipo = 'N';
      }
      for (int j = 0;
           j < prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos;
           j++) {
        strcpy(prof.disciplina[i].atividade[j].nome, "NULL");
        prof.disciplina[i].atividade[j].tipo = 'N';
      }
    }
    fclose(fp);
    firstLogin();
    // printStructs(); função para propósito de testes

  } else { // se há arquivo professor.txt prévio
    char disciplina[54];

    preencherProfessor(fp);

    for (int i = 0; i < prof.qtdMaterias; i++) {
      fscanf(fp, " %s",
             disciplina); // pegamos o nome da disciplina do arquivo professor
      strcat(disciplina, ".txt");
      fd = fopen(
          disciplina,
          "r"); // abrimos o arquivo da disciplina para preencher as structs
      preencherDisciplinas(fd, i);
      fclose(fd);
    }

    fclose(fp);
    atualizarMatriz(); // structs preenchidas e matriz de materias/semestre de
                       // acordo
  }
  printf("\n");
  // printStructs(); função para propósito de testes
  abrirMenu();
}

// percorre a matriz de disciplinas/semestre buscando disponível (-1) e
// preenchendo o espaço. Caso já haja 5 disciplinas no semestre desejado,
// retorna 0
int VerificaQtdMateria(int ano, int semestre, int cod) {
  int indice = (ano - 2013) * 2 + (semestre - 1);

  for (int i = 0; i < 5; i++) {
    if (matriz_disciplinas[indice][i] == -1) {
      matriz_disciplinas[indice][i] =
          cod; // indice dentro do vetor disciplinas do professor
      return 1;
    }
  }
  return 0;
}

// primeira vez que o professor "loga": salvamos as informações nos arquivos
void firstLogin() {
  FILE *professor, *disciplina;
  char disciplinaNome[55];
  int i, j, k;

  // para cada matéria do professor
  for (i = 0; i < prof.qtdMaterias; i++) {
    strcpy(disciplinaNome, prof.disciplina[i].nome);
    strcat(disciplinaNome, ".txt");
    // criamos o arquivo com o nome da disciplina
    disciplina = fopen(disciplinaNome, "w");

    fprintf(disciplina, "%s\n", prof.disciplina[i].nome);
    fprintf(disciplina, "%s\n", prof.disciplina[i].codigo);
    fprintf(disciplina, "%d %d\n", prof.disciplina[i].semestre.ano,
            prof.disciplina[i].semestre.semestre);
    fprintf(disciplina, "%d\n", prof.disciplina[i].numAlunos);
    fprintf(disciplina, "%d %d\n", prof.disciplina[i].qtdProvas,
            prof.disciplina[i].qtdTrabalhos);
    fprintf(disciplina, "%d %d ", prof.disciplina[i].cargaPrevista,
            prof.disciplina[i].cargaRealizada);
    fprintf(disciplina, "%d\n", prof.disciplina[i].horasPorAula);
    fprintf(disciplina, "%f %f\n", 5.0, 0.7);

    // para cada aluno
    for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
      fprintf(disciplina, "%d %s\n", prof.disciplina[i].alunos[j].numero,
              prof.disciplina[i].alunos[j].nome);
      // para cada atividade
      for (k = 0;
           k < prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos;
           k++) {
        fprintf(disciplina, "%f\n", prof.disciplina[i].alunos[j].nota[k]);
      }
      // continua preenchendo informações dos alunos
      fprintf(disciplina, "%f\n", 0.0); // nota final a principio vazia
      fprintf(
          disciplina, "%s\n",
          prof.disciplina[i].alunos[j].presenca); // presença a ser preenchida
    }

    // preenchendo atividades da disciplina
    for (k = 0;
         k < prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos;
         k++) {
      // inicializando campos
      fprintf(disciplina, "%s\n", "NULL");        // nome
      fprintf(disciplina, "%c\n", 78);            // tipo (78 = 'N')
      fprintf(disciplina, "%d %d %d\n", 0, 0, 0); // data
      fprintf(disciplina, "%f\n", 0.0);           // peso
    }

    // preenchendo para cada aula
    for (k = 0;
         k < prof.disciplina[i].cargaPrevista / prof.disciplina[i].horasPorAula;
         k++) {
      // incializando campos
      fprintf(disciplina, "%d\n", 0);             // ordem
      fprintf(disciplina, "%d %d %d\n", 0, 0, 0); // data
      fprintf(disciplina, "%d\n", 2);             // horas default
      fprintf(disciplina, "%s\n", "NULL");        // conteúdo
      fprintf(disciplina, "%c\n", 78);            // tipo (78 = 'N')
    }

    fclose(disciplina);
  }
}

// a partir do arquivo de informações do professor, preenche a struct e
// aloca o vetor de disciplinas
void preencherProfessor(FILE *fp) {
  fscanf(fp, "%s", prof.nome);
  fscanf(fp, "%d", &prof.qtdMaterias);
  prof.disciplina = malloc(prof.qtdMaterias * sizeof(Disciplina));
}

// preenche structs de disciplinas a partir de informações dos arquivos
void preencherDisciplinas(FILE *disciplina, int i) {
  int j = 0, k;

  // para cada matéria do professor
  for (int j = 0; j < prof.qtdMaterias; j++) {
    fscanf(disciplina, " %s", prof.disciplina[i].nome);
    fscanf(disciplina, " %s", prof.disciplina[i].codigo);
    fscanf(disciplina, "%d %d", &prof.disciplina[i].semestre.ano,
           &prof.disciplina[i].semestre.semestre);
    fscanf(disciplina, "%d", &prof.disciplina[i].numAlunos);

    // alocando vetor de alunos
    prof.disciplina[i].alunos =
        malloc(prof.disciplina[i].numAlunos * sizeof(Aluno));

    fscanf(disciplina, "%d %d", &prof.disciplina[i].qtdProvas,
           &prof.disciplina[i].qtdTrabalhos);
    fscanf(disciplina, "%d %d %d", &prof.disciplina[i].cargaPrevista,
           &prof.disciplina[i].cargaRealizada,
           &prof.disciplina[i].horasPorAula);

    // alocando vetor de atividades
    prof.disciplina[i].atividade = malloc(
        (prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos) *
        sizeof(Ativ));

    fscanf(disciplina, "%f %f", &prof.disciplina[i].notaMin,
           &prof.disciplina[i].frequenciaMin);

    // para cada aluno
    for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
      fscanf(disciplina, "%d %s", &prof.disciplina[i].alunos[j].numero,
             prof.disciplina[i].alunos[j].nome);

      // alocando vetor de notas do aluno
      prof.disciplina[i].alunos[j].nota =
          calloc(prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos,
                 sizeof(float));

      // alocando string de presença com a quantidade de aulas
      prof.disciplina[i].alunos[j].presenca = malloc(
          (prof.disciplina[i].cargaPrevista / prof.disciplina[i].horasPorAula) *
          sizeof(char));

      // para cada atividade
      for (k = 0;
           k < prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos;
           k++)
        fscanf(disciplina, "%f ", &prof.disciplina[i].alunos[j].nota[k]);

      // continua preenchendo informações dos alunos
      fscanf(disciplina, "%f", &prof.disciplina[i].alunos[j].notaFinal);
      fscanf(disciplina, " %s", prof.disciplina[i].alunos[j].presenca);
    }

    // preenchendo o resto da disciplina
    // alocando vetor de aulas
    prof.disciplina[i].aula = malloc(
        (prof.disciplina[i].cargaPrevista / prof.disciplina[i].horasPorAula) *
        sizeof(Aula));

    // para cada atividade
    for (k = 0;
         k < prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos;
         k++) {
      fscanf(disciplina, " %s", prof.disciplina[i].atividade[k].nome);
      fscanf(disciplina, " %c", &prof.disciplina[i].atividade[k].tipo);
      fscanf(disciplina, "%d %d %d", &prof.disciplina[i].atividade[k].data.dia,
             &prof.disciplina[i].atividade[k].data.mes,
             &prof.disciplina[i].atividade[k].data.ano);
      fscanf(disciplina, "%f", &prof.disciplina[i].atividade[k].peso);
    }

    // para cada aula
    for (k = 0;
         k < prof.disciplina[i].cargaPrevista / prof.disciplina[i].horasPorAula;
         k++) {
      fscanf(disciplina, "%d", &prof.disciplina[i].aula[k].ordem);
      fscanf(disciplina, "%d %d %d", &prof.disciplina[i].aula[k].data.dia,
             &prof.disciplina[i].aula[k].data.mes,
             &prof.disciplina[i].aula[k].data.ano);
      fscanf(disciplina, "%d", &prof.disciplina[i].aula[k].horas);
      fscanf(disciplina, " %s", prof.disciplina[i].aula[k].conteudo);
      fscanf(disciplina, " %c", &prof.disciplina[i].aula[k].tipo);
    }
  }
}

// menu principal
void abrirMenu() {
  int op;
  do {
    printf("\nSelecione uma operação:\n");
    printf("1 - Atualizar informação\n");
    printf("2 - Imprimir relatórios\n");
    printf("0 - Encerrar programa\n");
    scanf(" %d", &op);

    switch (op) {
    case 1:
      atualizar(); // entra em um novo menu
      break;
    case 2:
      relatorios(); // entra em um novo menu
      break;
    case 0: // sai do switch case e do laço do while
      break;
    default:
      printf("Opção inválida. Tente Novamente.\n");
      break;
    }
  } while (op != 0);
  salvar(); // salvamos todas as informações nos arquivos antes de fechar o
            // programa
  // printStructs(); função para propósitos de teste
}

// atualizar() é chamada como opção do menu principal
void atualizar() {
  int op;

  do {
    printf("\nSelecione uma operação:\n");
    printf("1 - Alterar disciplinas do docente\n");
    printf("2 - Gerenciar disciplina\n");
    printf("3 - Voltar \n");
    scanf("%d", &op);

    switch (op) {
    case 1:
      alterar_materias(); // entra em um novo menu
      break;
    case 2:
      alterar_disciplina(); // entra em um novo menu
      break;
    case 3: // sai do switch case e do laço do while
      break;
    default:
      printf("\nOpção inválida. Tente novamente.\n");
    }
  } while (op != 3);
}

// alterar_materias() é chamada como opção do menu de atualizar()
void alterar_materias() {
  int op, i, j;
  int ano, semestre, ind = 0;
  char checar, codRemove[11];

  do {
    printf("\nSelecione uma operação:\n");
    printf("1 - Adicionar disciplina\n");
    printf("2 - Remover disciplina\n");
    printf("3 - Voltar: \n");
    scanf("%d", &op);

    switch (op) {
    case 1: // Adicionar Matéria

      printf("\nAno e semestre: ");
      scanf("%d %d", &ano, &semestre);

      // verificaremos se o vetor de disciplinas já esta cheio. Se houver
      // espaço, a nova matéria ocupará. Se não houver, o vetor é realocado
      while (strcmp(prof.disciplina[ind].nome, "NULL") != 0 &&
             strcmp(prof.disciplina[ind].nome, "DELETED") != 0 &&
             ind < prof.qtdMaterias) {
        ind++;
      }

      if (VerificaQtdMateria(ano, semestre, ind) == 0)
        printf("Limite de disciplinas do semestre já atingido. Não foi "
               "possível adicionar.\n");
      else {
        if (ind == prof.qtdMaterias) { //é preciso realocar
          prof.disciplina = realloc(prof.disciplina, (prof.qtdMaterias + 1) *
                                                         sizeof(Disciplina));

          printf("\n-- Preenchendo disciplina --\n");
          printf("Nome: ");
          scanf(" %s", prof.disciplina[ind].nome);
          printf("Código: ");
          scanf(" %s", prof.disciplina[ind].codigo);

          prof.disciplina[ind].semestre.ano = ano;
          prof.disciplina[ind].semestre.semestre = semestre;

          do {
            printf("Número de alunos: ");
            scanf("%d", &prof.disciplina[ind].numAlunos);
            if (prof.disciplina[ind].numAlunos > 50)
              printf("\nNúmero de alunos excedeu o máximo. Tente novamente.\n");
          } while (prof.disciplina[ind].numAlunos > 50);

          do {
            printf("Quantidade de provas: ");
            scanf("%d", &prof.disciplina[ind].qtdProvas);
            if (prof.disciplina[ind].qtdProvas > 4)
              printf(
                  "\nQuantidade de provas execedeu o máximo. Tente novamente.");
          } while (prof.disciplina[ind].qtdProvas > 4);

          do {
            printf("Quantidade de trabalhos: ");
            scanf("%d", &prof.disciplina[ind].qtdTrabalhos);
            if (prof.disciplina[ind].qtdTrabalhos > 10)
              printf("\nQuantidade de trabalhos excedeu o máximo. Tente "
                     "novamente.\n");
          } while (prof.disciplina[ind].qtdTrabalhos > 10);

          printf("Carga horária prevista: ");
          scanf("%d", &prof.disciplina[ind].cargaPrevista);
          printf("Foi realizada alguma carga horária (s ou n)? ");
          scanf(" %c", &checar);
          if (toupper(checar) == 'S') {
            printf("Carga horária realizada: ");
            scanf("%d", &prof.disciplina[ind].cargaRealizada);
          } else
            prof.disciplina[ind].cargaRealizada = 0;

          printf("Quantidade de horas por aula: ");
          scanf("%d", &prof.disciplina[ind].horasPorAula);

          printf("Alterar a nota mínima para ser aprovado (s ou n)? ");
          scanf(" %c", &checar);
          if (toupper(checar) == 'S') {
            printf("Nota mínima: ");
            scanf("%f", &prof.disciplina[ind].notaMin);
          } else
            prof.disciplina[ind].notaMin = 5;

          printf("Alterar a frequência para ser aprovado (s ou n)? ");
          scanf(" %c", &checar);
          if (toupper(checar) == 'S') {
            printf("Frequência mínima: ");
            scanf("%f", &prof.disciplina[ind].frequenciaMin);
          } else
            prof.disciplina[ind].frequenciaMin = 0.7;

          // alocando os vetores para nova disciplina
          prof.disciplina[ind].alunos =
              malloc(prof.disciplina[ind].numAlunos * sizeof(Aluno));
          prof.disciplina[ind].atividade =
              malloc((prof.disciplina[ind].qtdProvas +
                      prof.disciplina[ind].qtdTrabalhos) *
                     sizeof(Ativ));
          prof.disciplina[ind].aula =
              malloc((prof.disciplina[ind].cargaPrevista /
                      prof.disciplina[ind].horasPorAula) *
                     sizeof(Aula));

          for (i = 0; i < prof.disciplina[ind].cargaPrevista /
                              prof.disciplina[ind].horasPorAula;
               i++) {
            strcpy(prof.disciplina[ind].aula[i].conteudo, "NULL");
            prof.disciplina[ind].aula[i].tipo = 'N';
          }

          // para cada aluno alocar notas e presença
          printf("\n-- Preenchendo alunos da disciplina --\n");
          for (i = 0; i < prof.disciplina[ind].numAlunos; i++) {
            prof.disciplina[ind].alunos[i].nota =
                calloc(prof.disciplina[ind].qtdProvas +
                           prof.disciplina[ind].qtdTrabalhos,
                       sizeof(float));
            prof.disciplina[ind].alunos[i].presenca =
                malloc((prof.disciplina[ind].cargaPrevista /
                        prof.disciplina[ind].horasPorAula) *
                       sizeof(char));
            // preenchendo informações básicas do aluno
            strcpy(prof.disciplina[ind].alunos[i].presenca, "NULL");
            printf("Nome: ");
            scanf("%s", prof.disciplina[ind].alunos[i].nome);
            printf("Número: ");
            scanf("%d", &prof.disciplina[ind].alunos[i].numero);
          }

          printf("\nDeseja atualizar as aulas dadas da disciplina (s ou n)? ");
          scanf(" %c", &checar);
          if (toupper(checar) == 'S') {
            alterar_disciplina();
          }
        } else { // já há espaço disponível no vetor

          printf("\n--Preenchendo disciplina--\n");
          printf("Nome: ");
          scanf(" %s", prof.disciplina[ind].nome);
          printf("Código: ");
          scanf(" %s", prof.disciplina[ind].codigo);

          prof.disciplina[ind].semestre.ano = ano;
          prof.disciplina[ind].semestre.semestre = semestre;

          do {
            printf("\nNúmero de alunos: ");
            scanf("%d", &prof.disciplina[ind].numAlunos);
            if (prof.disciplina[ind].numAlunos > 50)
              printf("\nNúmero de alunos excedeu o máximo. Tente novamente.\n");
          } while (prof.disciplina[ind].numAlunos > 50);

          do {
            printf("\nQuantidade de provas: ");
            scanf("%d", &prof.disciplina[ind].qtdProvas);
            if (prof.disciplina[ind].qtdProvas > 4)
              printf(
                  "\nQuantidade de provas execedeu o máximo. Tente novamente.");
          } while (prof.disciplina[ind].qtdProvas > 4);

          do {
            printf("\nQuantidade de trabalhos: ");
            scanf("%d", &prof.disciplina[ind].qtdTrabalhos);
            if (prof.disciplina[ind].qtdTrabalhos > 10)
              printf("\nQuantidade de trabalhos excedeu o máximo. Tente "
                     "novamente.\n");
          } while (prof.disciplina[ind].qtdTrabalhos > 10);

          printf("\nCarga horária prevista: ");
          scanf("%d", &prof.disciplina[ind].cargaPrevista);
          printf("Foi realizada alguma carga horária (s ou n)? ");
          scanf(" %c", &checar);
          if (toupper(checar) == 'S') {
            printf("Qual a carga horária que já foi realizada? ");
            scanf("%d", &prof.disciplina[ind].cargaRealizada);
          } else
            prof.disciplina[ind].cargaRealizada = 0;

          printf("\nQuantidade de horas por aula: ");
          scanf("%d", &prof.disciplina[ind].horasPorAula);

          printf("Deseja alterar a nota mínima para ser aprovado? (s ou n) ");
          scanf(" %c", &checar);
          if (toupper(checar) == 'S') {
            printf("Nota mínima: ");
            scanf("%f", &prof.disciplina[ind].notaMin);
          } else
            prof.disciplina[ind].notaMin = 5;

          printf("Deseja alterar a frequência para ser aprovado? (s ou n) ");
          scanf(" %c", &checar);
          if (toupper(checar) == 'S') {
            printf("Frequência mínima: ");
            scanf("%f", &prof.disciplina[ind].frequenciaMin);
          } else
            prof.disciplina[ind].frequenciaMin = 0.7;

          // para cada aluno alocar notas e presença
          printf("\n-- Preenchendo alunos da disciplina --");
          for (i = 0; i < prof.disciplina[ind].numAlunos; i++) {
            printf("\nNome: ");
            scanf("%s", prof.disciplina[ind].alunos[i].nome);
            printf("Número: ");
            scanf("%d", &prof.disciplina[ind].alunos[i].numero);
            strcpy(prof.disciplina[ind].alunos[i].presenca, "NULL");
            for (int j = 0; j < prof.disciplina[ind].qtdTrabalhos +
                                    prof.disciplina[ind].qtdProvas;
                 j++) {
              prof.disciplina[ind].alunos[i].nota[j] = 0;
            }
          }

          for (i = 0; i < prof.disciplina[ind].cargaPrevista /
                              prof.disciplina[ind].horasPorAula;
               i++) {
            strcpy(prof.disciplina[ind].aula[i].conteudo, "NULL");
            prof.disciplina[ind].aula[i].tipo = 'N';
          }

          printf("\nDeseja atualizar as aulas dadas da disciplina? (s ou n): ");
          scanf(" %c", &checar);
          if (toupper(checar) == 'S') {
            alterar_disciplina();
          }
        }
      }
      prof.qtdMaterias++;
      break; // fim do case 1

    case 2: // Remover Matéria
      j = acha_disciplina();
      if (j == -1) // se a disciplina não foi encontrada
        break;     // encerra o processo
      // do contrário, a disciplina está no índice j

      strcpy(prof.disciplina[j].nome, "DELETED"); // marca como removida
      retirarMatriz(j); // libera o espaço na matriz de disciplinas
      prof.qtdMaterias--;
      salvar();
      exit(0);
      break;

    case 3: // sai do switch case e do laço do while
      break;

    default:
      printf("\nOpção inválida. Tente novamente.\n");
    }
  } while (op != 3);
}

// alterar_disciplina() é chamada como opção do menu de atualizar()
void alterar_disciplina() {
  int op, achou = 0;
  int i, ind, aluno, j, k, l;
  char disc[11];
  char atividade[51];

  do {
    printf("\nSelecione uma operação:\n");
    printf("1 - Adicionar aula\n");
    printf("2 - Remover aluno\n");
    printf("3 - Adicionar aluno\n");
    printf("4 - Atualizar notas\n");
    printf("5 - Voltar\n");
    scanf("%d", &op);

    switch (op) {
    case 1: // adicionar aula
      printf("\n");
      ind = acha_disciplina();
      if (ind == -1) // se a disciplina não foi encontrada
        break;       // encerra a operação
      // do contrário, a disciplina está no índice ind
      i = 0;
      achou = 0;

      while (strcmp(prof.disciplina[ind].aula[i].conteudo, "NULL") != 0 &&
             i < (prof.disciplina[ind].cargaPrevista /
                  prof.disciplina[ind].horasPorAula))
        i++; // anda até encontrar a primeira aula vazia

      if (strcmp(prof.disciplina[ind].aula[i].conteudo, "NULL") != 0) {
        printf("\nTodas as aulas já foram ministradas e cadastradas. Tente "
               "novamente.");
        alterar_disciplina();
      } else {
        printf("Número da aula: ");
        scanf("%d", &prof.disciplina[ind].aula[i].ordem);

        printf("Data da aula (dd mm aaaa): ");
        do {
          scanf("%d %d %d", &prof.disciplina[ind].aula[i].data.dia,
                &prof.disciplina[ind].aula[i].data.mes,
                &prof.disciplina[ind].aula[i].data.ano);
          // aula só pode ser adicionada se pertencer
          // ao ano e semestre da disciplina desejada
          if (prof.disciplina[ind].aula[i].data.ano !=
                  prof.disciplina[ind].semestre.ano ||
              descobreSemestre(prof.disciplina[ind].aula[i].data.mes) !=
                  prof.disciplina[ind].semestre.semestre)
            printf("Data não condiz com o período da disciplina. Tente "
                   "novamente.\n");
        } while (prof.disciplina[ind].aula[i].data.ano !=
                     prof.disciplina[ind].semestre.ano ||
                 descobreSemestre(prof.disciplina[ind].aula[i].data.mes) !=
                     prof.disciplina[ind].semestre.semestre);

        printf("Duração: ");
        scanf("%d", &prof.disciplina[ind].aula[i].horas);

        printf("Detalhamento do conteúdo da aula: ");
        scanf(" %s", prof.disciplina[ind].aula[i].conteudo);

        printf("\n-- Preenchendo presenças da aula ('P' ou 'F') --\n");
        for (k = 0; k < prof.disciplina[ind].numAlunos; k++) {
          printf("Nome: %s - ", prof.disciplina[ind].alunos[k].nome);
          scanf(" %c", &prof.disciplina[ind].alunos[k].presenca[i]);
          // indice de presença igual ao da aula.
        }

        printf("\nTipo da aula (N - normal ou A - atividade): ");
        scanf(" %c", &prof.disciplina[ind].aula[i].tipo);

        if (toupper(prof.disciplina[ind].aula[i].tipo) == 'A') {
          j = 0;
          while (strcmp(prof.disciplina[ind].atividade[j].nome, "NULL") != 0 &&
                 j < (prof.disciplina[ind].qtdProvas +
                      prof.disciplina[ind].qtdTrabalhos))
            j++; // busca atividade vazia

          if (strcmp(prof.disciplina[ind].atividade[j].nome, "NULL") != 0)
            printf("\nErro! Todas as atividades já foram cadastradas.");
          else {
            printf("\nNome da atividade: ");
            scanf("%s", prof.disciplina[ind].atividade[j].nome);

            printf("\nProva (P), trabalho (T) ou exame/recuperação (E): ");
            scanf(" %c", &prof.disciplina[ind].atividade[j].tipo);

            // data igual a da aula em que foi dada
            prof.disciplina[ind].atividade[j].data.dia =
                prof.disciplina[ind].aula[i].data.dia;
            prof.disciplina[ind].atividade[j].data.mes =
                prof.disciplina[ind].aula[i].data.mes;
            prof.disciplina[ind].atividade[j].data.ano =
                prof.disciplina[ind].aula[i].data.ano;

            printf("\nPeso da atividade (0 a 1): ");
            scanf("%f", &prof.disciplina[ind].atividade[j].peso);

            printf("\n-- Inserindo notas dos alunos --");
            for (k = 0; k < prof.disciplina[ind].numAlunos; k++) {
              printf("\nAluno: %s \tNota: ",
                     prof.disciplina[ind].alunos[k].nome);
              scanf("%f", &prof.disciplina[ind].alunos[k].nota[j]);
              // nota com mesmo indice da atividade
            }
          }
        }
      }
      break; // fim do case 1 do switch(acao)

    case 2: // remover aluno
      printf("\n");
      ind = acha_disciplina();
      if (ind == -1) // se a disciplina não foi encontrada
        break;       // encerra a operação
      // do contrário, a disciplina está no índice ind
      achou = 0;
      i = 0;

      printf("Número: ");
      scanf("%d", &aluno);

      while (prof.disciplina[ind].alunos[i].numero != aluno &&
             i < prof.disciplina[ind].numAlunos)
        i++;

      if (i == prof.disciplina[ind].numAlunos)
        // saiu do while pela segunda condição
        printf("\nEsse aluno não está matriculado nesta disciplina.");
      else {
        strcpy(prof.disciplina[ind].alunos[i].nome, "DELETED");
        prof.disciplina[ind].numAlunos--;
      }
      salvar();
      exit(0);
      break; // fim do case 2 do switch (acao)

    case 3: // Adicionar aluno
      printf("\n");
      ind = acha_disciplina();
      if (ind == -1) // se a disciplina não foi encontrada
        break;       // encerra a operação
      // do contrário, a disciplina está no índice ind
      achou = 0;
      i = 0;

      if (prof.disciplina[ind].numAlunos == 50)
        printf("Número máximo de alunos atingidos, não é possivel adicionar "
               "mais.\n");
      else {
        while ((strcmp(prof.disciplina[ind].alunos[i].nome, "NULL") != 0 &&
                strcmp(prof.disciplina[ind].alunos[i].nome, "DELETED") != 0) &&
               i < prof.disciplina[ind].numAlunos)
          i++;

        // se já há espaço no vetor, não precisamos realocar
        if (strcmp(prof.disciplina[ind].alunos[i].nome, "DELETED") == 0 ||
            strcmp(prof.disciplina[ind].alunos[i].nome, "NULL") == 0) {
          printf("\n-- Preenchendo informações do aluno a ser inserido --\n");
          printf("Nome: ");
          scanf(" %s", prof.disciplina[ind].alunos[i].nome);

          do {
            printf("Número: ");
            scanf("%d", &prof.disciplina[ind].alunos[i].numero);
          } while (prof.disciplina[ind].alunos[i].numero > 50 ||
                   prof.disciplina[ind].alunos[i].numero < 1);
          strcpy(prof.disciplina[ind].alunos[i].presenca, "NULL");

          // para cada atividade
          for (int j = 0; j < prof.disciplina[ind].qtdTrabalhos +
                                  prof.disciplina[ind].qtdProvas;
               j++)
            prof.disciplina[ind].alunos[i].nota[j] = 0; // zera a nota
        } else {
          // precisa realocar
          prof.disciplina[ind].alunos =
              realloc(prof.disciplina[ind].alunos,
                      (prof.disciplina[ind].numAlunos + 1) * sizeof(Aluno));
          printf("\n-- Preenchendo informações do aluno a ser inserido --\n");
          printf("Nome: ");
          scanf(" %s", prof.disciplina[ind].alunos[i].nome);

          do {
            printf("Número: ");
            scanf("%d", &prof.disciplina[ind].alunos[i].numero);
          } while (prof.disciplina[ind].alunos[i].numero > 50 ||
                   prof.disciplina[ind].alunos[i].numero < 1);

          // realocando vetores do aluno
          prof.disciplina[ind].alunos[i].nota =
              realloc(prof.disciplina[ind].alunos[i].nota,
                      (prof.disciplina[ind].qtdProvas +
                       prof.disciplina[ind].qtdTrabalhos) *
                          sizeof(float));
          prof.disciplina[ind].alunos[i].presenca =
              realloc(prof.disciplina[ind].alunos[i].presenca,
                      (prof.disciplina[ind].cargaPrevista /
                       prof.disciplina[ind].horasPorAula) *
                          sizeof(char));
        }
        prof.disciplina[ind].numAlunos++;
      }
      break; // fim do case 3 do switch(acao)

    case 4: // atualizar notas
      printf("\n");
      ind = acha_disciplina();
      if (ind == -1) // se a disciplina não foi encontrada
        break;       // encerra a operação
      // do contrário, a disciplina está no índice ind

      achou = 0;
      i = 0;
      l = 0;
      printf("Número do aluno: ");
      scanf("%d", &aluno);

      // buscando o aluno cuja nota será alternada
      while (prof.disciplina[ind].alunos[i].numero != aluno &&
             i <= prof.disciplina[ind].numAlunos)
        i++;

      if (i > prof.disciplina[ind].numAlunos)
        printf("Esse aluno não está matriculado nesta disciplina.\n");

      else if (prof.disciplina[ind].alunos[i].numero == aluno) {
        printf("Nome da atividade a ser inserida/atualizada: ");
        scanf(" %s", atividade);

        while (strcmp(prof.disciplina[ind].atividade[l].nome, atividade) != 0 &&
               l <= prof.disciplina[ind].qtdProvas +
                        prof.disciplina[ind].qtdTrabalhos)
          l++;

        if (strcmp(prof.disciplina[ind].atividade[l].nome, atividade) == 0) {
          printf("Nota: ");
          scanf("%f", &prof.disciplina[ind].alunos[i].nota[l]);

        } else
          printf("Atividade não encontrada.\n");
      }
      break;

    case 5: // sai do switch case e do laço do while
      break;

    default:
      printf("\nOpção inválida. Tente novamente.\n");
      break;
    }
  } while (op != 5);
}

// retorna o semestre a partir do mês informado
int descobreSemestre(int mes) {
  if (mes <= 6)
    return 1;
  else
    return 2;
}

// para uma disciplina i, calcula a nota final de um aluno j
float calcula_final(int i, int j) {
  int n = 0;
  float p = 0;  // soma dos pesos das atividades
  float nf = 0; // nota final do aluno

  for (n = 0;
       n < (prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos);
       n++) {
    nf = nf + (prof.disciplina[i].alunos[j].nota[n] *
               prof.disciplina[i].atividade[n].peso);
    // multiplicamos a nota do aluno pelo peso da atividade
    p += prof.disciplina[i].atividade[n].peso;
  }
  nf = nf / p; // média ponderada
  return nf;
}

// determina, em porcentagem, a frequência de presença de um aluno i na
// disciplina j
float frequencia_aluno(int i, int j) {
  float f = 0;
  int a, t;

  // calcula a quantidade de aulas a serem dadas
  t = prof.disciplina[i].cargaPrevista / prof.disciplina[i].horasPorAula;

  for (a = 0; a < t; a++)
    if (toupper(prof.disciplina[i].alunos[j].presenca[a]) == 'P')
      f++;

  // f é a quantidade de aulas assistidas pelo aluno
  f = f * 100 / (float)t; // transforma f em porcentagem

  return f;
}

// relatórios() é chamada como opção do menu principal
void relatorios() {
  int op;

  do {
    do {
      printf("\nSelecione uma operação:\n");
      printf("1 - Situação individual de um aluno\n");
      printf("2 - Listagem geral de uma turma\n");
      printf("3 - Notas mínimas, máximas e média de cada turma\n");
      printf("4 - Alunos de exame\n");
      printf("5 - Aprovados e reprovados\n");
      printf("6 - Voltar\n");
      scanf("%d", &op);

      if (op < 0 || op > 6)
        printf("Opção inválida. Tente novamente.\n");

    } while (op < 0 || op > 6);

    switch (op) {
    case 1: // Situação individual de cada aluno
      printf("\n");
      individual();
      printf("\nOperação encerrada. Voltando ao menu.\n");
      break;
    case 2: // Listagem geral de uma turma
      printf("\n");
      listagem();
      printf("\nOperação encerrada. Voltando ao menu.\n");
      break;
    case 3: // Notas mínimas, máximas e média de cada turma
      printf("\n");
      relatorioNotas();
      printf("\nOperação encerrada. Voltando ao menu.\n");
      break;
    case 4: // Alunos de exame
      printf("\n");
      exame();
      printf("\nOperação encerrada. Voltando ao menu.\n");
      break;
    case 5: // Aprovados e reprovados
      printf("\n");
      relatorioAprovados();
      printf("\nOperação encerrada. Voltando ao menu.\n");
      break;
    case 6: // sai do switch case e do laço do while
      break;
    }
  } while (op != 6);
}

// determina se um aluno está aprovado ou não
char *aprovacao(float faltas, int i, int j) {
  float nf = calcula_final(i, j);

  if (faltas <= prof.disciplina[i].frequenciaMin &&
      nf >= prof.disciplina[i].notaMin)
    return "Aprovado";
  else
    return "Reprovado";
}

int acha_disciplina() {
  int flag = 0, i = 0;
  char cod[11];

  printf("Código da disciplina: ");
  scanf(" %s", cod);

  // procurando a disciplina
  while (strcmp(cod, prof.disciplina[i].codigo) != 0 && i < prof.qtdMaterias)
    i++;

  if (strcmp(cod, prof.disciplina[i].codigo) == 0)
    flag = 1; // encontrou a disciplina

  if (flag == 0) {
    printf("Disciplina não encontrada. Voltando ao menu.\n");
    return -1;
  }
  return i; // a disciplina foi encontrada no índice i
}

// imprime as informações de um aluno de determinada disciplina
void imprime_aluno(int i, int j) {
  int k;
  int qntAulas, falt = 0;
  float faltporc;

  // calculando faltas
  qntAulas = prof.disciplina[i].cargaPrevista / prof.disciplina[i].horasPorAula;
  for (k = 0; k < qntAulas; k++) {
    if (toupper(prof.disciplina[i].alunos[j].presenca[k]) == 'F')
      falt++;
  }
  faltporc = (falt / (float)qntAulas) * 100;

  // imprimindo dados
  printf("Nome: %s\n", prof.disciplina[i].alunos[j].nome);
  printf("Número: %d\n", prof.disciplina[i].alunos[j].numero);
  printf("Quantidade de faltas: %d\n", falt);
  printf("Porcentagem de faltas: %.2f%%\n", faltporc);
  printf("Notas: ");
  for (k = 0;
       k < (prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos);
       k++) {
    printf("%.2f", prof.disciplina[i].alunos[j].nota[k]);
    if (k !=
        (prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos) - 1)
      printf(" ");
    else
      printf("\n");
  }
  printf("Situação: %s\n", aprovacao(faltporc, i, j));
}

// determina a situação individual de um aluno de determinada disciplina
void individual() {
  int num;
  int i, j = 0, flag, k;
  int qntAulas, falt = 0;
  float faltporc = 0;

  printf("Situação individual de um aluno em uma disciplina\n\n");

  i = acha_disciplina();
  if (i == -1) // se a disciplina não foi encontrada
    return;    // encerra a função
  // do contrário, a disciplina está no índice i

  flag = 0; // o aluno ainda não foi encontrado
  printf("Número do aluno: ");
  scanf(" %d", &num);
  printf("\n");

  // procurando o aluno
  while (num != prof.disciplina[i].alunos[j].numero &&
         j < prof.disciplina[i].numAlunos)
    j++;

  if (num == prof.disciplina[i].alunos[j].numero)
    flag = 1; // encontrou o aluno

  if (flag == 0) {
    printf("Aluno não encontrado. Voltando ao menu.\n");
    return;
  }
  // o aluno foi encontrado no índice j
  imprime_aluno(i, j);
}

// lista as informações de todos os alunos de uma disciplina
void listagem() {
  int i, j;

  printf("Listagem geral dos alunos de uma disciplina\n");

  i = acha_disciplina();
  if (i == -1) // se a disciplina não foi encontrada
    return;    // encerra a função
  // do contrário, a disciplina está no índice i

  // para cada aluno na disciplina
  for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
    printf("\n");
    imprime_aluno(i, j);
  }
}

// lista as notas mínima, máxima e média de cada disciplina
void relatorioNotas() {
  int i, j;
  float min, max, med, nf;

  // para cada disciplina i ensinada
  for (i = 0; i < prof.qtdMaterias; i++) {
    printf("\n---- %s ----\n", prof.disciplina[i].nome);

    // inicializando as variáveis
    min = 10;
    max = 0;
    med = 0;

    // para cada aluno j nessa disciplina
    for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
      nf = calcula_final(i, j);

      if (nf < min)
        min = nf;
      if (nf > max)
        max = nf;

      med += nf;
    }
    med = med / prof.disciplina[i].numAlunos;

    // imprimindo:
    printf("Nota mínima: %.2f\n", min);
    printf("Nota máxima: %.2f\n", max);
    printf("Nota média: %.2f\n", med);

    printf("\n");
  }
}

// lista os alunos de determinada disciplina que precisam realizar o exame
void exame() {
  int i, j;
  float f;
  int flag = 0; // assume que ninguém está de recuperação
  float x, nf;

  i = acha_disciplina();
  if (i == -1) // se a disciplina não foi encontrada
    return;    // encerra a função
  // do contrário, a disciplina está no índice i

  printf("\n--- Alunos de Exame em %s ---\n", prof.disciplina[i].nome);
  // para cada aluno
  for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
    // verifica se ele tem a frequência mínima
    f = frequencia_aluno(i, j);
    if (f >= prof.disciplina[i].frequenciaMin) {
      // calcula as notas finais
      nf = calcula_final(i, j);

      // verifica se ele está de recuperação
      if (nf < prof.disciplina[i].notaMin) {
        flag = 1;
        printf("Nome: %s\n", prof.disciplina[i].alunos[j].nome);
        printf("Número: %d\n", prof.disciplina[i].alunos[j].numero);

        // calcula a nota necessária
        x = (2 * prof.disciplina[i].notaMin) - nf;

        printf("Nota necessária no exame: %.2f\n", x);
        printf("\n");
      }
    }
  }

  // se nenhum aluno estava de recuperação
  if (flag == 0)
    printf("Não há alunos de recuperação.\n");
}

void relatorioAprovados() {
  int i, j, k, l = 0;
  int qtd = 0;
  float notaExame, nf;

  i = acha_disciplina();
  if (i == -1)
    return;

  printf("\n---- Aprovados em %s ----", prof.disciplina[i].nome);
  for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
    nf = calcula_final(i, j);
    if (nf >= prof.disciplina[i].notaMin &&
        frequencia_aluno(i, j) >= 100 * prof.disciplina[i].frequenciaMin) {
      printf("\n %s", prof.disciplina[i].alunos[j].nome);
      qtd++;
    }
    // se não houveram alunos aprovados
    if (qtd == 0)
      printf("\nNão houveram aprovações\n");
  }

  printf("\n ---- Reprovados por falta em %s ----", prof.disciplina[i].nome);
  qtd = 0;
  for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
    if (frequencia_aluno(i, j) < 100 * prof.disciplina[i].frequenciaMin) {
      printf("\n %s", prof.disciplina[i].alunos[j].nome);
      qtd++;
    }
  }
  if (qtd == 0)
    printf("\nNão houveram reprovações\n");

  // para cada aluno na disciplina
  for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
    nf = calcula_final(i, j); // calcula sua nota final

    // se a nota final não é o suficiente para passar, e sua frequência é maior
    // ou igual à frequência mínima
    if (nf < prof.disciplina[i].notaMin &&
        frequencia_aluno(i, j) >= 100 * prof.disciplina[i].frequenciaMin) {
      // exige um exame
      printf("\nNota do exame de %s: ", prof.disciplina[i].alunos[j].nome);
      scanf("%f", &notaExame);
      if ((nf + notaExame) / 2 >= prof.disciplina[i].notaMin) {
        printf("Aluno reprovado.");
      } else {
        printf("Aluno aprovado.");
      }
    }
  }
}

// salvamos o conteúdo das structs (atualizado) em arquivos
void salvar() {
  int i, j, k;
  int aux;
  char nomeDisciplinaTemp[51];
  FILE *fp, *fpDisciplina;

  fp = fopen("professor.txt", "w");
  fprintf(fp, "%s\n", prof.nome);
  fprintf(fp, "%d\n", prof.qtdMaterias);

  // para cada disciplina do professor
  for (i = 0; i < prof.qtdMaterias; i++) {
    // se a disciplina não foi deletada
    if (strcmp(prof.disciplina[i].nome, "DELETED") != 0) {
      // cria um arquivo para a disciplina
      strcpy(nomeDisciplinaTemp, prof.disciplina[i].nome);
      fprintf(fp, "%s ", prof.disciplina[i].nome);
      strcat(nomeDisciplinaTemp, ".txt");
      fpDisciplina = fopen(nomeDisciplinaTemp, "w");

      // imprime as informaçẽos da disciplina
      fprintf(fpDisciplina, "%s\n", prof.disciplina[i].nome);
      fprintf(fpDisciplina, "%s\n", prof.disciplina[i].codigo);
      fprintf(fpDisciplina, "%d %d\n", prof.disciplina[i].semestre.ano,
              prof.disciplina[i].semestre.semestre);
      fprintf(fpDisciplina, "%d\n", prof.disciplina[i].numAlunos);
      fprintf(fpDisciplina, "%d %d\n", prof.disciplina[i].qtdProvas,
              prof.disciplina[i].qtdTrabalhos);
      fprintf(fpDisciplina, "%d %d ", prof.disciplina[i].cargaPrevista,
              prof.disciplina[i].cargaRealizada);
      fprintf(fpDisciplina, "%d\n", prof.disciplina[i].horasPorAula);
      fprintf(fpDisciplina, "%f %f\n", prof.disciplina[i].notaMin,
              prof.disciplina[i].frequenciaMin);

      // para cada aluno
      for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
        // se o aluno não foi deletado
        if (strcmp(prof.disciplina[i].alunos[j].nome, "DELETED") != 0) {
          // imprime as informações do aluno
          fprintf(fpDisciplina, "%d %s\n", prof.disciplina[i].alunos[j].numero,
                  prof.disciplina[i].alunos[j].nome);

          // para cada atividade, imprime uma nota
          for (k = 0; k < prof.disciplina[i].qtdProvas +
                              prof.disciplina[i].qtdTrabalhos;
               k++)
            fprintf(fpDisciplina, "%f\n", prof.disciplina[i].alunos[j].nota[k]);

          fprintf(fpDisciplina, "%f\n", prof.disciplina[i].alunos[j].notaFinal);
          fprintf(fpDisciplina, "%s\n", prof.disciplina[i].alunos[j].presenca);
        } else // se o aluno foi deletado
          prof.disciplina[i].numAlunos--;
      }

      // para cada atividade da disciplina
      for (k = 0;
           k < prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos;
           k++) {
        fprintf(fpDisciplina, "%s\n", prof.disciplina[i].atividade[k].nome);
        fprintf(fpDisciplina, "%c\n", prof.disciplina[i].atividade[k].tipo);
        fprintf(fpDisciplina, "%d %d %d\n",
                prof.disciplina[i].atividade[k].data.dia,
                prof.disciplina[i].atividade[k].data.mes,
                prof.disciplina[i].atividade[k].data.ano);
        fprintf(fpDisciplina, "%f\n", prof.disciplina[i].atividade[k].peso);
      }

      // para cada aula da disciplina
      for (k = 0; k < prof.disciplina[i].cargaPrevista /
                          prof.disciplina[i].horasPorAula;
           k++) {
        fprintf(fpDisciplina, "%d\n", prof.disciplina[i].aula[k].ordem);
        fprintf(fpDisciplina, "%d %d %d\n", prof.disciplina[i].aula[k].data.dia,
                prof.disciplina[i].aula[k].data.mes,
                prof.disciplina[i].aula[k].data.ano);
        fprintf(fpDisciplina, "%d\n", prof.disciplina[i].aula[k].horas);
        fprintf(fpDisciplina, "%s\n", prof.disciplina[i].aula[k].conteudo);
        fprintf(fpDisciplina, "%c\n", prof.disciplina[i].aula[k].tipo);
      }
      fclose(fpDisciplina);
    } else // se a disciplina foi deletada
      prof.qtdMaterias--;
  }
  fclose(fp);
}
// ----------------------------------------------------
// função auxiliar para impressão das informações armazenadas
void printStructs() {
  int i, j, k;
  printf("\n%s", prof.nome);
  printf("\n%d", prof.qtdMaterias);
  for (i = 0; i < prof.qtdMaterias; i++) {
    printf("\n DISCIPLINA: \n");
    printf("\nnome: %s", prof.disciplina[i].nome);
    printf("\ncod: %s", prof.disciplina[i].codigo);
    printf("\nsemestre: %d %d", prof.disciplina[i].semestre.ano,
           prof.disciplina[i].semestre.semestre);
    printf("\n num alunos: %d", prof.disciplina[i].numAlunos);
    printf("\n qtd provas e trabalhos: %d %d", prof.disciplina[i].qtdProvas,
           prof.disciplina[i].qtdTrabalhos);
    printf("\n carga prevista e realizada: %d %d",
           prof.disciplina[i].cargaPrevista, prof.disciplina[i].cargaRealizada);
    printf("\n Horas por aula: %d", prof.disciplina[i].horasPorAula);
    printf("\n nota  e freq min: %f %f \n", prof.disciplina[i].notaMin,
           prof.disciplina[i].frequenciaMin);
    printf("\n ALUNO \n");
    for (j = 0; j < prof.disciplina[i].numAlunos; j++) {
      printf("\n nome e numero: %s %d", prof.disciplina[i].alunos[j].nome,
             prof.disciplina[i].alunos[j].numero);
      printf("\n notas: ");
      for (k = 0;
           k < prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos;
           k++) {
        printf("%f ", prof.disciplina[i].alunos[j].nota[k]);
      }
      printf("%f", prof.disciplina[i].alunos[j].notaFinal);
      printf("\n presenca: %s \n", prof.disciplina[i].alunos[j].presenca);
      printf("\n ATIVIDADE: \n ");
      for (k = 0;
           k < prof.disciplina[i].qtdProvas + prof.disciplina[i].qtdTrabalhos;
           k++) {
        printf("\n nome e tipo: %s %c", prof.disciplina[i].atividade[k].nome,
               prof.disciplina[i].atividade[k].tipo);
        printf("\n data: %d %d %d", prof.disciplina[i].atividade[k].data.dia,
               prof.disciplina[i].atividade[k].data.mes,
               prof.disciplina[i].atividade[k].data.ano);
        printf("\n peso: %f \n", prof.disciplina[i].atividade[k].peso);
      }
      printf("\n AULA:\n");
      for (k = 0; k < prof.disciplina[i].cargaPrevista /
                          prof.disciplina[i].horasPorAula;
           k++) {
        printf("\n ordem: %d", prof.disciplina[i].aula[k].ordem);
        printf("\n data: %d %d %d", prof.disciplina[i].aula[k].data.dia,
               prof.disciplina[i].aula[k].data.mes,
               prof.disciplina[i].aula[k].data.ano);
        printf("\n horas: %d", prof.disciplina[i].aula[k].horas);
        printf("\n conteudo e tipo: %s %c", prof.disciplina[i].aula[k].conteudo,
               prof.disciplina[i].aula[k].tipo);
      }
    }
  }
}