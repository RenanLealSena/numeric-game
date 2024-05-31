#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TamanhoNome 50
#define TamanhoTelefone 15
#define TamanhoEmail 50

// Estrutura para armazenar os contatos
typedef struct {
    char nome[TamanhoNome];
    char telefone[TamanhoTelefone];
    char email[TamanhoEmail];
} Contato;

// Função para mesclar duas sublistas ordenadas em uma única lista ordenada
void mesclar(Contato arr[], Contato temp[], int esquerda, int meio, int direita) {
    int i = esquerda;
    int j = meio + 1;
    int k = esquerda;

    while (i <= meio && j <= direita) {
        if (strcmp(arr[i].nome, arr[j].nome) <= 0) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= meio) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= direita) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (i = esquerda; i <= direita; i++) {
        arr[i] = temp[i];
    }
}

// Função principal que implementa o Merge Sort
void ordenarMerge(Contato arr[], Contato temp[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        ordenarMerge(arr, temp, esquerda, meio);
        ordenarMerge(arr, temp, meio + 1, direita);

        mesclar(arr, temp, esquerda, meio, direita);
    }
}

// Função para imprimir os contatos
void imprimirContatos(Contato arr[], int tamanho) {
    printf("\nLista de Contatos:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. Nome: %s\n   Telefone: %s\n   Email: %s\n\n", i + 1, arr[i].nome, arr[i].telefone, arr[i].email);
    }
}

// Função para adicionar um contato
void adicionarContato(Contato arr[], int *tamanho, const char *nome, const char *telefone, const char *email) {
    strcpy(arr[*tamanho].nome, nome);
    strcpy(arr[*tamanho].telefone, telefone);
    strcpy(arr[*tamanho].email, email);
    (*tamanho)++;
}

// Função para ler um contato do usuário
void lerContatoDoUsuario(Contato *contato) {
    printf("Digite o nome: ");
    fgets(contato->nome, TamanhoNome, stdin);
    contato->nome[strcspn(contato->nome, "\n")] = 0; // Remover caracter de nova linha

    printf("Digite o telefone: ");
    fgets(contato->telefone, TamanhoTelefone, stdin);
    contato->telefone[strcspn(contato->telefone, "\n")] = 0; // Remover caracter de nova linha

    printf("Digite o email: ");
    fgets(contato->email, TamanhoEmail, stdin);
    contato->email[strcspn(contato->email, "\n")] = 0; // Remover caracter de nova linha
}

// Função para remover contatos duplicados
int removerDuplicados(Contato arr[], int tamanho) {
    if (tamanho == 0) return 0;

    int j = 0;
    for (int i = 1; i < tamanho; i++) {
        if (strcmp(arr[i].nome, arr[j].nome) != 0 || strcmp(arr[i].telefone, arr[j].telefone) != 0 || strcmp(arr[i].email, arr[j].email) != 0) {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1;
}

// Função para encontrar um contato pelo nome
int encontrarContato(Contato arr[], int tamanho, const char *nome) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(arr[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Função para remover um contato específico
void removerContato(Contato arr[], int *tamanho, const char *nome) {
    int indice = encontrarContato(arr, *tamanho, nome);
    if (indice != -1) {
        for (int i = indice; i < *tamanho - 1; i++) {
            arr[i] = arr[i + 1];
        }
        (*tamanho)--;
        printf("Contato '%s' removido com sucesso.\n", nome);
    } else {
        printf("Contato não encontrado.\n");
    }
}

// Função para atualizar um contato específico
void atualizarContato(Contato arr[], int tamanho, const char *nome) {
    int indice = encontrarContato(arr, tamanho, nome);
    if (indice != -1) {
        printf("Digite os novos detalhes para %s:\n", nome);
        lerContatoDoUsuario(&arr[indice]);
        printf("Contato '%s' atualizado com sucesso.\n", nome);
    } else {
        printf("Contato não encontrado.\n");
    }
}

// Função para exibir o menu e obter a escolha do usuário
int obterEscolhaMenu() {
    int escolha;
    printf("\nMenu:\n");
    printf("1. Adicionar contato\n");
    printf("2. Ordenar e exibir contatos\n");
    printf("3. Remover duplicados\n");
    printf("4. Remover contato especifico\n");
    printf("5. Atualizar contato especifico\n");
    printf("6. Sair\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    getchar(); // Consumir caractere de nova linha deixado por scanf
    return escolha;
}

int main() {
    int maxContatos = 100;
    Contato *contatos = (Contato *)malloc(maxContatos * sizeof(Contato));
    Contato *temp = (Contato *)malloc(maxContatos * sizeof(Contato));
    int quantidadeContatos = 0;
    int escolha;

    while (1) {
        escolha = obterEscolhaMenu();
        switch (escolha) {
            case 1:
                if (quantidadeContatos < maxContatos) {
                    lerContatoDoUsuario(&contatos[quantidadeContatos]);
                    quantidadeContatos++;
                } else {
                    printf("Lista de contatos esta cheia!\n");
                }
                break;
            case 2:
                ordenarMerge(contatos, temp, 0, quantidadeContatos - 1);
                imprimirContatos(contatos, quantidadeContatos);
                break;
            case 3:
                ordenarMerge(contatos, temp, 0, quantidadeContatos - 1); // Ordenar antes de remover duplicatas
                quantidadeContatos = removerDuplicados(contatos, quantidadeContatos);
                printf("Duplicados removidos.\n");
                break;
            case 4: {
                char nome[TamanhoNome];
                printf("Digite o nome do contato a ser removido: ");
                fgets(nome, TamanhoNome, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remover caracter de nova linha
                removerContato(contatos, &quantidadeContatos, nome);
                break;
            }
            case 5: {
                char nome[TamanhoNome];
                printf("Digite o nome do contato a ser atualizado: ");
                fgets(nome, TamanhoNome, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remover caracter de nova linha
                atualizarContato(contatos, quantidadeContatos, nome);
                break;
            }
            case 6:
                free(contatos);
                free(temp);
                printf("Adeus!\n");
                return 0;
            default:
                printf("Escolha invalida! Tente novamente.\n");
        }
    }

    return 0;
}
