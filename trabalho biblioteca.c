#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 100
#define MAX_COMPRAS 100

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    float preco;
    int estoque;
} Livro;

typedef struct {
    int id;
    int quantidade;
    char titulo[100];
} Compra;

Livro biblioteca[MAX_LIVROS];
int total_livros = 0;

Compra historico_compras[MAX_COMPRAS];
int total_compras = 0;

void cadastrarLivro();
void verLivros();
void venderLivro();
void atualizarLivro();
void registrarVenda(int id, int quantidade, char comprador[100]);

void comprarLivro();
void verLivrosCliente();
void buscarLivroCliente();
void verComprasCliente();
void registrarCompra(int id, int quantidade, char comprador[100]);

int buscarLivroPorId(int id);
void menuFuncionario();
void menuCliente();

int main() {
    int opcao;
    while (1) {
        printf("\n--- Sistema de Biblioteca 1.0 ---\n");
        printf("1. Funcionario\n");
        printf("2. Cliente\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                menuFuncionario();
                break;
            case 2:
                menuCliente();
                break;
            case 3:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção invalida! Tente novamente.\n");
        }
    }
}

void cadastrarLivro() {
    if (total_livros >= MAX_LIVROS) {
        printf("Capacidade maxima de livros atingida!\n");
        return;
    }
    Livro novoLivro;
    
    printf("Digite o ID do livro: ");
    scanf("%d", &novoLivro.id);
    
    if (buscarLivroPorId(novoLivro.id) != -1) {
        printf("Livro com este ID já existe.\n");
        return;
    }
    
    printf("Digite o titulo do livro: ");
    scanf(" %[^\n]", novoLivro.titulo);
    
    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", novoLivro.autor);
    
    printf("Digite o preco do livro: ");
    scanf("%f", &novoLivro.preco);
    
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoLivro.estoque);
    
    biblioteca[total_livros] = novoLivro;
    total_livros++;
    
    printf("Livro cadastrado com sucesso!\n");
}

