#include <iostream> 
#include <fstream> 
#include <vector>  
#include <string>  
#include <algorithm> 
#include <limits> 
#include "pesquisa.h"

using namespace std;

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


template <typename T>
bool ler_inteiro(T& num) {
    while (!(cin >> num)) {
        cout << "Entrada inválida. Digite somente numeros." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    return true;
}
class GerenciadorVoos {
public:
    void ler_dados_arquivos();
    void buscar_passageiro(int codigo);
    void listar_voos_passageiro(int codigo_passageiro);
    void buscar_tripulante(int codigo);
    void cadastrar_voo(); 
    void listar_voos(); 
    const vector<Passageiro>& get_passageiros() const; 
    void atualizar_pontos_fidelidade(int codigo_passageiro);

private:
    vector<Passageiro> passageiros;
    vector<Voo> voos;
};




void GerenciadorVoos::buscar_tripulante(int codigo) {
    vector<Tripulacao> tripulantes = lerTripulacao(); 

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
    do {
        cout << "7. Pesquisa\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        ler_inteiro(opcao1);

        switch (opcao1) {

            case 7: {
                int opcao, codigo;
                do {
                    cout << "\n=== Sistema de Pesquisa ===\n";
                    cout << "1. Buscar Passageiro\n";
                    cout << "2. Buscar Tripulante\n";  
                    cout << "0. Voltar\n";
                    cout << "Escolha uma opção: ";
                    ler_inteiro(opcao); 

                    switch (opcao) {
                        case 1:
                            cout << "Digite o código do passageiro: ";
                            ler_inteiro(codigo);
                            gerenciador.buscar_passageiro(codigo);
                            break;

                        case 2:
                            cout << "Digite o código do tripulante: ";
                            ler_inteiro(codigo);
                            gerenciador.buscar_tripulante(codigo); 
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



