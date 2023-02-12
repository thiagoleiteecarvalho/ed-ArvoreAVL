/*
 * arvore.c
 * Classe de implemantação da ED Árvore AVL.
 * Author: Thiago Leite
 */

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

No *raiz = NULL;

void setRaiz(No *no) {
	raiz = no;
}

No* getRaiz() {
	return raiz;
}

int maior_altura(int altura_esquerda, int altura_direita) {

	if (altura_esquerda > altura_direita) {
		return altura_esquerda;
	} else {
		return altura_direita;
	}
}

int altura_no(No *no) {

	if (no == NULL) {
		return -1;
	} else {
		return no->altura;
	}
}

int valor_balanceamento(No *no) {

	if (no != NULL) {
		return altura_no(no->filho_esquerdo) - altura_no(no->filho_direito);
	} else {
		return 0;
	}
}

No* balancear(No *no) {

	int balanceamento = valor_balanceamento(no); /*I*/

	if (balanceamento < -1 && valor_balanceamento(no->filho_direito) <= 0) { /*II*/
		no = rotacao_esquerda(no);
	} else if (balanceamento > 1
			&& valor_balanceamento(no->filho_esquerdo) >= 0) { /*III*/
		no = rotacao_direita(no);
	} else if (balanceamento > 1
			&& valor_balanceamento(no->filho_esquerdo) < 0) { /*VI*/
		no = rotacao_dupla_esquerda(no);
	} else if (balanceamento < -1
			&& valor_balanceamento(no->filho_direito) > 0) { /*V*/
		no = rotacao_dupla_direita(no);
	}

	return no;
}

No* rotacao_esquerda(No *no) {

	No *subarvore_D, *subarvore_E_D; /*I*/

	subarvore_D = no->filho_direito; /*II*/

	subarvore_E_D = subarvore_D->filho_esquerdo; /*III*/
	subarvore_D->filho_esquerdo = no; /*IV*/

	no->filho_direito = subarvore_E_D; /*V*/

	no->altura = maior_altura(altura_no(no->filho_esquerdo),
			altura_no(no->filho_direito)) + 1; /*VI*/
	subarvore_D->altura = maior_altura(altura_no(subarvore_D->filho_esquerdo),
			altura_no(subarvore_D->filho_direito)) + 1; /*VII*/

	return subarvore_D;
}

No* rotacao_direita(No *no) {

	No *subarvore_E, *subarvore_D_E; /*I*/

	subarvore_E = no->filho_esquerdo; /*II*/

	subarvore_D_E = subarvore_E->filho_direito; /*III*/
	subarvore_E->filho_direito = no; /*IV*/

	no->filho_esquerdo = subarvore_D_E; /*V*/

	no->altura = maior_altura(altura_no(no->filho_esquerdo),
			altura_no(no->filho_direito)) + 1; /*VI*/
	subarvore_E->altura = maior_altura(altura_no(subarvore_E->filho_esquerdo),
			altura_no(subarvore_E->filho_direito)) + 1; /*VII*/

	return subarvore_E;
}

No* rotacao_dupla_esquerda(No *no) {

	no->filho_esquerdo = rotacao_esquerda(no->filho_esquerdo); /*I*/
	return rotacao_direita(no); /*II*/
}

No* rotacao_dupla_direita(No *no) {

	no->filho_esquerdo = rotacao_direita(no->filho_direito); /*I*/
	return rotacao_esquerda(no); /*II*/
}

int folha(No *no) {

	if (no->filho_esquerdo == NULL && no->filho_direito == NULL) {
		return 1;
	} else {
		return 0;
	}
}

No* criar_no(int elemento) {

	No *no = malloc(sizeof(No));
	no->valor = elemento;
	no->filho_esquerdo = NULL;
	no->filho_direito = NULL;
	no->altura = 0;

	return no;
}

void criar_raiz(int elemento) {

	if (raiz == NULL) {
		raiz = criar_no(elemento);
	} else {
		printf("Raiz já foi criada\n");
	}
}

No* insert(No *no, int elemento) {

	if (no == NULL) {
		return criar_no(elemento);
	} else {

		if (elemento < no->valor) {
			no->filho_esquerdo = insert(no->filho_esquerdo, elemento);
		} else if (elemento > no->valor) {
			no->filho_direito = insert(no->filho_direito, elemento);
		} else {
			printf("INSERT não realizado, pois elemento já pertence a árvore.\n");
		}
	}

	no->altura = maior_altura(altura_no(no->filho_esquerdo),
			altura_no(no->filho_direito)) + 1;

	no = balancear(no);

	return no;
}

No* search(No *no, int elemento) {

	if (no == NULL) {
		return NULL;
	} else if (no->valor == elemento) {
		return no;
	} else if (elemento < no->valor) {
		search(no->filho_esquerdo, elemento);
	} else {
		search(no->filho_direito, elemento);
	}
}

void update(No *raiz, char elemento, char novo_valor) {

	No *no = search(raiz, elemento);

	if (no != NULL) {
		no->valor = novo_valor;
	} else {
		printf("Nó não encontrado. Impossível realizar update.\n");
	}
}

No* delete(No *no, int elemento) {

	if (no == NULL) {
		return NULL;
	} else if (no->valor != elemento) {

		if (elemento < no->valor) {
			no->filho_esquerdo = delete(no->filho_esquerdo, elemento);
		} else {
			no->filho_direito = delete(no->filho_direito, elemento);
		}
	} else {

		if (folha(no)) {

			free(no);
			no = NULL;

			return NULL;
		} else if (no->filho_esquerdo != NULL && no->filho_direito != NULL) {

			No *no_filho = no->filho_direito;

			while (no_filho->filho_direito != NULL) {
				no_filho = no_filho->filho_direito;
			}

			no->valor = no_filho->valor;
			no_filho->valor = elemento;
			no->filho_direito = delete(no->filho_direito, elemento);

			return no;
		} else {

			No *no_filho;

			if (no->filho_esquerdo != NULL) {
				no_filho = no->filho_esquerdo;
			} else {
				no_filho = no->filho_direito;
			}

			free(no);
			no = NULL;

			return no_filho;
		}
	}

	no->altura = maior_altura(altura_no(no->filho_esquerdo),
			altura_no(no->filho_direito)) + 1;

	no = balancear(no);

	return no;
}

void exibir_em_ordem(No *no) {

	if (no != NULL) {

		exibir_em_ordem(no->filho_esquerdo);
		printf("%d ", no->valor);
		exibir_em_ordem(no->filho_direito);
	}
}

void exibir_arvore(No *no, int nivel) {

	int i;

	if (no != NULL) {
		exibir_arvore(no->filho_direito, nivel + 1);
		printf("\n\n");

		for (i = 0; i < nivel; i++) {
			printf("\t");
		}

		printf("%d", no->valor);
		exibir_arvore(no->filho_esquerdo, nivel + 1);

	}
}