void verLivros() {
    if (total_livros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    
    for (int i = 0; i < total_livros; i++) {
        printf("\nID: %d\n", biblioteca[i].id);
        printf("Titulo: %s\n", biblioteca[i].titulo);
        printf("Autor: %s\n", biblioteca[i].autor);
        printf("Preco: %.2f\n", biblioteca[i].preco);
        printf("Estoque: %d\n", biblioteca[i].estoque);
    }
}

void venderLivro() {
    int id, quantidade;
    char comprador[100];
    printf("Digite o ID do livro que deseja vender: ");
    scanf("%d", &id);
    
    int indice = buscarLivroPorId(id);
    if (indice == -1) {
        printf("Livro nao encontrado.\n");
        return;
    }
    
    printf("Digite a quantidade que deseja vender: ");
    scanf("%d", &quantidade);
    
    printf("Digite o nome do comprador: ");
    scanf(" %[^\n]", comprador);
    
    if (biblioteca[indice].estoque < quantidade) {
        printf("Quantidade insuficiente em estoque.\n");
    } else {
        biblioteca[indice].estoque -= quantidade;
        registrarVenda(id, quantidade, comprador);
        printf("Venda realizada com sucesso!\n");
    }
}

void atualizarLivro() {
    int id;
    printf("Digite o ID do livro que deseja atualizar: ");
    scanf("%d", &id);
    
    int indice = buscarLivroPorId(id);
    if (indice == -1) {
        printf("Livro nao encontrado.\n");
        return;
    }
    
    printf("Digite o novo titulo do livro (atual: %s): ", biblioteca[indice].titulo);
    scanf(" %[^\n]", biblioteca[indice].titulo);
    
    printf("Digite o novo autor do livro (atual: %s): ", biblioteca[indice].autor);
    scanf(" %[^\n]", biblioteca[indice].autor);
    
    printf("Digite o novo preco do livro (atual: %.2f): ", biblioteca[indice].preco);
    scanf("%f", &biblioteca[indice].preco);
    
    printf("Digite a nova quantidade em estoque (atual: %d): ", biblioteca[indice].estoque);
    scanf("%d", &biblioteca[indice].estoque);
    
    printf("Livro atualizado com sucesso!\n");
}

void registrarVenda(int id, int quantidade, char comprador[100]) {
    
}

void comprarLivro() {
    int id, quantidade;
    char comprador[100];
    printf("Digite o ID do livro que deseja comprar: ");
    scanf("%d", &id);
    
    int indice = buscarLivroPorId(id);
    if (indice == -1) {
        printf("Livro nao encontrado.\n");
        return;
    }
    
    printf("Digite a quantidade que deseja comprar: ");
    scanf("%d", &quantidade);
    
    printf("Digite seu nome: ");
    scanf(" %[^\n]", comprador);
    
    if (biblioteca[indice].estoque < quantidade) {
        printf("Quantidade insuficiente em estoque.\n");
    } else {
        biblioteca[indice].estoque -= quantidade;
        registrarCompra(id, quantidade, comprador);
        printf("Compra realizada com sucesso!\n");
    }
}

void registrarCompra(int id, int quantidade, char comprador[100]) {
    if (total_compras >= MAX_COMPRAS) {
        printf("Não é possível registrar mais compras.\n");
        return;
    }

    Compra novaCompra;
    novaCompra.id = id;
    novaCompra.quantidade = quantidade;
    strcpy(novaCompra.titulo, biblioteca[buscarLivroPorId(id)].titulo);

    historico_compras[total_compras] = novaCompra;
    total_compras++;
}

void verLivrosCliente() {
    verLivros();
}

void buscarLivroCliente() {
    int id;
    printf("Digite o ID do livro que deseja buscar: ");
    scanf("%d", &id);
    
    int indice = buscarLivroPorId(id);
    if (indice == -1) {
        printf("Livro nao encontrado.\n");
    } else {
        printf("\nID: %d\n", biblioteca[indice].id);
        printf("Titulo: %s\n", biblioteca[indice].titulo);
        printf("Autor: %s\n", biblioteca[indice].autor);
        printf("Preco: %.2f\n", biblioteca[indice].preco);
        printf("Estoque: %d\n", biblioteca[indice].estoque);
    }
}

void verComprasCliente() {
    if (total_compras == 0) {
        printf("Você não comprou nenhum livro ainda.\n");
        return;
    }

    for (int i = 0; i < total_compras; i++) {
        printf("\nLivro: %s\n", historico_compras[i].titulo);
        printf("Quantidade: %d\n", historico_compras[i].quantidade);
    }
}

int buscarLivroPorId(int id) {
    for (int i = 0; i < total_livros; i++) {
        if (biblioteca[i].id == id) {
            return i;
        }
    }
    return -1;
}

void menuFuncionario() {
    int opcao;
    while (1) {
        printf("\n--- Menu Funcionario ---\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Ver Livros\n");
        printf("3. Vender Livro\n");
        printf("4. Atualizar Livro\n");
        printf("5. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastrarLivro();
                break;
            case 2:
                verLivros();
                break;
            case 3:
                venderLivro();
                break;
            case 4:
                atualizarLivro();
                break;
            case 5:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

void menuCliente() {
    int opcao;
    while (1) {
        printf("\n--- Menu Cliente ---\n");
        printf("--- Boas Compras! ---\n");
        printf("1. Ver Livros\n");
        printf("2. Comprar Livro\n");
        printf("3. Buscar Livro por ID\n");
        printf("4. Ver Livros Comprados\n");  
        printf("5. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                verLivrosCliente();
                break;
            case 2:
                comprarLivro();
                break;
            case 3:
                buscarLivroCliente();
                break;
            case 4:
                verComprasCliente(); 
                break;
            case 5:
                return;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}
