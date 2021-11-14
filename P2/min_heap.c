#include<stdio.h>
#include<stdlib.h>

int heap[100];
int count = 0;

int define_filho_esquerda(int indice){
    return indice * 2;
}

int define_filho_direita(int indice){
    return (indice*2) + 1;
}

int define_pai(int indice){
    return indice/2;
}

void subir_minimo(int indice){
    int aux;

    if(indice<=1){
        return;
    }

    int pai = define_pai(indice);

    if(heap[indice]<heap[pai]){
        aux = heap[indice];
        heap[indice] = heap[pai];
        heap[pai] = aux;
        subir_minimo(pai);
    }
}

void desce_minimo(int indice){
    if((indice*2)>count){
        return;
    }

    int filho_esquerda = define_filho_esquerda(indice);
    int filho_direita = define_filho_direita(indice);

    int menor = indice;

    if(filho_esquerda<=count && heap[filho_esquerda]<heap[menor]){
        menor = filho_esquerda;
    }

    if(filho_direita<=count && heap[filho_direita]<heap[menor]){
        menor = filho_direita;
    }

    if(menor==indice){
        return;
    }

    int aux;

    aux = heap[indice];
    heap[indice] = heap[menor];
    heap[menor] = aux;
    desce_minimo(menor);
}

int push(int x){
    count++;
    heap[count] = x;
    subir_minimo(count);
}

void pop(){
    if(count==0){
        return;
    }

    printf("\n%d",heap[1]);
    heap[1] = heap[count];
    count--;
    desce_minimo(1);
}

int main(){
    push(1);
    push(10);
    push(2);
    push(8);
    push(3);
    push(7);
    push(4);
    push(6);
    push(5);
    push(9);

    for(int i=0;i<10;i++){
        pop();
    }

    printf("\n");
    return 0;
}