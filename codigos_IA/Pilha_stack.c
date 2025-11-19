#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da pilha
typedef struct No {
    char valor;
    struct No* proximo;
} No;

// Definição da estrutura da pilha
typedef struct {
    No* topo;
} Pilha;

// Inicializa uma pilha vazia
void inicializarPilha(Pilha* pilha) {
    pilha->topo = NULL;
}

// Verifica se a pilha está vazia
int isEmpty(Pilha* pilha) {
    return pilha->topo == NULL;
}

// Insere um elemento no topo da pilha (push)
void push(Pilha* pilha, char valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    novo->valor = valor;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

// Remove e retorna o elemento do topo da pilha (pop)
char pop(Pilha* pilha) {
    if (isEmpty(pilha)) {
        printf("Erro: Pilha vazia!\n");
        return '\0';
    }
    
    No* temp = pilha->topo;
    char valor = temp->valor;
    
    pilha->topo = temp->proximo;
    free(temp);
    
    return valor;
}

// Retorna o elemento do topo sem remover (top)
char top(Pilha* pilha) {
    if (isEmpty(pilha)) {
        return '\0';
    }
    
    return pilha->topo->valor;
}

// Imprime todos os elementos da pilha
void imprimirPilha(Pilha* pilha) {
    if (isEmpty(pilha)) {
        printf("Pilha vazia\n");
        return;
    }
    
    No* atual = pilha->topo;
    printf("Pilha (topo → base): ");
    while (atual != NULL) {
        printf("%c ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// Libera toda a memória alocada pela pilha
void liberarPilha(Pilha* pilha) {
    while (!isEmpty(pilha)) {
        pop(pilha);
    }
}

// Verifica se um caractere é um parêntese/colchete/chave de abertura
int ehAbertura(char c) {
    return (c == '(' || c == '[' || c == '{');
}

// Verifica se um caractere é um parêntese/colchete/chave de fechamento
int ehFechamento(char c) {
    return (c == ')' || c == ']' || c == '}');
}

// Verifica se dois caracteres formam um par válido
int ehPar(char abertura, char fechamento) {
    return ((abertura == '(' && fechamento == ')') ||
            (abertura == '[' && fechamento == ']') ||
            (abertura == '{' && fechamento == '}'));
}

// Verifica se uma expressão está balanceada
int verificarBalanceamento(const char* expressao) {
    Pilha pilha;
    inicializarPilha(&pilha);
    
    int tamanho = strlen(expressao);
    int i;
    
    for (i = 0; i < tamanho; i++) {
        char c = expressao[i];
        
        // Se é um símbolo de abertura, empilha
        if (ehAbertura(c)) {
            push(&pilha, c);
        }
        // Se é um símbolo de fechamento, verifica o par
        else if (ehFechamento(c)) {
            // Se a pilha está vazia, não há par correspondente
            if (isEmpty(&pilha)) {
                liberarPilha(&pilha);
                return 0; // Não balanceada
            }
            
            char topoAtual = pop(&pilha);
            
            // Verifica se forma um par válido
            if (!ehPar(topoAtual, c)) {
                liberarPilha(&pilha);
                return 0; // Não balanceada
            }
        }
        // Outros caracteres são ignorados
    }
    
    // No final, a pilha deve estar vazia
    int resultado = isEmpty(&pilha);
    liberarPilha(&pilha);
    
    return resultado;
}

// Função para testar uma expressão
void testarExpressao(const char* expressao) {
    printf("\nExpressão: \"%s\"\n", expressao);
    
    if (verificarBalanceamento(expressao)) {
        printf("✓ Balanceada\n");
    } else {
        printf("✗ NÃO balanceada\n");
    }
}

// Função principal
int main() {
    printf("=== TESTE DE PILHA ===\n\n");
    
    // Testando operações básicas da pilha
    Pilha pilha;
    inicializarPilha(&pilha);
    
    printf("Testando operações básicas:\n");
    printf("Pilha vazia? %s\n", isEmpty(&pilha) ? "Sim" : "Não");
    
    printf("\nInserindo elementos: A, B, C\n");
    push(&pilha, 'A');
    push(&pilha, 'B');
    push(&pilha, 'C');
    imprimirPilha(&pilha);
    
    printf("\nTopo da pilha: %c\n", top(&pilha));
    printf("Pilha vazia? %s\n", isEmpty(&pilha) ? "Sim" : "Não");
    
    printf("\nRemovendo elemento: %c\n", pop(&pilha));
    imprimirPilha(&pilha);
    
    printf("\nRemovendo elemento: %c\n", pop(&pilha));
    imprimirPilha(&pilha);
    
    printf("\nRemovendo elemento: %c\n", pop(&pilha));
    printf("Pilha vazia? %s\n", isEmpty(&pilha) ? "Sim" : "Não");
    
    liberarPilha(&pilha);
    
    // Testando verificação de balanceamento
    printf("\n\n=== TESTE DE BALANCEAMENTO DE EXPRESSÕES ===\n");
    
    // Casos balanceados
    testarExpressao("()");
    testarExpressao("[]");
    testarExpressao("{}");
    testarExpressao("()[]{}");
    testarExpressao("{[()]}");
    testarExpressao("((a + b) * [c - d])");
    testarExpressao("{[(x + y) * z]}");
    testarExpressao("if (x > 0) { print[array[i]]; }");
    
    // Casos não balanceados
    testarExpressao("(");
    testarExpressao(")");
    testarExpressao("(]");
    testarExpressao("([)]");
    testarExpressao("((())");
    testarExpressao("{[(])}");
    testarExpressao(")(");
    testarExpressao("{[}]");
    testarExpressao("((a + b) * [c - d]");
    
    printf("\nTeste concluído!\n");
    
    return 0;
}