#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define filho_esquerda(x) 2 * x + 1
#define filho_direita(x) 2 * x + 2
#define pai(x) (x - 1) / 2

typedef struct node {
    int valor ;
} node ;

typedef struct min_heap {
    int tamanho ;
    node *elemento ;
} min_heap ;

min_heap inicia_min_heap(int tamanho) {
    min_heap hp;
    hp.tamanho = 0;
    return hp;
}

void trocar_valores(node *n1, node *n2) {
    node aux = *n1 ;
    *n1 = *n2 ;
    *n2 = aux ;
}

void heapify(min_heap *hp,int i) {
    int menor = (filho_esquerda(i) < hp->tamanho && hp->elemento[filho_esquerda(i)].valor < hp->elemento[i].valor) ? filho_esquerda(i) : i ;
    
    if(filho_direita(i) < hp->tamanho && hp->elemento[filho_direita(i)].valor < hp->elemento[menor].valor) {
        menor = filho_direita(i);
    }
    
    if(menor != i) {
        trocar_valores(&(hp->elemento[i]), &(hp->elemento[menor])) ;
        heapify(hp, menor);
    }
}

void contruir_min_heap(min_heap *hp, int *array, int tamanho) {
    int i ;

    for(i = 0; i < tamanho; i++) {
        if(hp->tamanho) {
            hp->elemento = realloc(hp->elemento, (hp->tamanho + 1) * sizeof(node)) ;
        } else {
            hp->elemento = malloc(sizeof(node)) ;
        }

        node no ;
        no.valor = array[i];
        hp->elemento[(hp->tamanho)++] = no;
    }

    for(i=(hp->tamanho-1)/2;i>=0;i--) {
        heapify(hp, i) ;
    }
}

void inserir_no(min_heap *hp, int valor) {
    if(hp->tamanho) {
        hp->elemento = realloc(hp->elemento, (hp->tamanho + 1) * sizeof(node)) ;
    } else {
        hp->elemento = malloc(sizeof(node)) ;
    }

    node no ;
    no.valor = valor ;

    int i = (hp->tamanho)++ ;
    while(i && no.valor < hp->elemento[pai(i)].valor) {
        hp->elemento[i] = hp->elemento[pai(i)] ;
        i = pai(i) ;
    }

    hp->elemento[i] = no ;
}

void excluir_no(min_heap *hp) {
    if(hp->tamanho) {
        printf("Excluir nó %d\n\n", hp->elemento[0].valor) ;

        hp->elemento[0] = hp->elemento[--(hp->tamanho)] ;
        hp->elemento = realloc(hp->elemento, hp->tamanho * sizeof(node)) ;

        heapify(hp, 0) ;
    } else {
        printf("\nMin Heap está vazia!\n") ;
        free(hp->elemento) ;
    }
}

int no_maximo(min_heap *hp, int i) {
    if(filho_esquerda(i) >= hp->tamanho) {
        return hp->elemento[i].valor ;
    }

    int l = no_maximo(hp, filho_esquerda(i)) ;
    int r = no_maximo(hp, filho_direita(i)) ;

    if(l >= r) {
        return l ;
    } else {
        return r ;
    }
}

void limpar_memoria(min_heap *hp) {
    free(hp->elemento) ;
}

void exibir_no_in_order(min_heap *hp, int i) {
    if(filho_esquerda(i) < hp->tamanho) {
        exibir_no(hp, filho_esquerda(i)) ;
    }
    printf("%d ", hp->elemento[i].valor) ;
    if(filho_direita(i) < hp->tamanho) {
        exibir_no(hp, filho_direita(i)) ;
    }
}

void exibir_no_pre_order(min_heap *hp, int i) {
    if(filho_esquerda(i) < hp->tamanho) {
        exibir_no_pre_order(hp, filho_esquerda(i)) ;
    }
    if(filho_direita(i) < hp->tamanho) {
        exibir_no_pre_order(hp, filho_direita(i)) ;
    }
    printf("%d ", hp->elemento[i].valor) ;
}

void exibir_no_pos_order(min_heap *hp, int i) {
    printf("%d ", hp->elemento[i].valor) ;
    if(filho_esquerda(i) < hp->tamanho) {
        exibir_no_pos_order(hp, filho_esquerda(i)) ;
    }
    if(filho_direita(i) < hp->tamanho) {
        exibir_no_pos_order(hp, filho_direita(i)) ;
    }
}

void exibir_no(min_heap *hp) {
    int i ;
    for(i = 0; i < hp->tamanho; i++) {
        printf("%d ", hp->elemento[i].valor) ;
    }
}