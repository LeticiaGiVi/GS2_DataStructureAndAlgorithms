#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Lista simplesmente encadeada
/*Criar uma lista de inteiros;  Inserir em ordem crescente;  Remover um elemento dado um valor;  Buscar um valor e retornar o ponteiro para o nó (ou NULL).*/
typedef struct NoSimples {
    int valor;          
    struct NoSimples *prox;     
} NoSimples;

NoSimples *lista1 = NULL; 

void inserirListaSimples(NoSimples **head, int valor) {
    NoSimples *novo = malloc(sizeof(NoSimples));
    if (!novo) {
        perror("malloc"); exit(1); 
    }
    novo->valor = valor;

    if (*head == NULL || (*head)->valor >= valor) {
        novo->prox = *head;
        *head = novo;
        return;
    }

    NoSimples *atual = *head; 
    while (atual->prox != NULL && atual->prox->valor < valor) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
}

void imprimirListaSimples(NoSimples *head) {
    NoSimples *tmp = head;
    while (tmp != NULL) {
        printf("%d -> ", tmp->valor);
        tmp = tmp->prox;
    }
    printf("NULL\n");
}

NoSimples* buscarListaSimples(NoSimples *head, int valor) {
    NoSimples *tmp = head; // Inicializa tmp com o início da lista
    while (tmp != NULL) {
        if (tmp->valor == valor) {
            return tmp;
        }
        tmp = tmp->prox;
    }
    return NULL;
}

int removerListaSimples(NoSimples **head, int valor) {
    if (*head == NULL) {
        return 0; 
    }
    if ((*head)->valor == valor) {
        NoSimples *temp = *head;
        *head = (*head)->prox;
        free(temp);
        return 1;
    }

    NoSimples *atual = *head;
    while (atual->prox != NULL && atual->prox->valor != valor) {
        atual = atual->prox;
    }

    if (atual->prox != NULL && atual->prox->valor == valor) {
        NoSimples *temp = atual->prox;
        atual->prox = temp->prox;
        free(temp);
        return 1;
    }
    return 0;
}

void liberarListaSimples(NoSimples **head) {
    NoSimples *atual = *head;
    NoSimples *temp;
    
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    
    *head = NULL;
}

// Lista duplamente encadeada
/*Inserir no início e no final;  Remover do início e do final;  Percorrer a lista nos dois sentidos (head → tail, tail → head).*/
typedef struct NoDuplo {
    int valor;
    struct NoDuplo *ant;   
    struct NoDuplo *prox; 
} NoDuplo;

NoDuplo *lista2 = NULL;

void inserirInicioListaDupla(NoDuplo **head, int valor) {
    NoDuplo *novo = malloc(sizeof(NoDuplo));
    novo->valor = valor;
    novo->ant = NULL;
    novo->prox = *head;
    if (*head != NULL) (*head)->ant = novo;
    *head = novo;
}

void inserirFimListaDupla(NoDuplo **head, int valor) {
    NoDuplo *novo = malloc(sizeof(NoDuplo));
    novo->valor = valor;
    novo->prox = NULL;

    if (*head == NULL) {
        novo->ant = NULL;
        *head = novo;
        return;
    }
    NoDuplo *tmp = *head;
    while (tmp->prox != NULL) tmp = tmp->prox;
    tmp->prox = novo;
    novo->ant = tmp;
}

void removerInicioListaDupla(NoDuplo **head) {
    if (*head == NULL) {
        return;
    }
    NoDuplo *tmp = *head;
    *head = (*head)->prox;
    if (*head != NULL) {
        (*head)->ant = NULL;
    }
    free(tmp);
}

