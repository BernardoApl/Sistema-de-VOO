#include <iostream> // entrada e saída de dados
#include <fstream>  // manipulação de arquivos (leitura e escrita)
#include <string>   // manipulação de strings
#include <vector>   // manipulação de listas
#include <limits>   // para limpar o buffer de entrada

using namespace std;

// Estrutura para armazenar os dados do passageiro
struct Passageiro {
    int codigo;
    char nome[100];
    char endereco[200];
    int telefone;
    int quantidade_voos;
};

// Classe para realizar o cadastro de passageiros
class CadastroPassageiro {
public:
    vector<Passageiro> carregar_passageiros(const string& arquivo) {
        vector<Passageiro> passageiros;
        ifstream infile(arquivo, ios::binary);
        if (infile.is_open()) {
            Passageiro p;
            while (infile.read(reinterpret_cast<char*>(&p), sizeof(Passageiro))) {
                passageiros.push_back(p);
            }
            infile.close();
        }
        return passageiros;
    }

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

// Função para garantir que a entrada seja um número inteiro
template <typename T>
bool ler_inteiro(T& num) {
    while (!(cin >> num)) {
        cout << "Entrada inválida. Digite somente números." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return true;
}

// Função principal
int main() {
    CadastroPassageiro cadastro;
    string arquivo = "passageiros.bin";
    vector<Passageiro> passageiros = cadastro.carregar_passageiros(arquivo);
    Passageiro passageiro;

    int opcao;
    do {
        cout << "\n=== Sistema de Voo ===\n";
        cout << "1. Cadastrar Passageiro\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        ler_inteiro(opcao);

        switch (opcao) {
            case 1: {
                bool sucesso = false;
                do {
                    bool codigoExistente = false;
                    cout << "Digite o código do passageiro: ";
                    ler_inteiro(passageiro.codigo);

                    for (const auto& p : passageiros) {
                        if (p.codigo == passageiro.codigo) {
                            cout << "Erro: Código já existente. Digite outro código." << endl;
                            codigoExistente = true;
                            break;
                        }
                    }

                    if (codigoExistente) {
                        continue;
                    }

                    cout << "Digite o nome do passageiro: ";
                    cin.ignore();
                    cin.getline(passageiro.nome, sizeof(passageiro.nome));

                    cout << "Digite o endereço do passageiro: ";
                    cin.getline(passageiro.endereco, sizeof(passageiro.endereco));

                    cout << "Digite o telefone do passageiro: (31) ";
                    ler_inteiro(passageiro.telefone);

                    cout << "Digite a quantidade de voos realizados: ";
                    ler_inteiro(passageiro.quantidade_voos);

                    sucesso = cadastro.cadastrar(arquivo, passageiro);
                    if (sucesso) {
                        cout << "Passageiro cadastrado com sucesso!" << endl;
                        passageiros.push_back(passageiro);
                    } else {
                        cout << "Erro no cadastro. Tente novamente." << endl;
                    }
                } while (!sucesso);
                break;
            }

            case 0:
                cout << "Saindo do sistema..." << endl;
                break;

            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0;
}
