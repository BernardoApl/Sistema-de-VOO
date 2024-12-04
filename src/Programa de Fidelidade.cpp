
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
    // Menu principal do código
    do {
        
        cout << "8. Programa de Fidelidade\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        ler_inteiro(opcao1); // Garante que a opção seja um número inteiro

        switch (opcao1) {
            // Cadastro de passageiro

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

