#include <iostream> // entrada e saída de dados
#include <fstream>  // manipulação de arquivos (leitura e escrita)
#include <vector>   // container de vetor 
#include <string>   // manipulação de strings
#include <algorithm> // funções algorítmicas, como busca e ordenação
#include <limits> // Para limpar o buffer de entrada

using namespace std;

// Estruturas para mostrar dados
struct Passageiro {
    int codigo;
    char nome[100]; // Array fixo para manipulação binária
    char endereco[200];
    int telefone;
    int quantidade_voos; // Novo campo para a quantidade de voos
    int pontos_fidelidade; // Novo campo para os pontos de fidelidade
};

struct Voo {
    int numero;
    char data[20];
    char origem[50];
    char destino[50];
    vector<int> passageiros;
    vector<int> tripulantes;
};

class GerenciadorVoos {
public:
    void ler_dados_arquivos();
    void buscar_passageiro(int codigo);
    void listar_voos_passageiro(int codigo_passageiro);
    const vector<Passageiro>& get_passageiros() const; // Método público para acessar passageiros
    void atualizar_pontos_fidelidade(int codigo_passageiro);

private:
    vector<Passageiro> passageiros;
    vector<Voo> voos;
};

class CadastroPassageiro {
public:
    bool cadastrar(const string& arquivo, const Passageiro& passageiro) {
        if (passageiro.codigo <= 0 || passageiro.nome[0] == '\0' || passageiro.endereco[0] == '\0' || passageiro.telefone <= 0) {
            cerr << "Dados inválidos." << endl;
            return false;
        }

        ofstream outfile(arquivo, ios::binary | ios::app);
        if (!outfile.is_open()) {
            cerr << "Erro ao abrir o arquivo " << arquivo << endl;
            return false;
        }

        outfile.write(reinterpret_cast<const char*>(&passageiro), sizeof(Passageiro));
        outfile.close();
        return true;
    }
};

void GerenciadorVoos::ler_dados_arquivos() {
    passageiros.clear();
    voos.clear();

    ifstream arquivo_passageiros("passageiros.bin", ios::binary);
    if (arquivo_passageiros.is_open()) {
        Passageiro passageiro;
        while (arquivo_passageiros.read(reinterpret_cast<char*>(&passageiro), sizeof(Passageiro))) {
            passageiros.push_back(passageiro);
        }
        arquivo_passageiros.close();
    }

    ifstream arquivo_voos("voos.bin", ios::binary);
    if (arquivo_voos.is_open()) {
        Voo voo;
        while (arquivo_voos.read(reinterpret_cast<char*>(&voo), sizeof(Voo))) {
            voos.push_back(voo);
        }
        arquivo_voos.close();
    }
}

void GerenciadorVoos::buscar_passageiro(int codigo) {
    for (const Passageiro& passageiro : passageiros) {
        if (passageiro.codigo == codigo) {
            cout << "Passageiro encontrado: " << endl;
            cout << "Nome: " << passageiro.nome << endl;
            cout << "Endereço: " << passageiro.endereco << endl;
            cout << "Telefone: " << passageiro.telefone << endl;
            cout << "Quantidade de voos: " << passageiro.quantidade_voos << endl;
            
            return;
        }
    }
    cout << "Codigo de Passageiro não encontrado." << endl;
}

void GerenciadorVoos::listar_voos_passageiro(int codigo_passageiro) {
    bool encontrou_voo = false;

    for (const Voo& voo : voos) {
        if (find(voo.passageiros.begin(), voo.passageiros.end(), codigo_passageiro) != voo.passageiros.end()) {
            cout << "Voo encontrado:" << endl;
            cout << "Número do Voo: " << voo.numero << endl;
            cout << "Data: " << voo.data << endl;
            cout << "Origem: " << voo.origem << endl;
            cout << "Destino: " << voo.destino << endl;
            cout << "--------------------------------" << endl;
            encontrou_voo = true;
        }
    }

    if (!encontrou_voo) {
        cout << "Nenhum voo encontrado para o passageiro com código " << codigo_passageiro << "." << endl;
    }
}

void GerenciadorVoos::atualizar_pontos_fidelidade(int codigo_passageiro) {
    bool encontrou = false; // Verifica se o passageiro foi encontrado no arquivo binario
    for (Passageiro& passageiro : passageiros) {
        if (passageiro.codigo == codigo_passageiro) {
            encontrou = true; // Se encontrou torna verdadeiro
            passageiro.pontos_fidelidade = passageiro.quantidade_voos * 10; // Calcula os pontos de fidelidade
            cout << "O passageiro de código " << codigo_passageiro << " tem " 
                 << passageiro.pontos_fidelidade << " pontos" << endl; 
            break;
        }
    }

    if (!encontrou) { // Caso nenhum passageiro com o código tenha sido encontrado
        cerr << "Erro: Não existe um passageiro com o código " << codigo_passageiro << " ainda." << endl;
    }
}



