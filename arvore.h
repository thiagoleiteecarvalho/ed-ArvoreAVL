/*
 * arvore.h
 * Header de definição da ED Árvore AVL.
 * Author: Thiago Leite
 */

#pragma once

typedef struct no {
	int valor;
	struct no *filho_esquerdo;
	struct no *filho_direito;
	int altura;
} No;

void setRaiz(No *no);
No* getRaiz();
No* criar_no(int elemento);
void criar_raiz(int elemento);
int maior_altura(int altura_esquerda, int altura_direita);
int altura_no(No *no);
int valor_balanceamento(No *no);
No* balancear(No *no);
No* rotacao_esquerda(No *no);
No* rotacao_direita(No *no);
No* rotacao_dupla_esquerda(No *no);
No* rotacao_dupla_direita(No *no);
No* insert(No *no, int elemento);
No* search(No *no, int elemento);
void update(No *raiz, char elemento, char novo_valor);
No* delete(No *no, int elemento);
void exibir_em_ordem(No *no);
void exibir_arvore(No *no, int nivel);
int folha(No *no);
