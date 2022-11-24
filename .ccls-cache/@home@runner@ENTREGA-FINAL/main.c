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

int main() {
  int fila = 0, menu = 0, i = 0, tammaxFila = 0, tamFila = 0,
      carrosAbastecidos = 0, opcao1 = 0, opcao2 = 0;
  float valorComb = 0, totalComb = 0, lucroComb = 0, litrosAbasTotal = 0,
        litrosAbas = 0, valorAbas = 0;
  char opLitro;
  struct Tcarro *filaEspera, *filaAtendidos;

  printf(MAGENTA
         "Autor: Estéfani Rup\nEsse programa tem como objetivo melhor o "
         "processo de gerenciamento em um posto de combustíveis! \n\n\n" WHITE);

  totalDeCombustivel(&totalComb);
  valorDoCombustivel(&valorComb);
  tamMaxFila(&tammaxFila);

  filaEspera = (struct Tcarro *)malloc(tammaxFila * sizeof(struct Tcarro));
  filaAtendidos = (struct Tcarro *)malloc(1 * sizeof(struct Tcarro));

  while (opcao1 != 5) {

    system("clear");
    opcao2 = 0;

    printf(MAGENTA "\n\nMENU PRINCIPAL" WHITE);
    printf("\nInforme a opção desejada: \n\n");
    printf(MAGENTA "[1]" WHITE " Adicionar um veículo na fila;\n");
    printf(MAGENTA "[2]" WHITE " Informar abastecimento;\n");
    printf(MAGENTA "[3]" WHITE " Exibir veículos na fila;\n");
    printf(MAGENTA "[4]" WHITE " Relatório;\n");
    printf(MAGENTA "[5]" WHITE " Encerrar.\n\n");
    scanf("%d", &opcao1);

    switch (opcao1) {

    // ADICIONAR UM VEÍCULO NA FILA
    case 1:
      // validação se a fila não está no tamanho máximo
      if (tammaxFila != tamFila) {

        if (totalComb != 0) { // validação se há combustível
          printf(GREEN "Carro adicionado a fila de abastecimento." WHITE);

          // vetor fila de espera recebe infos do veículo
          filaEspera[tamFila] = criaCarro();
          tamFila = tamFila + 1;

        } else {
          fimDoCombustivel(&totalComb, &tamFila, &totalComb);
        }

      } else {
        printf(RED "Fila cheia!" WHITE);
      }
      break;

    // INFORMAR ABASTECIMENTO
    case 2:
      if (tamFila != 0) { // verificação se há veículos na fila

        if (totalComb != 0) { // verificação se há combustível
          while (litrosAbas <= 0) {
            printf(MAGENTA "\n-> " WHITE
                           "Informe quantos litros gostaria de abastecer: ");
            scanf("%f", &litrosAbas);

            if (litrosAbas <= 0) {
              printf(RED "Valor inválido" WHITE);
              system("clear");
            }
          }

          // verificação se há a quantidade que o cliente deseja abastecer
          if (litrosAbas <= totalComb) {
            if (litrosAbas == totalComb) {
              printf(
                  RED
                  "\nATENÇÃO:" YELLOW
                  " Esse veículo acaba de abastecer o total de "
                  "combustível disponível.\nCom isso, na próxima tentativa de "
                  "abstecimento, todos os veículos da fila poderão ser" RED
                  " LIBERADOS!\n" WHITE);
            }
            // alocação
            filaAtendidos = (struct Tcarro *)realloc(
                filaAtendidos, (carrosAbastecidos + 1) * sizeof(struct Tcarro));

            valorAbas = litrosAbas * valorComb;
            litrosAbasTotal = litrosAbasTotal + litrosAbas;
            totalComb = totalComb - litrosAbas;
            abastecerVeiculo(litrosAbas, valorComb, filaAtendidos, filaEspera,
                             &carrosAbastecidos, &litrosAbasTotal, &totalComb,
                             &lucroComb, &tamFila, valorAbas);

          } else {
            /* Validação para quando um carro deseja abastecer uma quantidade
               maior de litros do que a disponível */
            printf(RED "Não há combustível suficiente para esse "
                       "abastecimento.\n" WHITE);
            printf(MAGENTA "\n-> " WHITE "Litros disponiveis: %.2lf\n",
                   totalComb);
            printf(MAGENTA "\n-> " WHITE
                           "Deseja abastecer a quantidade total de litros "
                           "disponiveis (s/n)? \n" WHITE);
            printf(
                RED
                "ATENÇÃO:" YELLOW " Se for abastecido, não haverá mais "
                "combustível disponível\n         e, na próxima tentativa de "
                "abstecimento, todos os veículos da fila poderão ser" RED
                " LIBERADOS!\n" WHITE);
            scanf(" %s", &opLitro);
            system("clear");

            if ((opLitro != 's') && (opLitro != 'n') && (opLitro != 'S') &&
                (opLitro != 'N')) {
              printf(RED "Valor inválido!" WHITE);
            }

            if ((opLitro == 's') || (opLitro == 'S')) {
              valorAbas = totalComb * valorComb;
              litrosAbasTotal = litrosAbasTotal + totalComb;
              totalComb = 0;
              abastecerVeiculo(litrosAbas, valorComb, filaAtendidos, filaEspera,
                               &carrosAbastecidos, &litrosAbasTotal, &totalComb,
                               &lucroComb, &tamFila, valorAbas);
            }
            if ((opLitro == 'n') || (opLitro == 'N')) {
              for (int i = 0; i < tamFila; i++) {
                filaEspera[i] = filaEspera[i + 1];
              }
              tamFila = tamFila - 1;
              printf(GREEN "Veículo liberado da fila de espera sem realizar o "
                           "abastecimento." WHITE);
            }
          }
        } else {
          fimDoCombustivel(&totalComb, &tamFila, &totalComb);
        }
      } else {
        printf(RED "A fila está vazia, nenhum carro foi abastecido." WHITE);
      }

      litrosAbas=0;
      getchar();
      break;

    // EXIBIR VEÍCULOS NA FILA
    case 3:
      // validação se a fila não está em seu tamanho máximo
      if (tammaxFila != tamFila) {

      } else {
        printf(RED "A fila está em sua capacidade máxima!" WHITE);
      }

      printf(MAGENTA "\n\nVeículos na fila: %d\n" WHITE, tamFila);
      imprimirInfos(filaEspera, tamFila, stdout);
      getchar();
      getchar();
      break;

    case 4:
      while (opcao2 != 7) {

        system("clear");

        printf(MAGENTA "\n\nMENU RELATÓRIO" WHITE);
        printf("\nInforme a opção desejada: \n\n");
        printf(MAGENTA "[1]" WHITE " Valor total arrecadado com as vendas;\n");
        printf(MAGENTA "[2]" WHITE " Quantidade de carros atendidos;\n");
        printf(MAGENTA "[3]" WHITE " Quantidade de litros vendida;\n");
        printf(MAGENTA "[4]" WHITE " Combustível restante no tanque;\n");
        printf(MAGENTA "[5]" WHITE " Informações dos carros atendidos e dos "
                       "carros na fila de espera;\n");
        printf(MAGENTA "[6]" WHITE " Gerar arquivo para impressão (com todas "
                       "as informações de 1, 2, 3, 4 e 5)\n");
        printf(MAGENTA "[7]" WHITE " Voltar ao menu principal;\n");
        printf(MAGENTA "[8]" WHITE " Encerrar.\n\n");
        scanf("%d", &opcao2);

        switch (opcao2) {

        case 1:
          dinheiroEmCaixa(lucroComb);

          break;

        case 2:
          carrosAbas(carrosAbastecidos);
          break;

        case 3:
          litrosAbastecidos(litrosAbasTotal);
          break;

        case 4:
          litrosDisponiveis(totalComb);
          break;

        case 5:
          printf(GREEN "\nVeículos atendidos: %d\n" WHITE, carrosAbastecidos);
          imprimirInfos(filaAtendidos, carrosAbastecidos, stdout);

          printf(RED "\nVeículos na fila: %d\n" WHITE, tamFila);
          imprimirInfos(filaEspera, tamFila, stdout);
          break;

        case 6:
          arquivoCase6(totalComb, valorComb, tammaxFila, lucroComb,
                       carrosAbastecidos, litrosAbasTotal, filaAtendidos,
                       carrosAbastecidos, filaEspera, tamFila);
          printf(GREEN "\nArquivo feito!" WHITE);
          break;

        case 7:
          printf(MAGENTA "Voltando ao menu principal..." WHITE);
          break;

        case 8:
          printf(MAGENTA "Programa encerrado." WHITE);
          exit(0);
          break;

        default:
          printf(RED "\nOpção inválida." WHITE);
        }
        if (opcao2 != 7) {
          getchar();
          getchar();
        }
      }

      break;

    case 5:
      printf(MAGENTA "\n\nPrograma encerrado." WHITE);
      exit(0);
      break;

    default:
      printf(RED "\nOpção inválida." WHITE);
    }
  }
  return 0;
}