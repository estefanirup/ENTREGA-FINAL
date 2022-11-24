#include <stdio.h>

struct Tcarro {
  char cliente[50];
  char modelo[20];
  char cor[20];
};

struct Tcarro criaCarro();
void totalDeCombustivel(float *combTotal);
void valorDoCombustivel(float *combValor);
void tamMaxFila(int *filaMax);
void fimDoCombustivel(float *combTotal, int *filaTam, float *totalComb);
void dinheiroEmCaixa(float combLucro);
void carrosAbas(int abastecidos);
void litrosAbastecidos(float abasLitros);
void litrosDisponiveis(float combTotal);
void imprimirInfos(struct Tcarro filas[], int contador, FILE *f);
void arquivoCase6(float totalComb, float valorComb, int tammaxFila,
                  float lucroComb, int abas, float litrosAbasTotal,
                  struct Tcarro filaAtendidos[], int carrosAbastecidos,
                  struct Tcarro filaEspera[], int tamFila);
void abastecerVeiculo(float abasLitros, float combValor, struct Tcarro filaA[],
                      struct Tcarro filaE[], int *abasCarros,
                      float *totalAbasLitros, float *combTotal,
                      float *combLucro, int *filaTam, float abasValor);
void flush_in();