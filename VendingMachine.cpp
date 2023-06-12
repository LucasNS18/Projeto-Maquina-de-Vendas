#include <iostream>//executar operações de leitura e gravação em arquivos
#include <vector>//biblioteca para utilização de vetores
#include <algorithm>//biblioteca com conjunto de rotinas padronizadas da linguagem (entrada e saída de infos)
#include <locale>//biblioteca para garantir que caracteres como “ç” e acentuação gráficas sejam exibidos normalmente em nossos programas
using namespace std;

typedef struct {
    string nome;
    string codigo;
    double preco;
    int quantidade;
} Produto;

double Faturamento_Total = 0.0;//variante global
double Faturamento_Restante = 0.0;//variante global

void Listar_Produtos(const vector<Produto>& produtos) {//função que será usada para "chamar" a lista de produtos durante o funcionamento do programa
    if (produtos.empty()) {
        cout << "\nNenhum produto foi inserido!\n";
    } else {
        cout << "\nProdutos disponíveis:\n";
        for (const auto& produto : produtos) {
            cout << "\nNome: " << produto.nome;
            cout << "\nCódigo: " << produto.codigo;
            cout << "\nPreço: " << produto.preco;
            cout << "\nQuantidade: " << produto.quantidade << endl;
        }
    }
}

// Função Modo Administrador
void Modo_Administrador(vector<Produto>& produtos) {
    int opcao_ADM = 0;
    int Contador_Login = 0;
    string Nome_ADM, Nome_ADM_Compativel;
    string Senha_ADM, Senha_ADM_Compativel;

    if (Contador_Login == 0) {//Sign in (criação de conta)
        cout << "\n======= Criar Conta =======\n";
        cout << "Criar nome de: ";
        cin >> Nome_ADM;
        cout << "Criar senha: ";
        cin >> Senha_ADM;
        cout << "" << endl;
    }

    Contador_Login = 1;
    do {//Login (entrar) na conta
        if (Contador_Login == 1) {
            cout << "======= Entrar na Conta =======\n";
            cout << "Digite seu nome: ";
            cin >> Nome_ADM_Compativel;
            cout << "Digite sua senha: ";
            cin >> Senha_ADM_Compativel;
            cout << "" << endl;

            if (Nome_ADM == Nome_ADM_Compativel && Senha_ADM == Senha_ADM_Compativel) {
                cout << "\n======= Modo Administrador ativado =======" << endl;

                do {//tela inicial do ADM
                    cout << "\n======= Escolha uma opção: =======\n";
                    cout << "1 - Listar os produtos inseridos\n";
                    cout << "2 - Retirar um produto\n";
                    cout << "3 - Repor um produto\n";
                    cout << "4 - Ver faturamento da máquina\n";
                    cout << "5 - Sair do modo administrador e retornar à tela de login\n";
                    cout << "Opção escolhida: ";
                    cin >> opcao_ADM;
                    cout << "" << endl;

                    switch (opcao_ADM) {
                        // Listar os produtos inseridos
                        case 1: {
                            Listar_Produtos(produtos);
                            break;
                        }
                        // Excluir produto
                        case 2: {//Case caso os produtos estejam indisponíveis para remoção
                            if (produtos.empty()) {
                                cout << "\nNenhum produto disponível para remoção.\n";
                            } else {
                                string codigo;
                                cout << "\nDigite o código do produto que deseja remover: ";
                                cin >> codigo;

                                auto it = find_if(produtos.begin(), produtos.end(), [&codigo](const Produto& produto) {
                                    return produto.codigo == codigo;
                                });

                                if (it != produtos.end()) {
                                    Produto produto = *it;
                                    produtos.erase(it); // Remove o produto do vetor de produtos
                                    Faturamento_Restante -= produto.preco * produto.quantidade; // Atualiza o faturamento restante da máquina
                                    cout << "\nProduto retirado com sucesso!\n";
                                } else {
                                    cout << "\nProduto não encontrado.\n";
                                }
                            }
                            break;
                        }
                        // Repor produto
                        case 3: {//Case caso os produtos estejam vazios para a reposição
                            if (produtos.empty()) {
                                cout << "\nNenhum produto disponível para reposição.\n";
                            } else {
                                string codigo;
                                cout << "\nDigite o código do produto que deseja repor: ";
                                cin >> codigo;

                                auto it = find_if(produtos.begin(), produtos.end(), [&codigo](const Produto& produto) {
                                    return produto.codigo == codigo;
                                });

                                if (it != produtos.end()) {
                                    Produto& produto = *it;
                                    int quantidade;
                                    cout << "Digite a quantidade a ser reposta: ";
                                    cin >> quantidade;
                                    produto.quantidade += quantidade; // Atualiza a quantidade do produto.
                                    Faturamento_Restante += produto.preco * quantidade; // Atualiza o faturamento restante da máquina
                                    cout << "\nProduto reposto com sucesso!\n";
                                } else {
                                    cout << "\nProduto não encontrado.\n";
                                }
                            }
                            break;
                        }
                        // Ver faturamento da máquina
                        case 4: {
                            cout << "\nTotal faturado: R$" << Faturamento_Total << endl;
                            cout << "Faturamento restante: R$" << Faturamento_Restante << endl;
                            break;
                        }
                        // Sair do modo administrador
                        case 5: {
                            cout << "Encerrando o modo Administrador...\n";
                            break;
                        }
                        // Caso o usuário não digite nenhuma das três opções
                        default: {
                            cout << "\nOpção inválida! Tente novamente.\n";
                            break;
                        }
                    }
                } while (opcao_ADM != 5);

            } else {
                cout << "Nome ou/e senha incorreto(s)!\n";
                cout << "" << endl;
            }
        }
    } while (Nome_ADM != Nome_ADM_Compativel || Senha_ADM != Senha_ADM_Compativel);
}

