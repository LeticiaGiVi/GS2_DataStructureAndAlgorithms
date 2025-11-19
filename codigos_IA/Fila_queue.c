#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da fila
typedef struct No {
    char nome[50];
    int senha;
    struct No* proximo;
} No;

// Definição da estrutura da fila
typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
} Fila;

// Inicializa uma fila vazia
void inicializarFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

// Verifica se a fila está vazia
int isEmpty(Fila* fila) {
    return fila->inicio == NULL;
}

// Insere um elemento no final da fila (enqueue)
void enqueue(Fila* fila, const char* nome, int senha) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    strcpy(novo->nome, nome);
    novo->senha = senha;
    novo->proximo = NULL;
    
    if (isEmpty(fila)) {
        // Fila estava vazia
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        // Adiciona no final
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
    
    fila->tamanho++;
}

// Remove e retorna o elemento do início da fila (dequeue)
No dequeue(Fila* fila) {
    No resultado;
    resultado.senha = -1;
    strcpy(resultado.nome, "");
    
    if (isEmpty(fila)) {
        printf("Erro: Fila vazia!\n");
        return resultado;
    }
    
    No* temp = fila->inicio;
    strcpy(resultado.nome, temp->nome);
    resultado.senha = temp->senha;
    
    fila->inicio = temp->proximo;
    
    // Se a fila ficou vazia, atualiza o fim
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(temp);
    fila->tamanho--;
    
    return resultado;
}

// Retorna o elemento do início sem remover (front)
No front(Fila* fila) {
    No resultado;
    resultado.senha = -1;
    strcpy(resultado.nome, "");
    
    if (isEmpty(fila)) {
        return resultado;
    }
    
    strcpy(resultado.nome, fila->inicio->nome);
    resultado.senha = fila->inicio->senha;
    
    return resultado;
}

// Retorna o tamanho da fila
int tamanhoFila(Fila* fila) {
    return fila->tamanho;
}

// Imprime todos os elementos da fila
void imprimirFila(Fila* fila) {
    if (isEmpty(fila)) {
        printf("   [Fila vazia]\n");
        return;
    }
    
    No* atual = fila->inicio;
    printf("   Fila (início → fim): ");
    while (atual != NULL) {
        printf("[%d-%s] ", atual->senha, atual->nome);
        atual = atual->proximo;
    }
    printf("\n");
}

// Libera toda a memória alocada pela fila
void liberarFila(Fila* fila) {
    while (!isEmpty(fila)) {
        dequeue(fila);
    }
}

// Função para simular a chegada de um cliente
void chegadaCliente(Fila* fila, const char* nome, int senha) {
    printf("\n[CHEGADA] Cliente %s (Senha %d) entrou na fila\n", nome, senha);
    enqueue(fila, nome, senha);
    printf("   Tamanho da fila: %d cliente(s)\n", tamanhoFila(fila));
    imprimirFila(fila);
}

// Função para simular o atendimento de um cliente
void atenderCliente(Fila* fila) {
    if (isEmpty(fila)) {
        printf("\n[ATENDIMENTO] Nenhum cliente na fila para atender\n");
        return;
    }
    
    No cliente = dequeue(fila);
    printf("\n[ATENDIMENTO] Atendendo cliente %s (Senha %d)\n", cliente.nome, cliente.senha);
    printf("   Tamanho da fila: %d cliente(s)\n", tamanhoFila(fila));
    imprimirFila(fila);
}

// Função para visualizar o próximo cliente sem atender
void proximoCliente(Fila* fila) {
    if (isEmpty(fila)) {
        printf("\n[PRÓXIMO] Nenhum cliente na fila\n");
        return;
    }
    
    No proximo = front(fila);
    printf("\n[PRÓXIMO] Próximo a ser atendido: %s (Senha %d)\n", proximo.nome, proximo.senha);
}

// Simulação de atendimento em um banco
void simularAtendimentoBanco() {
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║        SIMULAÇÃO DE ATENDIMENTO BANCÁRIO - FIFO       ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    Fila fila;
    inicializarFila(&fila);
    
    int senhaNumerica = 1;
    
    // Cenário 1: Chegada de vários clientes
    printf("\n=== MANHÃ: Chegada de clientes ===");
    chegadaCliente(&fila, "João Silva", senhaNumerica++);
    chegadaCliente(&fila, "Maria Santos", senhaNumerica++);
    chegadaCliente(&fila, "Pedro Costa", senhaNumerica++);
    chegadaCliente(&fila, "Ana Oliveira", senhaNumerica++);
    
    proximoCliente(&fila);
    
    // Cenário 2: Início dos atendimentos
    printf("\n\n=== Início dos atendimentos ===");
    atenderCliente(&fila);
    atenderCliente(&fila);
    
    // Cenário 3: Mais clientes chegam
    printf("\n\n=== Mais clientes chegando ===");
    chegadaCliente(&fila, "Carlos Lima", senhaNumerica++);
    chegadaCliente(&fila, "Juliana Rocha", senhaNumerica++);
    
    proximoCliente(&fila);
    
    // Cenário 4: Continua atendendo
    printf("\n\n=== Continuando atendimentos ===");
    atenderCliente(&fila);
    atenderCliente(&fila);
    atenderCliente(&fila);
    
    // Cenário 5: Último cliente
    printf("\n\n=== Último cliente ===");
    proximoCliente(&fila);
    atenderCliente(&fila);
    
    // Cenário 6: Fila vazia
    printf("\n\n=== Fila vazia ===");
    atenderCliente(&fila);
    proximoCliente(&fila);
    
    liberarFila(&fila);
    printf("\n[ENCERRAMENTO] Simulação finalizada!\n");
}

// Função principal
int main() {
    printf("═══════════════════════════════════════════════════════════\n");
    printf("           TESTE DE FILA COM LISTA ENCADEADA              \n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    // Teste básico das operações
    printf("\n\n=== TESTE BÁSICO DAS OPERAÇÕES ===\n");
    
    Fila fila;
    inicializarFila(&fila);
    
    printf("\nFila vazia? %s\n", isEmpty(&fila) ? "Sim" : "Não");
    
    printf("\nInserindo elementos na fila:\n");
    enqueue(&fila, "Cliente A", 100);
    enqueue(&fila, "Cliente B", 101);
    enqueue(&fila, "Cliente C", 102);
    imprimirFila(&fila);
    
    printf("\nTamanho da fila: %d\n", tamanhoFila(&fila));
    
    No primeiro = front(&fila);
    printf("\nPrimeiro da fila: %s (Senha %d)\n", primeiro.nome, primeiro.senha);
    
    printf("\nFila vazia? %s\n", isEmpty(&fila) ? "Sim" : "Não");
    
    printf("\nRemovendo elementos:\n");
    No removido = dequeue(&fila);
    printf("Removido: %s (Senha %d)\n", removido.nome, removido.senha);
    imprimirFila(&fila);
    
    removido = dequeue(&fila);
    printf("\nRemovido: %s (Senha %d)\n", removido.nome, removido.senha);
    imprimirFila(&fila);
    
    removido = dequeue(&fila);
    printf("\nRemovido: %s (Senha %d)\n", removido.nome, removido.senha);
    imprimirFila(&fila);
    
    printf("\nFila vazia? %s\n", isEmpty(&fila) ? "Sim" : "Não");
    
    liberarFila(&fila);
    
    // Simulação de atendimento bancário
    simularAtendimentoBanco();
    
    return 0;
}