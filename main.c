/*
 * main.c
 * Classe principal de execução da Árvore AVL.
 * Author: Thiago Leite
 */

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(void) {

	int opcao;
	int valor;

	do {

		printf("\n");
		printf("ÁRVORE AVL");
		printf("\nEscolha a opcao\n");
		printf("0. Sair\n");
		printf("1. ROOT\n");
		printf("2. INSERT\n");
		printf("3. SEARCH\n");
		printf("4. DELETE\n");
		printf("5. Exibir Em-Ordem\n");
		printf("Digite uma opção:");
		scanf("%d", &opcao);

		switch (opcao) {
		case 0:
			exit(1);
			break;

		case 1:
			printf("Digite um valor para a raiz da árvore:");
			scanf(" %d", &valor);
			criar_raiz(valor);
			break;

		case 2:
			printf("Digite um valor a ser inserido:");
			scanf(" %d", &valor);
			setRaiz(insert(getRaiz(), valor));
			break;

		case 3:
			printf("Digite um elemento a ser pesquisado:");
			scanf(" %d", &valor);

			No *no_search = NULL;
			no_search = search(getRaiz(), valor);
			if (no_search != NULL) {
				printf("Elemento %d pertence a árvore.", no_search->valor);
			} else {
				printf("Elemento não %d pertence a árvore.", valor);
			}
			break;

		case 4:
			printf("Digite um elemento a ser apagado:");
			scanf(" %d", &valor);

			No *no_delete = NULL;
			no_delete = delete(getRaiz(), valor);
			if (no_delete != NULL) {
				printf("Elemento %d excluido da árvore.", valor);
			} else {
				printf("Elemento não %d pertence a árvore.", valor);
			}
			break;
		case 5:
			exibir_arvore(getRaiz(), 1);
			printf("\n\n\n");
			exibir_em_ordem(getRaiz());
			break;

		default:
			printf("Comando invalido\n\n");
			break;
		}

	} while (opcao);

	free(getRaiz());
	return 0;
}