// Função Modo Usuário
void Modo_Usuario(const vector<Produto>& produtos) {
    cout << "\n======= Modo Usuário ativado =======" << endl;

    int opcao = 0;

    while (opcao != 3) {//tela de opções do modo usuario
        cout << "\n======= Escolha uma opção: =======\n";
        cout << "1 - Listar os produtos disponíveis\n";
        cout << "2 - Realizar uma compra\n";
        cout << "3 - Sair do modo usuário e retornar à tela de login\n";
        cout << "Opção escolhida: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {//case q chama a função da lista de produtos
                Listar_Produtos(produtos);
                break;
            }
            case 2: {//case de compra dos produtos
                string codigo;
                cout << "\nDigite o código do produto que deseja comprar: ";
                cin >> codigo;

                auto it = find_if(produtos.begin(), produtos.end(), [&codigo](const Produto& produto) {
                    return produto.codigo == codigo;
                });

                if (it != produtos.end()) {
                    Produto produto = *it;
                    int quantidade_compra;
                    cout << "\nProduto encontrado!";
                    cout << "Digite a quantidade que deseja comprar: ";
                    cin >> quantidade_compra;

                    double valor_total = produto.preco * quantidade_compra;
                    cout << "Valor total da compra: R$" << valor_total << endl;

                    double valor_pago;
                    cout << "Digite o valor que você irá dar à máquina: R$";
                    cin >> valor_pago;

                    if (valor_pago >= valor_total) {
                        double troco = valor_pago - valor_total;
                        cout << "Pagamento realizado com sucesso! Seu troco é de R$" << troco << endl;
                    } else {
                        cout << "Valor insuficiente. A compra não pode ser realizada." << endl;
                    }
                } else {
                    cout << "\nProduto não encontrado.\n";
                }
                break;
            }

            case 3: {//case de saída do módo usuário
                cout << "\nEncerrando o modo Usuário...\n";
                break;
            }
            default:
                cout << "\nOpção inválida! Tente novamente.\n";
                break;
        }
    }
}

int main() {
    int Opcao_Login;

    vector<Produto> produtos = {{"Coca-Cola 600ml", "001", 6.5, 10},   // Produto 1
                                {"Água com Gás", "002", 3.0, 5},  // Produto 2
                                {"Água Mineral", "003", 2.5, 3},   // Produto 3
                                {"Diamante Negro", "004", 10.0, 8},  // Produto 4
                                {"Salgadinho cheetos", "005", 9.0, 6}};   // Produto 5

    do {//funcionamento da tela inicial (login)
        cout << "\n===== VENDING MACHINE =====\n" << endl;
        cout << "====== Tela de Login ======\n" << endl;
        cout << "Selecione um modo:" << endl;
        cout << "1 - ADMINISTRADOR" << endl;
        cout << "2 - USUÁRIO" << endl;
        cout << "3 - SAIR DA MÁQUINA DE VENDAS" << endl;
        cout << "Modo escolhido: ";
        cin >> Opcao_Login;

        if (Opcao_Login == 1) {
            Modo_Administrador(produtos);
        } else if (Opcao_Login == 2) {
            Modo_Usuario(produtos);
        } else if (Opcao_Login == 3) {
            cout << "\nEncerrando o programa...\n";
            break;
        } else {
            cout << "Opção inválida! Tente novamente." << endl;
        }
    } while (true);

    return 0;
}
