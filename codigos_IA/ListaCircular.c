#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// Definição da estrutura da lista circular
typedef struct {
    No* cabeca;
} ListaCircular;

// Inicializa uma lista vazia
void inicializarLista(ListaCircular* lista) {
    lista->cabeca = NULL;
}

// Insere um elemento no final da lista circular
void inserir(ListaCircular* lista, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    novo->valor = valor;
    
    if (lista->cabeca == NULL) {
        // Lista vazia - nó aponta para si mesmo
        novo->proximo = novo;
        lista->cabeca = novo;
    } else {
        // Encontrar o último nó
        No* ultimo = lista->cabeca;
        while (ultimo->proximo != lista->cabeca) {
            ultimo = ultimo->proximo;
        }
        
        // Inserir no final e manter circularidade
        novo->proximo = lista->cabeca;
        ultimo->proximo = novo;
    }
}

// Avança "k" posições a partir de um nó
No* avancarKPosicoes(No* noInicial, int k) {
    if (noInicial == NULL) {
        return NULL;
    }
    
    No* atual = noInicial;
    
    // Avançar k posições
    for (int i = 0; i < k; i++) {
        atual = atual->proximo;
    }
    
    return atual;
}

// Remove um nó específico da lista circular mantendo a circularidade
int removerNo(ListaCircular* lista, int valor) {
    if (lista->cabeca == NULL) {
        return 0; // Lista vazia
    }
    
    No* atual = lista->cabeca;
    No* anterior = NULL;
    
    // Caso especial: único nó na lista
    if (atual->proximo == lista->cabeca && atual->valor == valor) {
        free(atual);
        lista->cabeca = NULL;
        return 1;
    }
    
    // Encontrar o último nó para começar a busca
    No* ultimo = lista->cabeca;
    while (ultimo->proximo != lista->cabeca) {
        ultimo = ultimo->proximo;
    }
    
    anterior = ultimo;
    
    // Percorrer a lista circular procurando o valor
    do {
        if (atual->valor == valor) {
            // Remover o nó
            anterior->proximo = atual->proximo;
            
            // Se estamos removendo a cabeça, atualizar a referência
            if (atual == lista->cabeca) {
                lista->cabeca = atual->proximo;
            }
            
            free(atual);
            return 1;
        }
        
        anterior = atual;
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    
    return 0; // Valor não encontrado
}

// Busca um valor e retorna o ponteiro para o nó
No* buscar(ListaCircular* lista, int valor) {
    if (lista->cabeca == NULL) {
        return NULL;
    }
    
    No* atual = lista->cabeca;
    
    do {
        if (atual->valor == valor) {
            return atual;
        }
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    
    return NULL; // Valor não encontrado
}

// Imprime a lista circular (limitando a uma volta completa)
void imprimirLista(ListaCircular* lista) {
    if (lista->cabeca == NULL) {
        printf("Lista vazia\n");
        return;
    }
    
    No* atual = lista->cabeca;
    
    printf("Lista circular: ");
    do {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    printf("(volta para %d)\n", lista->cabeca->valor);
}

// Imprime k elementos a partir de um nó
void imprimirKElementos(No* noInicial, int k) {
    if (noInicial == NULL) {
        printf("Nó inicial é NULL\n");
        return;
    }
    
    No* atual = noInicial;
    
    printf("Imprimindo %d elementos a partir de %d: ", k, noInicial->valor);
    for (int i = 0; i < k; i++) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// Retorna o tamanho da lista
int tamanhoLista(ListaCircular* lista) {
    if (lista->cabeca == NULL) {
        return 0;
    }
    
    int contador = 1;
    No* atual = lista->cabeca->proximo;
    
    while (atual != lista->cabeca) {
        contador++;
        atual = atual->proximo;
    }
    
    return contador;
}

// Libera toda a memória alocada pela lista
void liberarLista(ListaCircular* lista) {
    if (lista->cabeca == NULL) {
        return;
    }
    
    No* atual = lista->cabeca;
    No* proximo;
    
    // Quebrar a circularidade
    No* ultimo = lista->cabeca;
    while (ultimo->proximo != lista->cabeca) {
        ultimo = ultimo->proximo;
    }
    ultimo->proximo = NULL;
    
    // Liberar todos os nós
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    lista->cabeca = NULL;
}

// Função principal para demonstrar o uso
int main() {
    ListaCircular lista;
    inicializarLista(&lista);
    
    printf("=== Testando Lista Circular Simplesmente Encadeada ===\n\n");
    
    // Inserindo elementos
    printf("Inserindo valores: 10, 20, 30, 40, 50\n");
    inserir(&lista, 10);
    inserir(&lista, 20);
    inserir(&lista, 30);
    inserir(&lista, 40);
    inserir(&lista, 50);
    imprimirLista(&lista);
    printf("Tamanho da lista: %d\n", tamanhoLista(&lista));
    
    // Testando a função de avançar k posições
    printf("\n=== Testando avançar k posições ===\n");
    No* noInicial = lista.cabeca;
    printf("Nó inicial: %d\n", noInicial->valor);
    
    No* noApos3 = avancarKPosicoes(noInicial, 3);
    printf("Após avançar 3 posições: %d\n", noApos3->valor);
    
    No* noApos7 = avancarKPosicoes(noInicial, 7);
    printf("Após avançar 7 posições (dá a volta): %d\n", noApos7->valor);
    
    // Imprimindo k elementos a partir de um nó
    printf("\n");
    imprimirKElementos(noInicial, 8);
    
    // Testando busca
    printf("\n=== Testando busca ===\n");
    No* encontrado = buscar(&lista, 30);
    if (encontrado != NULL) {
        printf("Valor 30 encontrado no nó com endereço %p\n", (void*)encontrado);
        
        // Avançar 2 posições a partir do nó encontrado
        No* avancar = avancarKPosicoes(encontrado, 2);
        printf("Avançando 2 posições a partir de 30: %d\n", avancar->valor);
    }
    
    // Testando remoção
    printf("\n=== Testando remoção ===\n");
    printf("Removendo valor 30: ");
    if (removerNo(&lista, 30)) {
        printf("Removido com sucesso\n");
    } else {
        printf("Valor não encontrado\n");
    }
    imprimirLista(&lista);
    
    printf("\nRemovendo valor 10 (cabeça): ");
    if (removerNo(&lista, 10)) {
        printf("Removido com sucesso\n");
    } else {
        printf("Valor não encontrado\n");
    }
    imprimirLista(&lista);
    
    printf("\nRemovendo valor 50 (final): ");
    if (removerNo(&lista, 50)) {
        printf("Removido com sucesso\n");
    } else {
        printf("Valor não encontrado\n");
    }
    imprimirLista(&lista);
    
    printf("\nRemovendo valor 100 (não existe): ");
    if (removerNo(&lista, 100)) {
        printf("Removido com sucesso\n");
    } else {
        printf("Valor não encontrado\n");
    }
    imprimirLista(&lista);
    
    // Testando circularidade após remoções
    printf("\n=== Verificando circularidade ===\n");
    printf("Tamanho atual: %d\n", tamanhoLista(&lista));
    imprimirKElementos(lista.cabeca, 6);
    
    // Liberando memória
    liberarLista(&lista);
    printf("\nMemória liberada!\n");
    
    return 0;
}