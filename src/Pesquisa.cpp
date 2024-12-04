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

struct Tripulacao {
  int codigo;
  string nome;
  string telefone;
  string cargo; // 1 - piloto, 2 - co-piloto, 3 - comissario
};



vector<Tripulacao> lerTripulacao() {
  vector<Tripulacao> tripulantes;
  ifstream arquivo("tripulacao.dat", ios::binary);
  if (!arquivo) {
    cerr << "Erro ao abrir o arquivo para leitura!" << endl;
    return tripulantes;
  }

  Tripulacao tripulacao;
  size_t tamanho;
  string buffer;

  while (arquivo.read(reinterpret_cast<char *>(&tripulacao.codigo),
                      sizeof(tripulacao.codigo))) {
    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    tripulacao.nome = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    tripulacao.telefone = buffer;

    arquivo.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho));
    buffer.resize(tamanho);
    arquivo.read(&buffer[0], tamanho);
    tripulacao.cargo = buffer;

    tripulantes.push_back(tripulacao);
  }

  arquivo.close();
  return tripulantes;
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
class GerenciadorVoos {
public:
    void ler_dados_arquivos();
    void buscar_passageiro(int codigo);
    void listar_voos_passageiro(int codigo_passageiro);
    void buscar_tripulante(int codigo);
    void cadastrar_voo(); // Novo método para cadastrar voos
    void listar_voos(); // Novo método para listar voos
    const vector<Passageiro>& get_passageiros() const; // Método público para acessar passageiros
    void atualizar_pontos_fidelidade(int codigo_passageiro);

private:
    vector<Passageiro> passageiros;
    vector<Voo> voos;
};




void GerenciadorVoos::buscar_tripulante(int codigo) {
    vector<Tripulacao> tripulantes = lerTripulacao(); // Lê os tripulantes do arquivo binário

    for (const Tripulacao& tripulante : tripulantes) {
        if (tripulante.codigo == codigo) {
            string cargo;
            if (tripulante.cargo == "1") {
                cargo = "Piloto";
            } else if (tripulante.cargo == "2") {
                cargo = "Co-piloto";
            } else {
                cargo = "Comissário";
            }

            // Exibe as informações do tripulante encontrado
            cout << "Tripulante encontrado: " << endl;
            cout << "Código: " << tripulante.codigo << endl;
            cout << "Nome: " << tripulante.nome << endl;
            cout << "Telefone: " << tripulante.telefone << endl;
            cout << "Cargo: " << cargo << endl;
            return;
        }
    }

    cout << "Código de tripulante não encontrado." << endl;
}



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


int main() {
    GerenciadorVoos gerenciador;
    gerenciador.ler_dados_arquivos();

    int opcao1;
    // Menu principal do código
    do {
        cout << "7. Pesquisa\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        ler_inteiro(opcao1); // Garante que a opção seja um número inteiro

        switch (opcao1) {
            // Cadastro de passageiro

            case 7: {
                // Pesquisa do passageiro e tripulante pelos códigos
                int opcao, codigo;
                do {
                    cout << "\n=== Sistema de Pesquisa ===\n";
                    cout << "1. Buscar Passageiro\n";
                    cout << "2. Buscar Tripulante\n";  // Nova opção para buscar tripulante
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
                            cout << "Digite o código do tripulante: ";
                            ler_inteiro(codigo);
                            gerenciador.buscar_tripulante(codigo); // Chama a função de busca do tripulante
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

            case 0:
                cout << "Saindo do sistema...\n";
                break;

            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao1 != 0);

    return 0;
}



