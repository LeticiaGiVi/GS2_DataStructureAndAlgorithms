#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct No {
    int valor;
    struct No* proximo;
    struct No* anterior;
} No;

// Definição da estrutura da lista
typedef struct {
    No* inicio;
    No* fim;
} ListaDupla;

// Inicializa uma lista vazia
void inicializarLista(ListaDupla* lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

// Insere um elemento no início da lista
void inserirInicio(ListaDupla* lista, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    novo->valor = valor;
    novo->proximo = lista->inicio;
    novo->anterior = NULL;
    
    if (lista->inicio != NULL) {
        lista->inicio->anterior = novo;
    } else {
        // Lista estava vazia
        lista->fim = novo;
    }
    
    lista->inicio = novo;
}

// Insere um elemento no final da lista
void inserirFinal(ListaDupla* lista, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    novo->valor = valor;
    novo->proximo = NULL;
    novo->anterior = lista->fim;
    
    if (lista->fim != NULL) {
        lista->fim->proximo = novo;
    } else {
        // Lista estava vazia
        lista->inicio = novo;
    }
    
    lista->fim = novo;
}

// Remove o elemento do início da lista
int removerInicio(ListaDupla* lista) {
    if (lista->inicio == NULL) {
        printf("Lista vazia! Não é possível remover.\n");
        return 0;
    }
    
    No* temp = lista->inicio;
    int valor = temp->valor;
    
    lista->inicio = temp->proximo;
    
    if (lista->inicio != NULL) {
        lista->inicio->anterior = NULL;
    } else {
        // Lista ficou vazia
        lista->fim = NULL;
    }
    
    free(temp);
    return valor;
}

// Remove o elemento do final da lista
int removerFinal(ListaDupla* lista) {
    if (lista->fim == NULL) {
        printf("Lista vazia! Não é possível remover.\n");
        return 0;
    }
    
    No* temp = lista->fim;
    int valor = temp->valor;
    
    lista->fim = temp->anterior;
    
    if (lista->fim != NULL) {
        lista->fim->proximo = NULL;
    } else {
        // Lista ficou vazia
        lista->inicio = NULL;
    }
    
    free(temp);
    return valor;
}

// Percorre a lista do início ao fim (head → tail)
void percorrerInicioFim(ListaDupla* lista) {
    No* atual = lista->inicio;
    
    if (atual == NULL) {
        printf("Lista vazia\n");
        return;
    }
    
    printf("Início → Fim: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// Percorre a lista do fim ao início (tail → head)
void percorrerFimInicio(ListaDupla* lista) {
    No* atual = lista->fim;
    
    if (atual == NULL) {
        printf("Lista vazia\n");
        return;
    }
    
    printf("Fim → Início: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->anterior;
    }
    printf("\n");
}

// Libera toda a memória alocada pela lista
void liberarLista(ListaDupla* lista) {
    No* atual = lista->inicio;
    No* temp;
    
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    lista->inicio = NULL;
    lista->fim = NULL;
}

// Retorna o tamanho da lista
int tamanhoLista(ListaDupla* lista) {
    int contador = 0;
    No* atual = lista->inicio;
    
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    
    return contador;
}

// Função principal para demonstrar o uso
int main() {
    ListaDupla lista;
    inicializarLista(&lista);
    
    printf("=== Testando Lista Duplamente Encadeada ===\n\n");
    
    // Inserindo no início
    printf("Inserindo no início: 3, 2, 1\n");
    inserirInicio(&lista, 3);
    inserirInicio(&lista, 2);
    inserirInicio(&lista, 1);
    percorrerInicioFim(&lista);
    percorrerFimInicio(&lista);
    
    // Inserindo no final
    printf("\nInserindo no final: 4, 5, 6\n");
    inserirFinal(&lista, 4);
    inserirFinal(&lista, 5);
    inserirFinal(&lista, 6);
    percorrerInicioFim(&lista);
    percorrerFimInicio(&lista);
    
    printf("\nTamanho da lista: %d\n", tamanhoLista(&lista));
    
    // Removendo do início
    printf("\nRemovendo do início: ");
    int removido = removerInicio(&lista);
    printf("Valor removido = %d\n", removido);
    percorrerInicioFim(&lista);
    
    // Removendo do final
    printf("\nRemovendo do final: ");
    removido = removerFinal(&lista);
    printf("Valor removido = %d\n", removido);
    percorrerInicioFim(&lista);
    
    // Testando percurso em ambos os sentidos
    printf("\nPercorrendo nos dois sentidos:\n");
    percorrerInicioFim(&lista);
    percorrerFimInicio(&lista);
    
    // Removendo todos os elementos
    printf("\nRemovendo todos os elementos...\n");
    while (lista.inicio != NULL) {
        int val = removerInicio(&lista);
        printf("Removido: %d\n", val);
    }
    
    printf("\nApós remover tudo:\n");
    percorrerInicioFim(&lista);
    
    // Testando inserção após esvaziar
    printf("\nInserindo após esvaziar: 10, 20\n");
    inserirFinal(&lista, 10);
    inserirFinal(&lista, 20);
    percorrerInicioFim(&lista);
    percorrerFimInicio(&lista);
    
    // Liberando memória
    liberarLista(&lista);
    printf("\nMemória liberada!\n");
    
    return 0;
}