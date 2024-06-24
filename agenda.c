#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 100
#define MAX_NOME 50
#define MAX_TELEFONE 20
#define ARQUIVO_CONTATOS "contatos.dat"

// Estrutura para armazenar dados de um contato
typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
} Contato;

// Estrutura para armazenar o catálogo de contatos
typedef struct {
    Contato contatos[MAX_CONTATOS];
    int total;
} Catalogo;

// Função para adicionar um contato ao catálogo
void adicionar_contato(Catalogo *catalogo, char *nome, char *telefone) {
    if (catalogo->total < MAX_CONTATOS) {
        strncpy(catalogo->contatos[catalogo->total].nome, nome, MAX_NOME);
        strncpy(catalogo->contatos[catalogo->total].telefone, telefone, MAX_TELEFONE);
        catalogo->total++;
        printf("Contato adicionado com sucesso!\n");
    } else {
        printf("Catálogo cheio, não é possível adicionar mais contatos.\n");
    }
}

// Função para pesquisar um contato no catálogo
void pesquisar_contato(Catalogo *catalogo, char *nome) {
    for (int i = 0; i < catalogo->total; i++) {
        if (strcmp(catalogo->contatos[i].nome, nome) == 0) {
            printf("Contato encontrado: %s - %s\n", catalogo->contatos[i].nome, catalogo->contatos[i].telefone);
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

// Função para excluir um contato do catálogo
void excluir_contato(Catalogo *catalogo, char *nome) {
    for (int i = 0; i < catalogo->total; i++) {
        if (strcmp(catalogo->contatos[i].nome, nome) == 0) {
            for (int j = i; j < catalogo->total - 1; j++) {
                catalogo->contatos[j] = catalogo->contatos[j + 1];
            }
            catalogo->total--;
            printf("Contato excluído com sucesso!\n");
            return;
        }
    }
    printf("Contato não encontrado.\n");
}

// Função para salvar os contatos em um arquivo
void salvar_contatos(Catalogo *catalogo) {
    FILE *arquivo = fopen(ARQUIVO_CONTATOS, "wb");
    if (arquivo != NULL) {
        fwrite(catalogo, sizeof(Catalogo), 1, arquivo);
        fclose(arquivo);
        printf("Contatos salvos com sucesso!\n");
    } else {
        printf("Erro ao salvar contatos.\n");
    }
}

// Função para carregar os contatos de um arquivo
void carregar_contatos(Catalogo *catalogo) {
    FILE *arquivo = fopen(ARQUIVO_CONTATOS, "rb");
    if (arquivo != NULL) {
        fread(catalogo, sizeof(Catalogo), 1, arquivo);
        fclose(arquivo);
        printf("Contatos carregados com sucesso!\n");
    } else {
        catalogo->total = 0;
        printf("Nenhum contato para carregar.\n");
    }
}

// Função principal que executa o menu de opções
int main() {
    Catalogo catalogo;
    catalogo.total = 0;
    carregar_contatos(&catalogo);

    int opcao;
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];

    do {
        printf("\nCatálogo de Contatos\n");
        printf("1. Adicionar Contato\n");
        printf("2. Pesquisar Contato\n");
        printf("3. Excluir Contato\n");
        printf("4. Salvar Contatos\n");
        printf("5. Carregar Contatos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Digite o nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite o telefone: ");
                fgets(telefone, MAX_TELEFONE, stdin);
                telefone[strcspn(telefone, "\n")] = '\0';
                adicionar_contato(&catalogo, nome, telefone);
                break;
            case 2:
                printf("Digite o nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                pesquisar_contato(&catalogo, nome);
                break;
            case 3:
                printf("Digite o nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                excluir_contato(&catalogo, nome);
                break;
            case 4:
                salvar_contatos(&catalogo);
                break;
            case 5:
                carregar_contatos(&catalogo);
                break;
            case 0:
                salvar_contatos(&catalogo);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
