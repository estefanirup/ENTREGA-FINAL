#include "header.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN "\e[0;36m"
#define WHITE "\e[0;37m"

void totalDeCombustivel(float *combTotal) {

  while (*combTotal <= 0) {
    printf(MAGENTA "-> " WHITE
                   "Informe o total de litros de combustível(usar ponto, não "
                   "vírgula): ");
    scanf("%f", &*combTotal);

    if (*combTotal <= 0) {
      printf(RED "Valor não aceito.\n" WHITE);
      getchar();
      getchar();
      system("clear");
    }
  }
}

void valorDoCombustivel(float *combValor) {
  while (*combValor <= 0) {
    printf(MAGENTA "-> " WHITE
                   "Informe o valor do litro de combustível(usar ponto, não "
                   "vírgula): ");
    scanf("%f", &*combValor);

    if (*combValor <= 0) {
      printf(RED "Valor não aceito.\n" WHITE);
      getchar();
      getchar();
      system("clear");
    }
  }
}

void tamMaxFila(int *filaMax) {
  while (*filaMax <= 0) {
    printf(MAGENTA "-> " WHITE "Informe o tamanho máximo da fila: ");
    scanf("%d", &*filaMax);

    if (*filaMax <= 0) {
      printf(RED "Valor não aceito.\n" WHITE);
      getchar();
      getchar();
      system("clear");
    }
  }
}

void fimDoCombustivel(float *combTotal, int *filaTam, float *totalComb) {
  char combResp;
  printf(RED "Sem combustível!\n" WHITE);
  printf(MAGENTA "\n-> " WHITE
                 "Deseja fornecer um novo total de litros disponíveis "
                 "(s/n)? \n" WHITE);
  printf(
      YELLOW
      "ATENÇÃO: Ao não informar um novo total, todos os veículos da fila serão "
      "liberados! \n" WHITE);
  scanf(" %s", &combResp);
  printf("\n");

  if ((combResp != 's') && (combResp != 'n')) {
    printf(RED "Valor inválido!" WHITE);
  }

  if (combResp == 's') {
    totalDeCombustivel(&*totalComb);
  }

  if (combResp == 'n') {
    printf(RED "\nNão há mais nenhum carro na fila!" WHITE);
    *filaTam = 0;
  }
}

// case 1 relatório
void dinheiroEmCaixa(float combLucro) {
  printf("\nValor total arrecadado com as vendas: " MAGENTA "R$ %.2lf " WHITE,
         combLucro);
}
// case 2 relatório
void carrosAbas(int abastecidos) {
  printf("\nQuantidade de carros atendidos: " MAGENTA "%d" WHITE, abastecidos);
}
// case 3 relatório
void litrosAbastecidos(float abasLitros) {
  printf("\nQuantidade de litros vendida: " MAGENTA "%.2lf L" WHITE,
         abasLitros);
}
// case 4 relatório
void litrosDisponiveis(float combTotal) {
  printf("\nQuantidade de combustível restante no tanque " MAGENTA
         "%.2lf L" WHITE,
         combTotal);
}

void imprimirInfos(struct Tcarro filas[], int contador, FILE *f) {
  for (int i = 0; i < contador; i++) {
    fprintf(f, "Cliente: %s\n", filas[i].cliente);
    fprintf(f, "Modelo do veículo: %s\n", filas[i].modelo);
    fprintf(f, "Cor do veículo: %s\n\n", filas[i].cor);
  }
}

void arquivoCase6(float totalComb, float valorComb, int tammaxFila,
                  float lucroComb, int abas, float litrosAbas,
                  struct Tcarro filaAtendidos[], int carrosAbastecidos,
                  struct Tcarro filaEspera[], int tamFila) {
  FILE *txt;

  txt = fopen("RelatorioPostoDeGasolina.txt", "w");

  if (txt == NULL) {
    printf("Erro ao criar o arquivo");
    exit(0);
  }
  fprintf(txt, "ARQUIVO COM TODAS AS INFORMAÇÕES:\n\n");
  fprintf(txt, " Total de combustível= %.2lf\n", totalComb);
  fprintf(txt, " Valor do combustível= %.2lf\n", valorComb);
  fprintf(txt, " Tamanho máximo da fila= %d\n", tammaxFila);
  fprintf(txt, " Lucro com os abastecimentos= %.2lf\n", lucroComb);
  fprintf(txt, " Carros abastecidos= %d\n", abas);
  fprintf(txt, " Litros abastecidos= %.2lf\n\n", litrosAbas);
  fprintf(txt, "\nVEÍCULOS ATENDIDOS: %d\n", carrosAbastecidos);
  imprimirInfos(filaAtendidos, carrosAbastecidos, txt);
  fprintf(txt, "\nVEÍCULOS NA FILA: %d\n", tamFila);
  imprimirInfos(filaEspera, tamFila, txt);
  fclose(txt);
}

struct Tcarro criaCarro() {

  struct Tcarro aux;
  getchar();
  printf(MAGENTA "\n\nCliente: " WHITE);
  fgets(aux.cliente, 50, stdin);
  aux.cliente[strcspn(aux.cliente, "\n")] = 0;
  printf(MAGENTA "Modelo do veículo: " WHITE);
  fgets(aux.modelo, 20, stdin);
  aux.modelo[strcspn(aux.modelo, "\n")] = 0;
  printf(MAGENTA "Cor do veículo: " WHITE);
  fgets(aux.cor, 20, stdin);
  aux.cor[strcspn(aux.cor, "\n")] = 0;
  fflush(stdin);
  return aux;
}

void flush_in() {
  int ch;
  while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
  }
}

void abastecerVeiculo(float abasLitros, float combValor, struct Tcarro filaA[],
                      struct Tcarro filaE[], int *abasCarros,
                      float *totalAbasLitros, float *combTotal,
                      float *combLucro, int *filaTam, float abasValor) {

  printf(GREEN "\nCarro abastecido e removido da fila!\n" MAGENTA
               "Valor: " WHITE "R$ %.lf",
         abasValor);
  getchar();

  // movimentação das informações do veículo atendido
  filaA[*abasCarros] = filaE[0];

  *abasCarros = *abasCarros + 1;
  *combLucro = (*totalAbasLitros * combValor);

  // movimentação da fila
  for (int i = 0; i < *filaTam; i++) {
    filaE[i] = filaE[i + 1];
  }
  *filaTam = *filaTam - 1;

  printf(MAGENTA "\n\nINFORMAÇÕES GERAIS: " WHITE);
  dinheiroEmCaixa(*combLucro);
  carrosAbas(*abasCarros);
  litrosAbastecidos(*totalAbasLitros);
  litrosDisponiveis(*combTotal);
}
