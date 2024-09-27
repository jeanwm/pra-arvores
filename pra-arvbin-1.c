#include <stdlib.h>
#include <stdio.h>

typedef struct no {
	struct no* pai; 
	struct no* esquerda;
	struct no* direita; 
	float valor; 
} No;

typedef struct arvore {
	struct no* raiz;
} Arvore;

Arvore* criar() {
	Arvore *arvore;
	arvore = malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	
	return arvore;
}

int vazia(Arvore* arvore) {
	return (arvore->raiz == NULL);
}

No* adicionar(Arvore* arvore, No* pai, float valor) {
	No *no  = malloc(sizeof(No));
	no->pai = pai;
	no->esquerda = NULL;
	no->direita  = NULL;
	no->valor 	 = valor;
	
	if (pai == NULL) {
		arvore->raiz = no;
	}
	
	return no;
}

void remover(Arvore* arvore, No* no) {
	if (no->esquerda != NULL)
		remover(arvore, no->esquerda);
	
	if (no->direita != NULL)
	 	remover(arvore, no->direita);
	
	if (no->pai == NULL) {
	 	arvore->raiz = NULL;
	 	
	} else {
	 	if (no->pai->esquerda == no)
	 		no->pai->esquerda = NULL;
	 		
	 	else
	 		no->pai->direita = NULL;
	}
	
	free(no);
}

void percorrer(No* no) {
	if (no != NULL) {
	 	printf("%f", no->valor);
	 	
	 	percorrer(no->esquerda);
	 	percorrer(no->direita);
	}
}

int main() {
	Arvore* avr = criar();
	No* no;
	int valores[7] = { 1, 2, 3, 4, 5, 6, 7 };
	int i = 0;
	
	vazia(avr);
	
	for (i = 0; i <= 7; i++){
		adicionar(avr, no, valores[i]);
	}
	
	percorrer(no);
	
	return 0;
}