const vector<Passageiro>& GerenciadorVoos::get_passageiros() const {
    return passageiros;
}

// Função para garantir que a entrada seja um número inteiro
template <typename T>
bool ler_inteiro(T& num) {
    while (!(cin >> num)) {
        cout << "Entrada inválida. Digite somente numeros." << endl;
        cin.clear(); // Faz a limpeza da falha de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a linha atual
    }
    return true;
}

// Função para perguntar ao usuário a quantidade de voos realizados
void pedir_quantidade_voos(Passageiro& passageiro) {
    while (true) {
        cout << "Quantos voos o passageiro realizou? ";
        if (ler_inteiro(passageiro.quantidade_voos) && passageiro.quantidade_voos >= 0) {
            break;
        } else {
            cout << "Entrada inválida. Digite somente numeros inteiro não negativo." << endl;
        }
    }
}

int main() {
    GerenciadorVoos gerenciador;
    gerenciador.ler_dados_arquivos();

    int opcao1;
    // Menu principal do codigo 
    do {
        cout << "\n=== Sistema de Gestão de Voos ===\n";
        cout << "1. Cadastrar Passageiro\n";
        cout << "7. Pesquisa\n";
        cout << "8. Programa de Fidelidade\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        ler_inteiro(opcao1); // Garante que a opção seja um número inteiro

        switch (opcao1) {
            // Cadastro de passageiro
            case 1: {
                CadastroPassageiro cadastro;
                Passageiro passageiro;
                bool sucesso = false;
                do {
                    cout << "Digite o Nº código do passageiro: ";
                    ler_inteiro(passageiro.codigo);  // Validação de código numérico

                    bool codigoExistente = false;
                    for (const auto& p : gerenciador.get_passageiros()) {
                        if (p.codigo == passageiro.codigo) {
                            cout << "Erro: Já existe um passageiro com esse código!\n";
                            codigoExistente = true;
                            break;
                        }
                    }

                    if (codigoExistente) {
                        cout << "Digite um numero maior que 1 para continuar ou Digite 0 para voltar ao menu principal.\n";
                        ler_inteiro(passageiro.codigo);
                        if (passageiro.codigo == 0) break;
                        continue;
                    }

                    cout << "Digite o nome do passageiro: ";
                    cin.ignore();
                    cin.getline(passageiro.nome, sizeof(passageiro.nome));
                    cout << "Digite o endereço do passageiro: ";
                    cin.getline(passageiro.endereco, sizeof(passageiro.endereco));
                    cout << "Digite o Nº de telefone do passageiro: \n (31) ";
                    ler_inteiro(passageiro.telefone);  // Validação de telefone numérico

                    // Pergunta pela quantidade de voos
                    pedir_quantidade_voos(passageiro);

                    sucesso = cadastro.cadastrar("passageiros.bin", passageiro);
                    if (sucesso) {
                        cout << "Passageiro cadastrado com sucesso!\n";
                        gerenciador.ler_dados_arquivos();
                    } else {
                        cout << "Esse código já está em uso, utilize outro código.\n";
                    }
                } while (!sucesso);
                break;
            }

            case 7: {
                // Pesquisa do passageiro pelos codigos
                int opcao, codigo;
                do {
                    cout << "\n=== Sistema de Gestão de Voos ===\n";
                    cout << "1. Buscar passageiro\n";
                    cout << "2. Histórico de voos\n";
                    cout << "0. Voltar\n";
                    cout << "Escolha uma opção: ";
                    ler_inteiro(opcao); // Validação da opção numérica

                    switch (opcao) {
                        case 1:
                            cout << "Digite o código do passageiro: ";
                            ler_inteiro(codigo);
                            gerenciador.buscar_passageiro(codigo);
                            break;

                        case 2:
                            cout << "Digite o código do passageiro: ";
                            ler_inteiro(codigo);
                            gerenciador.listar_voos_passageiro(codigo);
                            break;

                        case 0:
                            cout << "Voltando ao menu principal...\n";
                            break;

                        default:
                            cout << "Opção inválida! Tente novamente.\n";
                    }
                } while (opcao != 0);
                break;
            }

            case 8: {
                int codigo;
                cout << "\n=== Programa de Fidelidade ===\n";
                cout << "Digite o código do passageiro: ";
                ler_inteiro(codigo);
                gerenciador.atualizar_pontos_fidelidade(codigo);
                break;
            }

            case 0:
                cout << "Saindo do sistema...\n";
                break;

            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao1 != 0);

    return 0;
}
