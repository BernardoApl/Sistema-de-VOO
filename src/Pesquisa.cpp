
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

// Estrutura para armazenar os dados da tripulação
struct Tripulacao {
    int codigo;
    char nome[100];
    char telefone[20];
    char cargo[50];
};

// Classe para realizar operações de passageiros e tripulantes
class CadastroDados {
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

    vector<Tripulacao> carregar_tripulantes(const string& arquivo) {
        vector<Tripulacao> tripulantes;
        ifstream infile(arquivo, ios::binary);
        if (infile.is_open()) {
            Tripulacao t;
            while (infile.read(reinterpret_cast<char*>(&t), sizeof(Tripulacao))) {
                tripulantes.push_back(t);
            }
            infile.close();
        }
        return tripulantes;
    }

    Passageiro* buscar_passageiro(vector<Passageiro>& passageiros, int codigo) {
        for (auto& passageiro : passageiros) {
            if (passageiro.codigo == codigo) {
                return &passageiro;
            }
        }
        return nullptr;
    }

    Tripulacao* buscar_tripulante(vector<Tripulacao>& tripulantes, int codigo) {
        for (auto& tripulante : tripulantes) {
            if (tripulante.codigo == codigo) {
                return &tripulante;
            }
        }
        return nullptr;
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
    CadastroDados cadastro;
    string arquivo_passageiros = "passageiros.bin";
    string arquivo_tripulantes = "tripulantes.bin";

    vector<Passageiro> passageiros = cadastro.carregar_passageiros(arquivo_passageiros);
    vector<Tripulacao> tripulantes = cadastro.carregar_tripulantes(arquivo_tripulantes);

    int opcao;
    do {
       
        cout << "1. Buscar Passageiro\n";
        cout << "2. Buscar Tripulante\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        ler_inteiro(opcao);

        switch (opcao) {
            case 1: {
                int codigo;
                cout << "Digite o código do passageiro: ";
                ler_inteiro(codigo);

                Passageiro* passageiro = cadastro.buscar_passageiro(passageiros, codigo);
                if (passageiro) {
                    cout << "\nPassageiro encontrado:\n";
                    cout << "Código: " << passageiro->codigo << "\n";
                    cout << "Nome: " << passageiro->nome << "\n";
                    cout << "Endereço: " << passageiro->endereco << "\n";
                    cout << "Telefone: " << passageiro->telefone << "\n";
                    cout << "Quantidade de voos: " << passageiro->quantidade_voos << "\n";
                } else {
                    cout << "Passageiro não encontrado." << endl;
                }
                break;
            }

            case 2: {
                int codigo;
                cout << "Digite o código do tripulante: ";
                ler_inteiro(codigo);

                Tripulacao* tripulante = cadastro.buscar_tripulante(tripulantes, codigo);
                if (tripulante) {
                    cout << "\nTripulante encontrado:\n";
                    cout << "Código: " << tripulante->codigo << "\n";
                    cout << "Nome: " << tripulante->nome << "\n";
                    cout << "Telefone: " << tripulante->telefone << "\n";
                    cout << "Cargo: " << tripulante->cargo << "\n";
                } else {
                    cout << "Tripulante não encontrado." << endl;
                }
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
