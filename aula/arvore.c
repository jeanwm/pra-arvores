#include <stdlib.h>
#include <stdio.h>

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
 	struct no* pai;
 	struct no* esquerda;
 	struct no* direita;
 	Cor cor; 
 	int valor;
} No;

typedef struct arvore {
 	struct no* raiz;
 	struct no* nulo;
} Arvore;

No* criarNo(Arvore* arvore, No* pai, int valor) {
 	No* no = malloc(sizeof(No));

 	no->pai = pai;
 	no->valor = valor;
 	no->direita = arvore->nulo;
 	no->esquerda = arvore->nulo;
 	no->cor = Vermelho;
}

Arvore* criarArvore() {
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

int altura(No* no){
	int esquerda = 0, direita = 0;
	
	if (no->esquerda != NULL) {
		esquerda = altura(no->esquerda) + 1;
	}
	 
	if (no->direita != NULL) {
	 	direita = altura(no->direita) + 1;
	}
	
	return esquerda > direita ? esquerda : direita;
}

int fb(No* no) {
	int esquerda = 0, direita = 0;
	
	if (no->esquerda != NULL) {
		esquerda = altura(no->esquerda) + 1;
	}
	
	if (no->direita != NULL) {
		direita = altura(no->direita) + 1;
	}
	
	return esquerda - direita;
}

No* rse(No* no) {
	No* pai = no->pai;
	No* direita = no->direita;

 	no->direita = direita->esquerda;
 	no->pai = direita;
 	direita->esquerda = no;
 	direita->pai = pai;

 	return direita;
}

No* rsd(No* no) {
 	No* pai = no->pai;
 	No* esquerda = no->esquerda;

 	no->esquerda = esquerda->direita;
 	no->pai = esquerda;

 	esquerda->direita = no;
 	esquerda->pai = pai;

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

void balancear(Arvore* arvore, No* no) {
 	while (no->pai->cor == Vermelho) { 
 		if (no->pai == no->pai->pai->esquerda) {
 			No *tio = no->pai->pai->direita;

 			if (tio->cor == Vermelho) {
 				tio->cor = Preto;
 				no->pai->cor = Preto;
 				no->pai->pai->cor = Vermelho;
 				no = no->pai->pai;
 			} else {
 				if (no == no->pai->direita) {
 					no = no->pai;
 					rotacionarEsquerda(arvore, no);
 				} else {
 					no->pai->cor = Preto;
 					no->pai->pai->cor = Vermelho;
 					rotacionarDireita(arvore, no->pai->pai);
 				}
 			}
 		} else {
 			No *tio = no->pai->pai->esquerda;

 			if (tio->cor == Vermelho) {
 				tio->cor = Preto;
 				no->pai->cor = Preto;
 				no->pai->pai->cor = Vermelho;
 				no = no->pai->pai;
 			} else {
 				if (no == no->pai->esquerda) {
 					no = no->pai;
 					rotacionarEsquerda(arvore, no);
 				} else {
 					no->pai->cor = Preto;
 					no->pai->pai->cor = Vermelho;
 					rotacionarDireita(arvore, no->pai->pai);
 				}
 			}
 		}
 	}
 	
	arvore->raiz->cor = Preto; 
}

int main() {
	Arvore* avr = criarArvore();
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


// No *no = criar(....);
//
// while(no != NULL) {
//	 int fator = fb(no);
//	 no = no->pai;
// }
