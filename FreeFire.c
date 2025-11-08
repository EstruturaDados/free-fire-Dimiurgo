#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
#define TAM 50

typedef enum {
    POR_NOME,
    POR_TIPO,
    POR_PRIORIDADE
} Criterio;

typedef struct {
    char nome[TAM];
    char tipo[TAM];
    int qtd;
    int prioridade;
} Item;

Item mochila[MAX];
int total = 0;
bool ordenado_por_nome = false;
int comparacoes = 0;

void adicionar() {
    if (total >= MAX) {
        printf("\nMochila lotada!\n");
        return;
    }
    
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", mochila[total].nome);
    
    printf("Digite o tipo: ");
    scanf(" %[^\n]", mochila[total].tipo);
    
    printf("Digite a quantidade: ");
    scanf("%d", &mochila[total].qtd);
    
    printf("Digite a prioridade (1 a 5): ");
    scanf("%d", &mochila[total].prioridade);
    
    total++;
    ordenado_por_nome = false;
    printf("\nItem adicionado com sucesso!\n");
}

void remover() {
    if (total == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    
    char busca[TAM];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", busca);
    
    int achei = -1;
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, busca) == 0) {
            achei = i;
            break;
        }
    }
    
    if (achei == -1) {
        printf("\nItem nao encontrado.\n");
        return;
    }
    
    for (int i = achei; i < total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    total--;
    ordenado_por_nome = false;
    printf("\nItem removido com sucesso!\n");
}

void ordenar() {
    if (total == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    
    int opcao;
    printf("\nEscolha o criterio de ordenacao:\n");
    printf("1 - Por nome\n");
    printf("2 - Por tipo\n");
    printf("3 - Por prioridade\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    
    comparacoes = 0;
    
    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            int deve_mover = 0;
            
            if (opcao == 1) {
                deve_mover = strcmp(mochila[j].nome, chave.nome) > 0;
            } else if (opcao == 2) {
                deve_mover = strcmp(mochila[j].tipo, chave.tipo) > 0;
            } else if (opcao == 3) {
                deve_mover = mochila[j].prioridade > chave.prioridade;
            }
            
            if (!deve_mover) break;
            
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
    
    ordenado_por_nome = (opcao == 1);
    printf("\nItens ordenados com sucesso!\n");
    printf("Total de comparacoes: %d\n", comparacoes);
}

void busca_binaria() {
    if (!ordenado_por_nome) {
        printf("\nERRO: A mochila precisa estar ordenada por nome!\n");
        printf("Use a opcao 4 para ordenar por nome primeiro.\n");
        return;
    }
    
    if (total == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    
    char busca[TAM];
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", busca);
    
    int esq = 0, dir = total - 1;
    int encontrado = -1;
    
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int cmp = strcmp(mochila[meio].nome, busca);
        
        if (cmp == 0) {
            encontrado = meio;
            break;
        } else if (cmp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    
    if (encontrado != -1) {
        printf("\n=== ITEM ENCONTRADO ===\n");
        printf("Nome: %s\n", mochila[encontrado].nome);
        printf("Tipo: %s\n", mochila[encontrado].tipo);
        printf("Quantidade: %d\n", mochila[encontrado].qtd);
        printf("Prioridade: %d\n", mochila[encontrado].prioridade);
        printf("=======================\n");
    } else {
        printf("\nItem nao encontrado.\n");
    }
}

void listar() {
    printf("\n==============================================\n");
    
    if (total == 0) {
        printf("Nenhum item na mochila.\n");
        printf("==============================================\n");
        return;
    }
    
    printf("ITENS NA MOCHILA (%d/%d)\n", total, MAX);
    printf("==============================================\n");
    printf("%-20s %-15s %-10s %s\n", "Nome", "Tipo", "Qtd", "Prior.");
    printf("----------------------------------------------\n");
    
    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %-10d %d\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].qtd,
               mochila[i].prioridade);
    }
    printf("==============================================\n");
}

int main() {
    int escolha;
    
    do {
        printf("\n--- MENU ---\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar itens\n");
        printf("5 - Buscar item (busca binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        
        switch (escolha) {
            case 1:
                adicionar();
                break;
            case 2:
                remover();
                break;
            case 3:
                listar();
                break;
            case 4:
                ordenar();
                break;
            case 5:
                busca_binaria();
                break;
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (escolha != 0);
    
    return 0;
}