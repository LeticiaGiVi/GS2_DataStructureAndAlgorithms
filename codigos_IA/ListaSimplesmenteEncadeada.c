#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// Definição da estrutura da lista
typedef struct {
    No* inicio;
} Lista;

// Inicializa uma lista vazia
void inicializarLista(Lista* lista) {
    lista->inicio = NULL;
}

// Insere um valor em ordem crescente
void inserirOrdenado(Lista* lista, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    novo->valor = valor;
    novo->proximo = NULL;
    
    // Lista vazia ou inserir no início
    if (lista->inicio == NULL || lista->inicio->valor >= valor) {
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        return;
    }
    
    // Buscar posição correta
    No* atual = lista->inicio;
    while (atual->proximo != NULL && atual->proximo->valor < valor) {
        atual = atual->proximo;
    }
    
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

// Remove um elemento dado um valor
int remover(Lista* lista, int valor) {
    if (lista->inicio == NULL) {
        return 0; // Lista vazia
    }
    
    No* atual = lista->inicio;
    
    // Remover do início
    if (atual->valor == valor) {
        lista->inicio = atual->proximo;
        free(atual);
        return 1;
    }
    
    // Buscar o nó anterior ao que será removido
    while (atual->proximo != NULL && atual->proximo->valor != valor) {
        atual = atual->proximo;
    }
    
    // Valor não encontrado
    if (atual->proximo == NULL) {
        return 0;
    }
    
    // Remover o nó
    No* temp = atual->proximo;
    atual->proximo = temp->proximo;
    free(temp);
    return 1;
}

// Busca um valor e retorna o ponteiro para o nó (ou NULL)
No* buscar(Lista* lista, int valor) {
    No* atual = lista->inicio;
    
    while (atual != NULL) {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL; // Valor não encontrado
}

// Imprime a lista
void imprimirLista(Lista* lista) {
    No* atual = lista->inicio;
    
    if (atual == NULL) {
        printf("Lista vazia\n");
        return;
    }
    
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// Libera toda a memória alocada pela lista
void liberarLista(Lista* lista) {
    No* atual = lista->inicio;
    No* temp;
    
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    lista->inicio = NULL;
}

// Função principal para demonstrar o uso
int main() {
    Lista lista;
    inicializarLista(&lista);
    
    printf("=== Testando Lista Encadeada ===\n\n");
    
    // Inserindo valores
    printf("Inserindo valores: 5, 2, 8, 1, 9, 3\n");
    inserirOrdenado(&lista, 5);
    inserirOrdenado(&lista, 2);
    inserirOrdenado(&lista, 8);
    inserirOrdenado(&lista, 1);
    inserirOrdenado(&lista, 9);
    inserirOrdenado(&lista, 3);
    imprimirLista(&lista);
    
    // Buscando valores
    printf("\nBuscando valor 8: ");
    No* encontrado = buscar(&lista, 8);
    if (encontrado != NULL) {
        printf("Encontrado! Valor = %d\n", encontrado->valor);
    } else {
        printf("Não encontrado\n");
    }
    
    printf("Buscando valor 10: ");
    encontrado = buscar(&lista, 10);
    if (encontrado != NULL) {
        printf("Encontrado! Valor = %d\n", encontrado->valor);
    } else {
        printf("Não encontrado\n");
    }
    
    // Removendo valores
    printf("\nRemovendo valor 5: ");
    if (remover(&lista, 5)) {
        printf("Removido com sucesso\n");
    } else {
        printf("Valor não encontrado\n");
    }
    imprimirLista(&lista);
    
    printf("\nRemovendo valor 1: ");
    if (remover(&lista, 1)) {
        printf("Removido com sucesso\n");
    } else {
        printf("Valor não encontrado\n");
    }
    imprimirLista(&lista);
    
    printf("\nRemovendo valor 15: ");
    if (remover(&lista, 15)) {
        printf("Removido com sucesso\n");
    } else {
        printf("Valor não encontrado\n");
    }
    imprimirLista(&lista);
    
    // Liberando memória
    liberarLista(&lista);
    printf("\nMemória liberada!\n");
    
    return 0;
}