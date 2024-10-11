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

Arvore* criarArvore() {
	Arvore *arvore = malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	return arvore;
}

int vazia(Arvore* arvore) {
	return (arvore->raiz == NULL);
}

No* criarNo(No* pai, float valor) {
	No *no = malloc(sizeof(No));
	no->pai = pai;
	no->esquerda = NULL;
	no->direita = NULL;
	no->valor = valor;
	return no;
}

int altura(No* no) {
	if (no == NULL) return -1;
	int esquerda = altura(no->esquerda);
	int direita = altura(no->direita);
	return (esquerda > direita ? esquerda : direita) + 1;
}

int fb(No* no) {
	if (no == NULL) return 0;
	return altura(no->esquerda) - altura(no->direita);
}

No* rse(No* no) {
	No* direita = no->direita;
	no->direita = direita->esquerda;
	if (direita->esquerda != NULL) {
		direita->esquerda->pai = no;
	}
	direita->pai = no->pai;
	if (no->pai == NULL) {
		direita->pai = NULL;  // Nova raiz
	} else if (no == no->pai->esquerda) {
		no->pai->esquerda = direita;
	} else {
		no->pai->direita = direita;
	}
	direita->esquerda = no;
	no->pai = direita;
	return direita;
}

No* rsd(No* no) {
	No* esquerda = no->esquerda;
	no->esquerda = esquerda->direita;
	if (esquerda->direita != NULL) {
		esquerda->direita->pai = no;
	}
	esquerda->pai = no->pai;
	if (no->pai == NULL) {
		esquerda->pai = NULL;  // Nova raiz
	} else if (no == no->pai->direita) {
		no->pai->direita = esquerda;
	} else {
		no->pai->esquerda = esquerda;
	}
	esquerda->direita = no;
	no->pai = esquerda;
	return esquerda;
}

No* rde(No* no) {
	no->direita = rsd(no->direita);
	return rse(no);
}

No* rdd(No* no) {
	no->esquerda = rse(no->esquerda);
	return rsd(no);
}

No* adicionar(Arvore* arvore, No* no, float valor) {
	if (no == NULL) {
		return criarNo(NULL, valor);
	}
	if (valor < no->valor) {
		no->esquerda = adicionar(arvore, no->esquerda, valor);
		no->esquerda->pai = no;
	} else {
		no->direita = adicionar(arvore, no->direita, valor);
		no->direita->pai = no;
	}

	// Rebalancear a árvore
	int fator = fb(no);
	if (fator > 1) {
		if (fb(no->esquerda) < 0) {
			no->esquerda = rse(no->esquerda);
		}
		return rsd(no);
	}
	if (fator < -1) {
		if (fb(no->direita) > 0) {
			no->direita = rde(no->direita);
		}
		return rse(no);
	}
	return no;
}

void percorrer(No* no) {
	if (no != NULL) {
		percorrer(no->esquerda);
		printf("%f ", no->valor);
		percorrer(no->direita);
	}
}

void remover(Arvore* arvore, No* no) {
	if (no != NULL) {
		remover(arvore, no->esquerda);
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
}

int main() {
	Arvore* avr = criarArvore();
	int valores[7] = { 1, 2, 3, 4, 5, 6, 7 };
	int i = 0;
	
	for (i = 0; i < 7; i++) {
		avr->raiz = adicionar(avr, avr->raiz, valores[i]);
	}
	
	printf("Valores na árvore (em ordem): ");
	percorrer(avr->raiz);
	printf("\n");

	// Limpeza da árvore
	remover(avr, avr->raiz);
	free(avr);
	return 0;
}