void removerFimListaDupla(NoDuplo **head) {
    if (*head == NULL) return;
    if ((*head)->prox == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    NoDuplo *tmp = *head;
    while (tmp->prox != NULL) tmp = tmp->prox;
    tmp->ant->prox = NULL;
    free(tmp);
}

void imprimirListaDupla(NoDuplo *head) {
    NoDuplo *tmp = head;
    while (tmp != NULL) {
        printf("%d <-> ", tmp->valor);
        tmp = tmp->prox;
    }
    printf("NULL\n");
}

void imprimirContrarioListaDupla(NoDuplo *head) {
    if (head == NULL) return;
    NoDuplo *tmp = head;
    while (tmp->prox != NULL) tmp = tmp->prox; 
    while (tmp != NULL) {
        printf("%d <-> ", tmp->valor);
        tmp = tmp->ant;
    }
    printf("NULL\n");
}

void liberarListaDupla(NoDuplo **head) {
    NoDuplo *atual = *head;
    NoDuplo *temp;
    
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    
    *head = NULL;
}

//lista circular 
/*Implementar uma lista circular de inteiros;  Função para avançar "k" posições a partir de um nó;  Função para remover um nó específico da lista circular mantendo a circularidade.*/
typedef struct {
    NoSimples *inicio;
    NoSimples *fim;
    int tam;
} ListaCircular;

ListaCircular* criarListaCircular() {
    ListaCircular *lista = (ListaCircular*)malloc(sizeof(ListaCircular));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return lista;
}

void inserirListaCircular(ListaCircular *lista3, int num) {
    NoSimples *novo = malloc(sizeof(NoSimples));
    if(novo) {
        novo->valor = num;
        if(lista3->inicio == NULL) { 
            lista3->inicio = novo;
            lista3->fim = novo;
            novo->prox = novo; 
        } else { 
            novo->prox = lista3->inicio;
            lista3->inicio = novo;
            lista3->fim->prox = novo; 
        }
        lista3->tam++;
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

void imprimirListaCircular(ListaCircular *lista3) {
    if (lista3->inicio == NULL) {
        printf("Lista vazia\n");
        return;
    }
    NoSimples *tmp = lista3->inicio;
    int count = 0;
    do {
        printf("%d -> ", tmp->valor);
        tmp = tmp->prox;
        count++;
    } while (count < lista3->tam);
    printf("(início)\n");
}

NoSimples* avancarK(NoSimples *noAtual, int k) {
    if(noAtual == NULL) return NULL;

    NoSimples *atual = noAtual;
    for(int i = 0; i < k; i++) {
        atual = atual->prox;
    }
    return atual;
}

NoSimples* removerListaCircular(ListaCircular *lista, int num) {
    NoSimples *aux, *remover = NULL;
    if(lista->inicio) {
        if(lista->inicio == lista->fim && lista->inicio->valor == num) {
            remover = lista->inicio;
            lista->inicio = NULL;
            lista->fim = NULL;
            lista->tam--;
        }
        else if(lista->inicio->valor == num) {
            remover = lista->inicio;
            lista->inicio = remover->prox;
            lista->fim->prox = lista->inicio;
            lista->tam--;
        }
        else {
            aux = lista->inicio;
            while(aux->prox != lista->inicio && aux->prox->valor != num)
                aux = aux->prox;
            if(aux->prox->valor == num) {
                if(lista->fim == aux->prox) {
                    remover = aux->prox;
                    aux->prox = remover->prox;
                    lista->fim = aux;
                }
                else {
                    remover = aux->prox;
                    aux->prox = remover->prox;
                }
                lista->tam--;
            }
        }
    }
    return remover;
}

void liberarListacircular(ListaCircular* lista) {
    if (lista->inicio == NULL) {
        return;
    }
    
    NoSimples* atual = lista->inicio;
    NoSimples* proximo;

    NoSimples* ultimo = lista->inicio;
    while (ultimo->prox != lista->inicio) {
        ultimo = ultimo->prox;
    }
    ultimo->prox = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    
    lista->inicio = NULL;
}

//Pilha (stack)
/*Implementar uma pilha usando lista encadeada;  Operações: push, pop, top, isEmpty;  Exemplo de uso: verificar se uma expressão com parênteses ()[]{} está balanceada.*/
typedef struct NoPilha {
    char dado;
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
    int tam;
} Pilha;

void inicializarPilha(Pilha *pilha) {
    pilha->topo = NULL;
    pilha->tam = 0;
}

int isEmptyPilha(Pilha *pilha) {
    return pilha->topo == NULL;
}

void push(Pilha *pilha, char valor) {
    NoPilha *novo = malloc(sizeof(NoPilha));
    if (!novo) { perror("malloc"); exit(1); }
    novo->dado = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tam++;
}

char pop(Pilha *pilha) {  
    if (isEmptyPilha(pilha)) {
        printf("Pilha vazia\n");
        return '0';  
    }
    NoPilha *tmp = pilha->topo;
    char valor = tmp->dado;
    pilha->topo = tmp->prox;
    free(tmp);
    pilha->tam--;
    return valor;
}

char top(Pilha *pilha) {  
    if (isEmptyPilha(pilha)) {
        return '0';
    }  
    return pilha->topo->dado;
}

void imprimirPilha(Pilha *pilha) {
    if (isEmptyPilha(pilha)) {
        printf("Pilha vazia\n");
        return;
    }

    NoPilha *atual = pilha->topo;
    printf("Topo -> ");
    while (atual != NULL) {
        printf("%c ", atual->dado);  
        atual = atual->prox;
    }
    printf("\n");
}

int Abertura(char c) {
    return (c == '(' || c == '[' || c == '{');
}

int Fechamento(char c) {
    return (c == ')' || c == ']' || c == '}');
}

int Par(char abertura, char fechamento) {
    return ((abertura == '(' && fechamento == ')') ||
            (abertura == '[' && fechamento == ']') ||
            (abertura == '{' && fechamento == '}'));
}

void liberarPilha(Pilha* pilha) {
    while (!isEmptyPilha(pilha)) {
        pop(pilha);
    }
}

int verificarBalanceamento(const char* expressao) {
    Pilha pilha;
    inicializarPilha(&pilha);
    
    int tamanho = strlen(expressao);
    int i;
    
    for (i = 0; i < tamanho; i++) {
        char c = expressao[i];
        
        if (Abertura(c)) {
            push(&pilha, c);
        }
        else if (Fechamento(c)) {
            if (isEmptyPilha(&pilha)) {
                liberarPilha(&pilha);
                return 0;
            }
            
            char topoAtual = pop(&pilha);
            if (!Par(topoAtual, c)) {
                liberarPilha(&pilha);
                return 0; 
            }
        }
    }
    int resultado = isEmptyPilha(&pilha);
    liberarPilha(&pilha);
    
    return resultado;
}

void testarExpressao(const char* expressao) {
    printf("\nExpressão: \"%s\"\n", expressao);
    
    if (verificarBalanceamento(expressao)) {
        printf("✓ Balanceada\n");
    } else {
        printf("✗ NÃO balanceada\n");
    }
}

//fila (queue)
/*Implementar uma fila usando lista encadeada;  Operações: enqueue, dequeue, front, isEmpty;  Exemplo de uso: simular atendimento de clientes com chegada em ordem e saída em FIFO.*/
typedef struct FilaClientes {
    char nome[10];
    struct FilaClientes *prox;
} FilaClientes;

typedef struct {
    FilaClientes *ini, *fim;
    int tam;
} Fila;

void inicializarFila(Fila *fila) {
    fila->ini = NULL;
    fila->fim = NULL;
    fila->tam = 0;
}

int isEmptyFila(Fila *fila) {
    return fila->ini == NULL;
}

char* dequeue(Fila *fila) {
    if (isEmptyFila(fila)) {
        printf("Fila vazia!\n");
        return NULL;
    }
    FilaClientes *tmp = fila->ini;

    char *nome = malloc(10 * sizeof(char));
    if (!nome) {
        perror("malloc");
        exit(1);
    }
    strcpy(nome, tmp->nome); 

    fila->ini = tmp->prox;
    if (fila->ini == NULL) fila->fim = NULL;
    free(tmp);
    fila->tam--;

    return nome; 
}

void enqueue(Fila *fila, const char *nome) {
    FilaClientes *novo = malloc(sizeof(FilaClientes));
    if (!novo) { 
        perror("malloc"); 
        exit(1); 
    }
    strcpy(novo->nome, nome);  
    novo->prox = NULL;

    if (isEmptyFila(fila)) {
        fila->ini = novo;
    } else {
        fila->fim->prox = novo;
    }
    fila->fim = novo;
    fila->tam++;
}

char* front(Fila *fila) { 
    if (isEmptyFila(fila)) return NULL;
    return fila->ini->nome;  
}

void liberarFila(Fila* fila) {
    while (!isEmptyFila(fila)) {
        char *nome = dequeue(fila);
        if (nome) free(nome);
    }
}


int main(){
    printf("TESTE LISTA SIMPLESMENTE ENCADEADA\n");
    int num;
    char r = 's';

    while(r == 's' || r == 'S') {
        printf("\nInsira um numero para adicionar na lista: ");
        scanf("%d", &num);
        inserirListaSimples(&lista1, num);
        printf("Gostaria de adicionar mais um numero? (s/n): ");
        scanf(" %c", &r);
    }

    printf("\nLista: ");
    imprimirListaSimples(lista1);

    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nInsira o numero que voce quer buscar na lista: ");
        scanf("%d", &num);
        NoSimples *encontrado = buscarListaSimples(lista1, num);
        if (encontrado) {
            printf("Numero %d encontrado no endereco: %p\n", num, (void*)encontrado);
        } else {
            printf("Numero %d nao encontrado.\n", num);
        }
        printf("Gostaria de buscar mais um numero? (s/n): ");
        scanf(" %c", &r);
    }

    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nInsira o numero que voce quer remover da lista: ");
        scanf("%d", &num);
        if (removerListaSimples(&lista1, num)) {
            printf("Numero removido com sucesso!\n");
        } else {
            printf("Numero nao encontrado.\n");
        }
        printf("Lista apos remocao: ");
        imprimirListaSimples(lista1);
        printf("Gostaria de remover mais um numero? (s/n): ");
        scanf(" %c", &r);
    }
    
    liberarListaSimples(&lista1);

    printf("\nTESTE LISTA DUPLAMENTE ENCADEADA\n");
    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nInsira um numero para adicionar no inicio da lista: ");
        scanf("%d", &num);
        inserirInicioListaDupla(&lista2, num);
        printf("Gostaria de adicionar mais um numero? (s/n): ");
        scanf(" %c", &r);
    }

    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nInsira um numero para adicionar no fim da lista: ");
        scanf("%d", &num);
        inserirFimListaDupla(&lista2, num);
        printf("Gostaria de adicionar mais um numero? (s/n): ");
        scanf(" %c", &r);
    }

    printf("\nLista original: \n");
    imprimirListaDupla(lista2);

    printf("Lista ao contrario: \n");
    imprimirContrarioListaDupla(lista2);    

    printf("\nRemovendo primeiro numero\n");
    removerInicioListaDupla(&lista2);
    printf("Lista apos remocao: \n");
    imprimirListaDupla(lista2);

    printf("\nRemovendo ultimo numero\n");
    removerFimListaDupla(&lista2);
    printf("Lista apos remocao: \n");
    imprimirListaDupla(lista2);
    
    liberarListaDupla(&lista2);

    printf("\nTESTE LISTA CIRCULAR\n");
    ListaCircular *lista3 = criarListaCircular();

    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nInsira um numero para adicionar na lista circular: ");
        scanf("%d", &num);
        inserirListaCircular(lista3, num);
        printf("Gostaria de adicionar mais um numero? (s/n): ");
        scanf(" %c", &r);
    }

    printf("\nLista circular: \n");
    imprimirListaCircular(lista3);

    NoSimples *noAtual = lista3->inicio;
    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nNumero de posicoes que voce deseja avancar: ");
        scanf("%d", &num);
        NoSimples *noAvancado = avancarK(noAtual, num);
        if (noAvancado) {
            printf("Avancado %d posicoes: %d\n", num, noAvancado->valor);
        }
        printf("Gostaria de avancar mais posicoes? (s/n): ");
        scanf(" %c", &r);
    }

    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nInsira o numero para remover da lista circular: ");
        scanf("%d", &num);
        NoSimples *removido = removerListaCircular(lista3, num);
        if (removido) {
            printf("Numero %d removido!\n", removido->valor);
            free(removido);
        } else {
            printf("Numero nao encontrado.\n");
        }
        printf("\nLista apos remocao: \n");
        imprimirListaCircular(lista3);
        printf("Gostaria de remover mais um numero? (s/n): ");
        scanf(" %c", &r);
    }
    
    liberarListacircular(lista3);

    printf("\nTESTE PILHA\n");
    Pilha pilha;
    inicializarPilha(&pilha);

    printf("\nPilha vazia? %s\n", isEmptyPilha(&pilha) ? "Sim" : "Nao");  

    char dado;
    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nInsira um caractere para adicionar na pilha: ");
        scanf(" %c", &dado);
        push(&pilha, dado);
        printf("Gostaria de adicionar mais um caractere? (s/n): ");
        scanf(" %c", &r);
    }

    printf("\nPilha vazia? %s\n", isEmptyPilha(&pilha) ? "Sim" : "Nao");

    printf("\nEstado atual da pilha:\n");
    imprimirPilha(&pilha);

    printf("\nRetirando o ultimo dado da pilha\n");
    printf("Pop: %c\n", pop(&pilha));  
    printf("Top: %c\n", top(&pilha));  

    printf("\nEstado da pilha:\n");
    imprimirPilha(&pilha);

    printf("\nPop: %c\n", pop(&pilha));  
    printf("Top: %c\n", top(&pilha));  

    printf("\nEstado final da pilha:\n");
    imprimirPilha(&pilha);
    
    printf("\n\nTESTE DE BALANCEAMENTO DE EXPRESSÕES\n");
    testarExpressao("{[()]}");
    testarExpressao("((a + b) * [c - d])");
    testarExpressao("{[}]");
    testarExpressao("((a + b) * [c - d]");
    
    liberarPilha(&pilha);

    printf("\nTESTE FILA\n");
    Fila fila;
    inicializarFila(&fila);

    char nome[10];
    r = 's';
    while(r == 's' || r == 'S') {
        printf("\nInsira um nome para adicionar na fila (maximo 10 letras): ");
        scanf("%9s", nome);
        enqueue(&fila, nome);
        printf("Gostaria de adicionar mais um nome? (s/n): ");
        scanf(" %c", &r);
    }

    printf("\nPrimeiro da fila: %s\n", front(&fila));
    printf("\nRemovendo o primeiro da fila\n");
    char *nomeRemovido = dequeue(&fila);
    if (nomeRemovido) {
        printf("Removido: %s\n", nomeRemovido);
        free(nomeRemovido);
    }
    printf("\nPrimeiro da fila: %s\n", front(&fila));
    printf("\nRemovendo o primeiro da fila\n");
    char *nomeRemovido2 = dequeue(&fila);
    if (nomeRemovido2) {
        printf("Removido: %s\n", nomeRemovido2);
        free(nomeRemovido2);
    }
    
    liberarFila(&fila);

    return 0;
}